#!/bin/bash

outputFile="results.txt"

rm -f $outputFile
# BLOCKSIZE:
echo -e '\t16K\t32K\t64K\t128K\t256K\t512K' >> $outputFile
for t in 16 32 64
do
	# NUMTRIALS (SIZE):
	echo -e -n $t'\t' >> $outputFile
	for s in 16000 32000 64000 128000 256000 512000
	do
		make clean
		make BLOCKSIZE="-DBLOCKSIZE=$t" SIZE="-DSIZE=$s"
		monteCarlo
	done
	echo '' >> $outputFile
done
