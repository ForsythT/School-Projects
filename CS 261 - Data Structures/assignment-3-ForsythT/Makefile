all: testADT testLL

testADT: cirListDeque.h cirListDeque.c testADT.c
	gcc -g -Wall -std=c99 -o testADT cirListDeque.c testADT.c

testLL: linkedList.h linkedList.c testLL.c
	gcc -g -Wall -std=c99 -o testLL linkedList.c testLL.c

clean:
	rm testADT testLL
