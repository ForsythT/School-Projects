#!/bin/bash

yes | cp ./Makefile ./linux/block/Makefile
yes | cp ./Kconfig.iosched ./linux/block/Kconfig.iosched
yes | cp ./look-iosched.c ./linux/block/look-iosched.c
