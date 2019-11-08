#!/bin/bash

outputFile="results.txt"

rm -f $outputFile
# arraysize:
for a in 1000 5000 10000 50000 100000 250000 500000 1000000 2000000 4000000 10000000
do
	# number of subdivisions:
	echo -e -n $a'\t' >> $outputFile
	make clean
	make CFLAGS="-DLEN=$a"
	arraymult
	echo '' >> $outputFile
done
