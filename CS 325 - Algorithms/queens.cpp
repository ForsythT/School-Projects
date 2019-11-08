#include <stdio.h>
#define MAX 9

void printSolution(int n, int sol[500][MAX], int numS){
	int j;

	printf("[ ");
	for(j = 0; j < n; j++){
		printf("%d ", sol[numS][j]);
	}
	printf("]\n");

}

void addSolution(int sol[500][MAX], int board[MAX][MAX], int n, int numS){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(board[j][i] == 1){
				sol[numS][i] = j+1;
			}
		}
	}

	printSolution(n, sol, numS);

	return;
}

bool reflect(int old_board[MAX][MAX], int new_board[MAX][MAX], int n){
	int i, j, x, y;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			x = i;
			y = n - 1 - j;
			new_board[i][j] = old_board[x][y];	
		}
	}
}

bool rotate(int old_board[MAX][MAX], int new_board[MAX][MAX], int n){
	int i, j;

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			new_board[i][j] = old_board[n-1-j][i];
		}
	}

	return true;
}

bool isSafe(int board[MAX][MAX], int row, int col, int n){
	int i, j;

	// Only need to check the left side since it is called when the queens are already placed from 0 to col-1
	
	// Checking this row (if it sees a 1 it will return false)
	for(i = 0; i < col; i++){
		if(board[row][i] == 1)
			return false;
	}

	// Checking the upper diagonal (if it sees a 1 it will return false)
	for(i = row, j = col; i >= 0 && j >= 0; i--, j--){
		if(board[i][j] == 1)
			return false;
	}

	// Checking the lower diagonal (if it sees a 1 it will return false)
	for(i = row, j = col; j >= 0 && i < n; i++, j--){
		if(board[i][j] == 1)
			return false;
	}
	
	return true;
}

void getArray(int board[MAX][MAX], int array[8][MAX], int n, int m){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(board[j][i] == 1){
				array[m][i] = j+1;
			}
		}
	}

	return;
}

bool isNew(int board[MAX][MAX], int trial[MAX][MAX], int n){
	int trial90[MAX][MAX];
	int trial180[MAX][MAX];
	int trial270[MAX][MAX];
	int trialRef[MAX][MAX];
	int trialRef90[MAX][MAX];
	int trialRef180[MAX][MAX];
	int trialRef270[MAX][MAX];
	
	int isoArray[8][MAX];
	int i, j;
	int m = 0;
	
	getArray(board, isoArray, n, m);

	rotate(board, trial90, n);
	m++;
	getArray(trial90, isoArray, n, m);

	rotate(trial90, trial180, n);
	m++;
	getArray(trial180, isoArray, n, m);

	rotate(trial180, trial270, n);
	m++;
	getArray(trial270, isoArray, n, m);
	
	reflect(trial270, trialRef, n);
	m++;
	getArray(trialRef, isoArray, n, m);
	
	rotate(trialRef, trialRef90, n);
	m++;
	getArray(trialRef90, isoArray, n, m);
	
	rotate(trialRef90, trialRef180, n);
	m++;
	getArray(trialRef180, isoArray, n, m);
	
	rotate(trialRef180, trialRef270, n);
	m++;
	getArray(trialRef270, isoArray, n, m);
	
	for(j = 1; j < 8; j++){
		for(i = 0; i < n; i++){
			if(isoArray[0][i] < isoArray[j][i])
				break;
			else if(isoArray[0][i] > isoArray[j][i])
				return false;
		}
	}
	
	return true;
}

int nQueens(int board[MAX][MAX], int col, int n, int numS, int sol[500][MAX]){
	int i;
	int trial[MAX][MAX];

	if(col >= n){
		if(isNew(board, trial, n)){
			addSolution(sol, board, n, numS);
			numS++;
		}
		return numS;
	}
	for(i = 0; i < n; i++){
		if(isSafe(board, i, col, n)){
			// Place queen
			board[i][col] = 1;

			// Recursively place the rest
			numS = nQueens(board, col+1, n, numS, sol);

			// Backtrack
			board[i][col] = 0;
		}
	}

	// Return total num of solutions
	return numS;
}



int solveNQueens(int n){
	int i, j;
	int x[MAX][MAX];
	int sol[500][MAX];
	int numS = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			x[i][j] = 0;
		}
	}

	numS = nQueens(x, 0, n, 0, sol);

	if(numS == 0){
		printf("No board for %d queens exists.\n", n);
		return numS;
	}

	return numS;
}

int main(){
	int n;
	int totalSol = 0;
	for(n = 1; n < 10; n++){
		totalSol += solveNQueens(n);
	}

	printf("Total Solutions: %d\n", totalSol);
	return 0;
}

