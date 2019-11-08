#include "randomizationInterface.h"
unsigned long getRandom(unsigned long min, unsigned long max){

	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned long returnValue;
	char vendor[13];
	
	eax = 0x01;

	__asm__ __volatile__(
	                     "cpuid;"
	                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	                     : "a"(eax)
	                     );
	
	if(ecx & 0x40000000){
		//use rdrand
		//printf("Using rdrand\n");
		returnValue = genRDrand(min, max);
	}
	else{
		//use mt19937
		//printf("Using MT\n");
		unsigned int buffer;
		int fd = open("/dev/urandom", O_RDONLY);
		read(fd, &buffer, 4);
		close(fd);
		init_genrand(buffer); /* a default initial seed is used */
		returnValue = genrand(min, max);
	}

	return returnValue;
}
// int main(){
// 	getRandom();
// 	return 0;
// }
