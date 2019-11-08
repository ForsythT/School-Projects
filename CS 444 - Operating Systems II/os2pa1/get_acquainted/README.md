- clone yocto project
- change to v3.19.2
- delete the yocto remote
- source /scratch/opt/environment-setup-i586-poky-linux
- copy files from  /scratch/files/
- boot up (test) with qemu-system-i386 -gdb tcp::5509 -S -nographic -kernel bzImage-qemux86.bin -drive file=core-image-lsb-sdk-qemux86.ext4,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
- run gdb and continue
- copy from /scratch/files/config-3.19.2-yocto-qemu to $SRC_ROOT/.config
- make -j4 all
- $ ls ./arch/x86/boot/bzImage 
  -rw-r--r--. 1 upg3108 6632704 Oct  8 12:36 ./arch/x86/boot/bzImage
- cp ./arch/x86/boot/bzImage .
- boot again with -kernel=./bzImage


  -rw-r--r--.  1 upg3108 2804557824 Oct  8 12:53 core-image-lsb-sdk-qemux86.ext4
  => Too big to push

  git rebase -i
  git filter-branch --index-filter 'git rm -r --cached --ignore-unmatch get_acquainted/core-image-lsb-sdk-qemux86.ext4' HEAD
  => that file was deleted
  => push


