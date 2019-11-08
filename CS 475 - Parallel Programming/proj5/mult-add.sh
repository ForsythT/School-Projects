#!/bin/bash

outputFile="multadd-results.txt"
rm -f $outputFile
# global work size:
echo -e '\t8\t16\t32\t64\t128\t256\t512' >> $outputFile
for t in 1024 4096 16384 65536 262144 1048576 2097152 4194304 8388608
do
	# NUMT = t
	# local work size:
	echo -e -n $t'\t' >> $outputFile
	for s in 8 16 32 64 128 256 512
	do
	# NUMTRIALS = s
		g++ -DNUM_ELEMENTS=$t -DLOCAL_SIZE=$s -DOUTPUT_FILE=\"$outputFile\" -o multadd multadd.cpp ../../../../../../scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp
		./multadd >> $outputFile
	done
	echo '' >> $outputFile
done
