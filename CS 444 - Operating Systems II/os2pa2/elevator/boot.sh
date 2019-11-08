#!/bin/bash

source /scratch/files/environment-setup-i586-poky-linux
qemu-system-i386 -gdb tcp::5509 -S -nographic -kernel ./linux/arch/x86/boot/bzImage -drive file=/scratch/files/core-image-lsb-sdk-qemux86.ext4 -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/hda rw console=ttyS0 debug elevator=look"

