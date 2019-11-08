#!/bin/bash

outputFile="results.txt"
# number of threads:
echo -e '\t10000\t50000\t100000\t500000\t1000000\t5000000\t6250000\t7500000\t10000000' >> $outputFile
for t in 1 2 4 6 8
do
	# NUMT = t
	# number of trials:
	echo -e -n $t'\t' >> $outputFile
	for s in 10000 50000 100000 500000 1000000 5000000 6250000 7500000 10000000
	do
	# NUMTRIALS = s
		g++ -DNUMTRIALS=$s -DNUMT=$t -DOUTPUT_FILE=\"$outputFile\" proj1.cpp -o proj1 -O3 -lm -fopenmp
		./proj1
	done
	echo '' >> $outputFile
done
