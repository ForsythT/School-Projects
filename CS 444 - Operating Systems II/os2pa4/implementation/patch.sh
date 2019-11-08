#!/bin/bash

patch -p0 --dry-run < ./morse.patch
if [ $? -ne 0  ]; then
    echo "------------------"
    echo "PATCHING FAILED"
    echo "=> Running manual patch"
    echo "------------------"
	yes | cp ./Makefile ./linux/drivers/leds/triggers/Makefile
	yes | cp ./Kconfig ./linux/drivers/leds/triggers/Kconfig
	yes | cp ./ledtrig-morse.c ./linux/drivers/leds/triggers/ledtrig-morse.c
fi
patch -p0 < ./morse.patch
