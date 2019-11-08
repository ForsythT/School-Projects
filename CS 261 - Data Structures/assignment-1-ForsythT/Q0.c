/* CS261- Assignment 1 - Q. 0*/
/* Name: Tim Forsyth
 * Date: 9/28/2016
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int fooB(int* a, int* b, int c) {
	c = *a + *b;
	*b = *a;
	*b = *b * 2;
	return c;
}

void fooA(int* iptr){
	printf("Value pointed to: %d\n", *iptr);
	printf("Address of x: %p\n", iptr);
	printf("Address of iptr: %p\n", &iptr);
}

int main(){

	/* declare an integer x */
	int x = 5;
	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	int c;
	*a = 10;
	*b = 5;
	c = 0;
	printf("Value of a: %d\n", *a);
	printf("Value of b: %d\n", *b);
	printf("Value of c: %d\n", c);
	c = fooB(a, b, c);
	printf("New a value: %d\nNew b value: %d\nNew c value: %d\n", *a, *b, c);
  
  	/* print the address of x */
	printf("Address of x: %p\n", &x);
    
  	/* Call fooA() with the address of x */
	fooA(&x);
    
  	/* print the value of x */
	printf("Value of x: %d\n", x);
	free(a);
	free(b);
  	return 0;
}


