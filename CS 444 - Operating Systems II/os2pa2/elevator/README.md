Assuming you're on the `os2` server and you're standing at the directory to which the tarball file extract. From now on, we call this directory `${PROJECT_ROOT}`. 

To be sure, please set an environment variable for this
```
$PROJECT_ROOT=<the path to directory you just extract our tallball to>
```

Go into the `elevator` directory to grade this part:
```
cd $PROJECT_ROOT/elevator
```

Clone linux stock source code, and rename it so we don't have conflicting name when we clone it again
```
./setup.sh
```

content of `setup.sh`:
```
git clone git://git.yoctoproject.org/linux-yocto-3.19
cd linux-yocto-3.19
git checkout tags/v3.19.2
rm -rf .git
cd ..
mv linux-yocto-3.19 linux
```

If you already have cloned the linux original source, please rename it too because the later steps below depend on this name.

Check if the patch is ok to proceed without error
```
cd $PROJECT_ROOT/elevator/linux/block
patch -p1 --dry-run < ../../elevator.patch
```
If there's no error, proceed to applying the patch:
```
cd $PROJECT_ROOT/elevator/linux/block
patch -p1 < ../../elevator.patch
```

If the new scheduler is not there or in case our patch file doesn't work, please apply the patch manually with our provided source code along with following instruction:

```
cd $PROJECT_ROOT/elevator
./manual_patch.sh
```
content of `manual_patch.sh`:
```
yes | cp ./Makefile ./linux/block/Makefile
yes | cp ./Kconfig.iosched ./linux/block/Kconfig.iosched
yes | cp ./look-iosched.c ./linux/block/look-iosched.c

```

Compile the kernel:
```
cd $PROJECT_ROOT/elevator
./compile.sh
```
content of `compile.sh`:
```
source /scratch/files/environment-setup-i586-poky-linux
yes | cp /scratch/files/config-3.19.2-yocto-standard ./linux/.config
cd ./linux
make -j4 all
if [ $? -ne 0 ]; then
    echo "------------------"
    echo "COMPILATION FAILED"
    echo "------------------"
fi
cd ..
```
The kernel compiling process will ask you to choose a default scheduler, choose LOOK as the default scheduler

Boot:
```
cd $PROJECT_ROOT/elevator
./boot.sh
```

content of `boot.sh`:
```
source /scratch/files/environment-setup-i586-poky-linux
qemu-system-i386 -gdb tcp::5509 -S -nographic -kernel ./linux/arch/x86/boot/bzImage -drive file=/scratch/files/core-image-lsb-sdk-qemux86.ext4 -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/hda rw console=ttyS0 debug elevator=look"

```


The boot process will pause. Open `gdb` and run commands:
```
target remote tcp:localhost:5009
c
```
to allow the kernel to continue booting

There are two testing Bash script named `test1.sh` and `test2.sh` located at `$PROJECT_ROOT/elevator`. These scripts repeatedly writes >=1000 bytes into each file at directory `./test_data/test_data`

Once the kernel finish booting, login as `root` and create 2 files with the same content as `test1.sh` and `test2.sh`, remember to `chmod +x` them, and then run those file to generate a lot of heavy disk write requests.

If you have any difficulty creating these test files in the vm, please download our disk image file from our group directory on `os2` at `/scratch/fall2018/group9/os2pa2/elevator/core-image-lsb-sdk-qemux86.ext4`. Please email or send us a message on Canvas if you have any difficulty testing our work

After a slight delay, the `printk` calls in the C-LOOK scheduler implementation will print out on the terminal the sector numbers being add to request queue and what are, or have been, being processed by the IO scheduler


