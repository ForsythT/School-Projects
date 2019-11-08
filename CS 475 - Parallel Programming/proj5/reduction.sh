#!/bin/bash

outputFile="reduction-results.txt"
rm -f $outputFile
# print local work size:
echo -e '\t32\t64\t128\t256' >> $outputFile
for t in 1024 4096 16384 65536 262144 1048576 2097152 4194304 8388608
do
	# NUMT = t
	# print global work size:
	echo -e -n $t'\t' >> $outputFile
	for s in 32 64 128 256
	do
	# NUMTRIALS = s
		g++ -DNUM_ELEMENTS=$t -DLOCAL_SIZE=$s -DOUTPUT_FILE=\"$outputFile\" -o reduction reduction.cpp ../../../../../../scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp
		./reduction >> $outputFile
	done
	echo '' >> $outputFile
done
