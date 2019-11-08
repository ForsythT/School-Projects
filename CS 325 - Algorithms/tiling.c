#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int tile(int**, int, int, int, int, int, int*);

int main(int argc, char *argv[]){
	if(argc != 4){
		printf("tiling: tiling [k value] [missing x] [missing y]\n");
		exit(1);
	}
	int k = atoi(argv[1]);
	int px = atoi(argv[3]);
	int py = atoi(argv[2]);

	int n = pow(2,k)-1;
	int var = 1;
	int *move = malloc(sizeof(int));
	move = &var;
	int **b = (int**)malloc((n+1) * sizeof(int*));
	
	int i, j;
	for(i = 0; i <= n; i++){
		b[i] = (int*)malloc((n+1) * sizeof(int));
	}

	for(i = 0; i <= n; i++){
		for(j = 0; j <= n; j++){
			b[i][j] = 0;
		}
	}
	
	clock_t begin = clock();
	tile(b, n, 0, 0, px, py, move);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	/*for(i = 0; i <= n; i++){
		for(j = 0; j <= n; j++){
			if(k > 2 && k < 5){
				if(b[i][j] < 10){
					printf("%d  ", b[i][j]);
				}
				else{
					printf("%d ", b[i][j]);
				}
			}
			else if(k >= 5){
				if(b[i][j] < 10){
					printf("%d   ", b[i][j]);
				}
				else if (b[i][j] < 100){
					printf("%d  ", b[i][j]);
				}
				else{
					printf("%d ", b[i][j]);
				}
				
			}
			else{
				printf("%d ", b[i][j]);
			}
		}
		printf("\n");
	}*/

	printf("\n--------RUN TIME--------\n\n%f s\n", time_spent);
}

int tile(int **b, int n, int x, int y, int px, int py, int *move){
	int i, j, m, centerx, centery;
	int px1, py1, px2, py2, px3, py3, px4, py4;

	if(n == 2){
		for(i = x; i < x+2; i++){
			for(j = y; j < y+2; j++){
				if(i != px || j != py){
					b[i][j] = *move;
				}
			}
		}

		return 0;
	}

	m = (n+1)/2;
	centerx = x+m;
	centery = y+m;


	// Checking if empty tile is in first quadrant 1
	if(px < centerx && py < centery){
		b[centerx][centery] = *move;
		b[centerx][centery-1] = *move;
		b[centerx-1][centery] = *move;
		px1 = px;
		py1 = py;
	}
	else{
		px1 = centerx-1;
		py1 = centery-1;
	}

	// Checking if empty tile is in second quadrant 3
	if(px >= centerx && py < centery){
		b[centerx][centery] = *move;
		b[centerx-1][centery] = *move;
		b[centerx-1][centery-1] = *move;
		px2 = px; 
		py2 = py;
	}
	else{
		px2 = centerx;
		py2 = centery-1;
	}

	// Checking if empty tile is in third quadrant 4
	if(px >= centerx && py >= centery){
		b[centerx][centery-1] = *move;
		b[centerx-1][centery] = *move;
		b[centerx-1][centery-1] = *move;
		px3 = px;
		py3 = py;
	}
	else{
		px3 = centerx; py3 = centery;
	}

	// Checking if empty tile is in fourth quadrant 2
	if(px < centerx && py >= centery){
		b[centerx][centery] = *move;
		b[centerx][centery-1] = *move;
		b[centerx-1][centery-1] = *move;
		px4 = px;
		py4 = py;
	}
	else{
		px4 = centerx-1;
		py4 = centery;
	}

	// Recursive calls
	(*move)++;
	tile(b, m, x, y, px1, py1, move);

	(*move)++;
	tile(b, m, x+m, y, px2, py2, move);

	(*move)++;
	tile(b, m, x+m, y+m, px3, py3, move);
	
	(*move)++;
	tile(b, m, x, y+m, px4, py4, move);
}
