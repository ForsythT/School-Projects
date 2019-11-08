#!/bin/bash

git clone git://git.yoctoproject.org/linux-yocto-3.19
cd linux-yocto-3.19
git checkout tags/v3.19.2
rm -rf .git
cd ..
mv linux-yocto-3.19 linux
