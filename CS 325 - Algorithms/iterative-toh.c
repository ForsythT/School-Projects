// Tim Forsyth
// ONID Number: 932711331
//
// Recommend to compile with:
// gcc -o itertoh iterative-toh.c
// 
// Run with command structure: 
// itertoh [num disks]

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isNumber(char[]);
int iterHanoi(char, char, char, int);

int main(int argc, char *argv[]){
	if(argc != 2 || isNumber(argv[1]) == 0){
		printf("itertoh: itertoh [num disks]\n");
		exit(-1);
	}
	int n = atoi(argv[1]);
	clock_t begin = clock();
	iterHanoi('A', 'B', 'C', n);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//	printf("Run Time: %f\n", time_spent);
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

int iterHanoi(char a, char b, char c, int n){
	int i = 1;
	char L1[n-1];
	char L2[n-1];
	char L3[n-1];
	char TEMP;
	int PAR[n-1];
	L1[0] = a;
	L2[0] = c;
	L3[0] = b;
	PAR[0] = 1;
	PAR[1] = 1;

	while(i >= 1){
		if(i != n-1){
			L1[i] = L1[i-1];
			L2[i] = L3[i-1];
			L3[i] = L2[i-1];
			PAR[i+1] = 1;
			i = i+1;
		}
		else{
			printf("Move top disk from %c to %c\n", L1[i-1], L3[i-1]);
			while(PAR[i] == 2){
				i = i-1;
			}
			if(i >= 1){
				printf("Move top disk from %c to %c\n", L1[i-1], L2[i-1]);
				PAR[i] = 2;
				TEMP = L1[i-1];
				L1[i-1] = L3[i-1];
				L3[i-1] = L2[i-1];
				L2[i-1] = TEMP;
			}
		}
	}
	return 0;
}
