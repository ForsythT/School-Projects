#!/bin/bash
cd linux
cp arch/arm64/boot/Image /media/$( whoami )/boot/kernel8.img
cd ..
