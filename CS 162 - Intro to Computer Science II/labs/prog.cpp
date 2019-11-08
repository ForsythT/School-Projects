#include "./mult_div.h"

int main(int argc, char *argv[]){
	int rows, col;
	if(is_valid_dimension(argv[1], argv[2]) == 1){
		rows = atoi(argv[1]);
		col = atoi(argv[2]);
	}
	else{
		cout << "Invalid arguments." << endl;
		exit(0);
	}

	mult_div_values** table = create_table(rows, col);

	set_mult_values(table, rows, col);
	set_div_values(table, rows, col);
	print_div_table(table, rows, col);
	delete_table(table, col);
	return 0;
}
