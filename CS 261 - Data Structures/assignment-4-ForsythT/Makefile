all: testbst

testbst: bst.h structs.h cirListDeque.h testbst.c bst.c compare.c cirListDeque.c
	gcc -g -Wall -std=c99 -o testbst testbst.c bst.c compare.c cirListDeque.c 

clean:
	rm testbst
