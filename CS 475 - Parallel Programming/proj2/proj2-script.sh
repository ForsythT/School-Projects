#!/bin/bash

outputFile="results.txt"

rm -f $outputFile
# number of threads:
echo -e '\t16\t64\t256\t1024\t16384\t65536\t262144\t1048576' >> $outputFile
for t in 1 2 4 6 8
do
	# number of subdivisions:
	echo -e -n $t'\t' >> $outputFile
	for s in 4 8 16 32 64 128 256 512 1024
	do
		g++ -DNUMNODES=$s -DNUMT=$t -DOUTPUT_FILE=\"$outputFile\" proj2.cpp -o proj2 -O3 -lm -fopenmp
		./proj2
	done
	echo '' >> $outputFile
done
