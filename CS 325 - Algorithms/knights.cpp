/* Source of code: https://www.geeksforgeeks.org/warnsdorffs-algorithm-knights-tour-problem/ */

#include <bits/stdc++.h>
using namespace std;

// Move pattern on basis of the change of
// x coordinates and y coordinates respectively
static int cx[8] = {1,1,2,2,-1,-1,-2,-2};
static int cy[8] = {2,-2,1,-1,2,-2,1,-1};
 
// function restricts the knight to remain within
// the 8x8 chessboard
bool limits(int x, int y, int n)
{
    return ((x >= 0 && y >= 0) && (x < n && y < n));
}
 
/* Checks whether a square is valid and empty or not */
bool isempty(int a[], int x, int y, int n)
{
    return (limits(x, y, n)) && (a[y*n+x] <= 0);
}
 
/* Returns the number of empty squares adjacent
   to (x, y) */
int getDegree(int a[], int x, int y, int n)
{
    int count = 0;
    for (int i = 0; i < 8; ++i){
        if (isempty(a, (x + cx[i]), (y + cy[i]), n) == true){
            count++;
	}
    }
 
    return count;
}
 
// Picks next point using Warnsdorff's heuristic.
// Returns false if it is not possible to pick
// next point.
bool nextMove(int a[], int *x, int *y, int n)
{
    int min_deg_idx = -1, c, min_deg = 9, nx, ny;
 
    // Try all N adjacent of (*x, *y) starting
    // from a random adjacent. Find the adjacent
    // with minimum degree.
    for (int count = 0; count < 8; count++)
    {
        nx = *x + cx[count];
        ny = *y + cy[count];
        if ((isempty(a, nx, ny, n)) && (c = getDegree(a, nx, ny, n)) < min_deg){
            min_deg_idx = count;
            min_deg = c;
	}
    }


    // IF we could not find a next cell
    if (min_deg_idx == -1)
        return false;
 
    // Store coordinates of next point
    nx = *x + cx[min_deg_idx];
    ny = *y + cy[min_deg_idx];
 
    // Mark next move
    a[ny*n + nx] = a[(*y)*n + (*x)]+1;
 
    // Update next point
    *x = nx;
    *y = ny;
 
    return true;
}
 
/* displays the chessboard with all the
  legal knight's moves */
void print(int a[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%d\t",a[j*n+i]);
        printf("\n");
    }
}
 
/* checks its neighbouring sqaures */
/* If the knight ends on a square that is one
   knight's move from the beginning square,
   then tour is closed */
bool neighbour(int x, int y, int xx, int yy, int n)
{
    for (int i = 0; i < n; ++i)
        if (((x+cx[i]) == xx)&&((y + cy[i]) == yy))
            return true;
 
    return false;
}
 
/* Generates the legal moves using warnsdorff's
  heuristics. Returns false if not possible */
int findTour(int n, int sx, int sy)
{
    // Filling up the chessboard matrix with -1's
    int a[n*n];
    for (int i = 0; i< n*n; ++i)
        a[i] = 0;
 
    // Current points are same as initial points
    int x = sx, y = sy;
    a[y*n+x] = 1; // Mark first move.
 
    // Keep picking next points using
    // Warnsdorff's heuristic
    for (int i = 0; i < n*n-1; ++i)
        if (nextMove(a, &x, &y, n) == 0){
            printf("\n"); 
            printf("Failed to find tour.\nPartial tour:\n");
	    print(a, n);
	    return 0;
	}

    // Check if tour is closed (Can end
    // at starting point)
    if (!neighbour(x, y, sx, sy, n)){
        printf("\n"); 
    	printf("Open tour\n");
	print(a, n);
	return 2;
    }
 
    printf("\n"); 
    printf("Closed tour\n");
    print(a, n);
    return 1;
}
 
// Driver code
int main()
{
    // To make sure that different random
    // initial positions are picked.
    srand(time(NULL));

    int n, x, y;
    printf("n: ");
    cin >> n;
    printf("x: ");
    cin >> x;
    printf("y: ");
    cin >> y;
    
    findTour(n, x, y);
  
    // Used for question numbers 2/3 instead of manually entering the coordinates 25 times
    /*int type, numCT, numOT;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
	    type = findTour(5, i, j);
	    if(type == 1){
	    	numCT++;
	    }
	    else if(type == 2){
	    	numOT++;
	    }
	}
    }

    printf("\nNumber of Closed Tours: %d\nNumber of Open Tours: %d\nTotal Tours: %d\n", numCT, numOT, numCT+numOT);
*/
    return 0;
}
