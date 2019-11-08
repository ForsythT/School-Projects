#!/bin/bash

outputFile="results.txt"
rm -f $outputFile
g++ proj3.cpp -o proj3 -O3 -lm -fopenmp
./proj3 > $outputFile
