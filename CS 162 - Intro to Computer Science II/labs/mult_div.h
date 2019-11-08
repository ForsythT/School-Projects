#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct mult_div_values{
	int mult;
	float div;
};

bool is_valid_dimension(char* rows, char* col);
mult_div_values** create_table(int rows, int col);
void set_div_values(mult_div_values **table, int rows, int col);
void set_mult_values(mult_div_values **table, int rows, int col);
void print_div_table(mult_div_values **table, int rows, int col);
void delete_table(mult_div_values **table, int col);
