#!/bin/bash
cd linux
cp arch/arm64/boot/Image /media/$( whoami )/kernel8.img
# cp arch/arm64/boot/dts/broadcom/bcm2710-rpi-3-b.dtb /media/aidan/boot
cd ..
