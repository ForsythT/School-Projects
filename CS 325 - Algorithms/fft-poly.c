#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printPoly(int poly[], int n){
	int i;

	for(i = 0; i < n; i++){
		printf("%d", poly[i]);
		if(i != 0)
			printf("x^%d", i);
		if(i != n-1)
			printf(" + ");
	}
	printf("\n");
}

int* fft(int polyA[], int polyB[], int n){
	int i;

	if(n == 2){
		
		int *temp = malloc(sizeof(int));
		temp[0] = polyA[0]*polyB[0];
		return temp;
	}

	int m = n/2 + n%2;	

	int *aHigh = malloc(sizeof(int) * m);
	int *bHigh = malloc(sizeof(int) * m);
	int *aLow = malloc(sizeof(int) * m);
	int *bLow = malloc(sizeof(int) * m);

	for(i = 0; i < m; i++){
		aHigh[i] = polyA[i+m];
		bHigh[i] = polyB[i+m];
		aLow[i] = polyA[i];
		bLow[i] = polyB[i];
	}

	int *addLowHighA = malloc(sizeof(int) * m);
	int *addLowHighB = malloc(sizeof(int) * m);

	for(i = 0; i < m; i++){
		addLowHighA[i] = aLow[i]+aHigh[i];
		addLowHighB[i] = bLow[i]+bHigh[i];
	}

	int *sol = malloc(sizeof(int) * ((2*n)-1));

	for(i = 0; i < n; i++){
		sol[i] += lowAB[i];
		sol[i+m] += middle[i] - lowAB[i] - highAB[i];
		sol[i+2*m] += highAB[i];
	}

	return sol;
}

int main(int argc, char *argv[]){
	int i, j, n1, n2, bigger, aSize, bSize, solSize;
	
	n1 = atoi(argv[1]);
	n2 = atoi(argv[3+n1]);
	aSize = n1+1;
	bSize = n2+1;

	if(n1 > n2){
		bigger = 1;
	}
	else{
		bigger = 2;
	}

	if(bigger == 1){
		bSize = aSize;
	}
	else{
		aSize = bSize;
	}

	int *polyA = malloc(sizeof(int) * aSize);
	for(i = 0; i < aSize; i++){
		polyA[i] = 0;
	}
	
	for(i = 2; i < 3+n1; i++){
		polyA[i-2] = atoi(argv[i]);
	}
	
	int *polyB = malloc(sizeof(int) * bSize);
	for(i = 0; i < bSize; i++){
		polyB[i] = 0;
	}

	for(i = 4+n1; i < 5+n1+n2; i++){
		polyB[i-4-n1] = atoi(argv[i]);
	}

	printf("Polynomial A\n");
	printPoly(polyA, aSize);
	
	printf("Polynomial B\n");
	printPoly(polyB, bSize);

	solSize = aSize+bSize-1;

	int *sol = malloc(sizeof(int) * solSize);
	
	for(i = 0; i < solSize; i++){
		sol[i] = 0;
	}
	
	sol = dandc(polyA, polyB, aSize);

	printf("Solution\n");
	printPoly(sol, solSize);
	
	return 0;
}
