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



int main(int argc, char *argv[]){
	int i, j, n1, n2, bigger, aSize, bSize, solSize;
	
	n1 = atoi(argv[1]);
	n2 = atoi(argv[3+n1]);
	aSize = n1+1;
	bSize = n2+1;
	solSize = aSize+bSize-1;

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

	int polyA[aSize];
	for(i = 0; i < aSize; i++){
		polyA[i] = 0;
	}
	
	for(i = 2; i < 3+n1; i++){
		polyA[i-2] = atoi(argv[i]);
	}
	
	int polyB[bSize];
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

	int sol[solSize];

	for(i = 0; i < solSize; i++){
		sol[i] = 0;
	}

	struct timespec begin, end;
	clock_gettime(CLOCK_REALTIME, &begin);
	
	for(i = 0; i < aSize; i++){
		for(j = 0; j < bSize; j++){
			sol[i+j] += polyA[i]*polyB[j];
		}
	}
	
	clock_gettime(CLOCK_REALTIME, &end);
	double time_spent = (double)(end.tv_nsec - begin.tv_nsec) / CLOCKS_PER_SEC;
	
	printf("Solution\n");
	printPoly(sol, solSize);

	printf("\nRunning Time: %f s\n", time_spent);
	
	return 0;
}
