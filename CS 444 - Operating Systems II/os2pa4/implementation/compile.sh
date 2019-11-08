#!/bin/bash
cd linux
KERNEL=kernel8
make -j4 ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- all
if [ $? -ne 0  ]; then
	echo "------------------"
	echo "COMPILATION FAILED"
	echo "------------------"
    cd ..
fi
cd ..
