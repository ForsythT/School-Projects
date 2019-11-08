/* By: Tim Forsyth
 * For: CS 472 HW 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]){
	// Get the command line arguments as integers
	int va_width = atoi(argv[1]);
	int pa_width = atoi(argv[2]);
	int mem_page_bits = log2(atoi(argv[3]));
	// Calculate physical page number bit size
	int phys_page_num = va_width - mem_page_bits;
	// Calculate how many entries on a page table
	int num_entries = pow(2, phys_page_num);
	// Calculate how many bits in each page table entry
	int bits_per_entry = pa_width + 3;
	// Final page table size calculation
	int size = num_entries * bits_per_entry;
	printf("Full page table requires %i bits.\n", size);
	return 0;
}
