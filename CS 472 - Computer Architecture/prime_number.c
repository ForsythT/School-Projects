/*
	Short program to determine whether a provided positive number is prime.
*/
int main() {
	// do not change this section
	// you MUST retain the following two variable names:
	int num = 59;
	int is_prime;
 
	// your code goes in between the following markers
	// <------------->
 	int i;
	is_prime = 1;
	for(i = 2; i < num; i++){ // checks whether n is a multiple of ints between 2 and n
		if(num % i == 0){
			is_prime = 0;
		}
	}
	// <------------->


	// should return 0 if "num" was not prime
	// should return 1 if "num" was prime
	return is_prime;
}
