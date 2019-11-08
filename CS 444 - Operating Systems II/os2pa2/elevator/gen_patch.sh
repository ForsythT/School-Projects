#!/bin/bash

#diff -urN linux-yocto-3.19 linux > elevator.patch
diff -urN linux-yocto-3.19/block linux/block > elevator.patch
