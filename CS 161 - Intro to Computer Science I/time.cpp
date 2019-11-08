#include <iostream>
#include <sys/time.h> 
#include <cstdlib> 

using namespace std;

int get_input();
int fib_iter(int);
int fib_recurs(int);

int main() {      
	typedef struct timeval time;      
	time stop, start;       
	int n, iter, recurs;

	n = get_input();

	gettimeofday(&start, NULL);      
	//Time your iterative or recursive function here.

	iter = fib_iter(n);
	cout << iter << endl;

     	gettimeofday(&stop, NULL);      
	
	if(stop.tv_sec > start.tv_sec)         
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;      
	else         
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;     
	
	gettimeofday(&start, NULL);      
	//Time your iterative or recursive function here.

	recurs = fib_recurs(n);
	cout << recurs << endl;

     	gettimeofday(&stop, NULL);      
	
	if(stop.tv_sec > start.tv_sec)         
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;      
	else         
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;     

	return 0;
}

int get_input(){	
	int n;
	cout << "Enter a number: ";
	cin >> n;
	return n;
}

int fib_iter(int n){
	int first = 0, second = 1, next;
	for(int i = 1; i < n; i++){
		next = first + second;
		first = second;
		second = next;
	}

	if (n == 1)
		return 1;
	else if (n == 0)
		return 0;
	return next;
}

int fib_recurs(int n){
	int x, value;
	if(n >= 2){
		value = fib_recurs(n-1) + fib_recurs(n-2);
	}
	else if (n == 1)
		return 1;
	else 
		return 0;
	
	return value;
}


