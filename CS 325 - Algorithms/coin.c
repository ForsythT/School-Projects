#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int findCoin(int*, int, int, int*);
int balance(int*, int, int, int, int, int*);

int main(int argc, char *argv[]){
	srand(time(NULL));
	
	if(argc < 2){
		printf("coin: coin [num coins (3^this num is num coins used)]");
		exit(1);
	}
	
	int n = atoi(argv[1]);
	int numC = pow(3, n);
	int *coins = malloc(numC * sizeof(int));
	if(!coins){
		printf("Malloc failed! Too many coins.\n");
		exit(1);
	}
	int i;
	
	// Set each 'coin' to be 5 weight
	for(i = 0; i < numC; i++){
		coins[i] = 5;
	}

	// Get random index from 0 to numC-1
	int idx = rand() % numC;

	// Get random weight from 0 to 9 (except for 5, obviously)
	int weight = 5;
	while(weight == 5){
		weight = rand() % 10;
	}

	// Place that 'coin' in the idx with its new weight
	coins[idx] = weight;

	int *numWeigh = malloc(sizeof(int));
	int num = 0;
	numWeigh = &num;
	
	clock_t begin = clock();
	int coinIdx = findCoin(coins, 0, numC-1, numWeigh);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Real Idx: %d\nFound Idx: %d\n", idx, coinIdx);

	printf("\n--------RUN TIME--------\n\n%f s\n", time_spent);
	printf("Num Weighs: %d\n", *numWeigh);
	free(coins);
}

int findCoin(int *coins, int low, int high, int *numW){
	int range = high - low + 1;
	
	if(range == 1){
		return low;
	}
	
	int split = range / 3;
	int low1, high1, low2, high2, low3, high3;

	low1 = low;
	high1 = low + split - 1;

	low2 = high1 + 1;
	high2 = low2 + split - 1;
	
	low3 = high2 + 1;
	high3 = high;

	if(balance(coins, low1, high1, low2, high2, numW) != 0){
		if(balance(coins, low1, high1, low3, high3, numW) != 0){
			findCoin(coins, low1, high1, numW);
		}
		else{
			findCoin(coins, low2, high2, numW);
		}
	}
	else{
		findCoin(coins, low3, high3, numW);
	}
}

int balance(int *coins, int lowL, int highL, int lowR, int highR, int *numW){
	int i;
	int left = 0;
	int right = 0;

	(*numW)++;

	// Get left side weight
	for(i = lowL; i <= highL; i++){
		left += coins[i];
	}

	// Get right side weight
	for(i = lowR; i <= highR; i++){
		right += coins[i];
	}

	if(left == right){
		return 0;
	}
	else{
		return 1;
	}
}
