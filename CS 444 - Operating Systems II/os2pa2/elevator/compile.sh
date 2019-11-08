#!/bin/bash

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

