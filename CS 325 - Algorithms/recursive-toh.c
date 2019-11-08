// Tim Forsyth
// ONID Number: 932711331
//
// Recommended to compile with:
// gcc -o hanoi recursive-toh.c
//
// Run with command structure:
// hanoi [num disks]

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isNumber(char[]);
int Hanoi(char, char, char, int);

int main(int argc, char *argv[]){
	if(argc != 2 || isNumber(argv[1]) == 0){
		printf("hanoi: hanoi [num disks]\n");
		exit(-1);
	}
	int n = atoi(argv[1]);
	//printf("Hanoi(A, B, C, n)\n");
	clock_t begin = clock();
	Hanoi('A', 'B', 'C', n);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//printf("Run Time: %f\n", time_spent);
}

int isNumber(char number[]){
	int i = 0;
	if(number[0] == '-')
		return 0;
	for(i; number[i] != 0; i++){
		if(!isdigit(number[i]))
			return 0;
	}
	return 1;
}

int Hanoi(char a, char b, char c, int n){
	if(n == 1){
		printf("Move disk 1 from %c to %c\n", a, c);
	//	printf("Completed Hanoi(%c, %c, %c, %d) Call\n", a, b, c, n);
		return;
	}	
	//printf("Hanoi(%c, %c, %c, %d)\n", a, c, b, n-1);
	Hanoi(a, c, b, n-1);
	//printf("Hanoi(%c, %c, %c, %d)\n", b, a, c, n-1);
	printf("Move disk %d from %c to %c\n", n, a, c);
	Hanoi(b, a, c, n-1);
	//printf("Completed Hanoi(%c, %c, %c, %d) Call\n", a, b, c, n);
}
