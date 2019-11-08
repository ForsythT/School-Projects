#include "./mult_div.h"

bool is_valid_dimension(char *rows, char *col){
	for(int i = 0; i < strlen(rows); i++){
		if(rows[i] >= '0' && rows[i] <= '9'){
			if(i == 0){
				if(rows[i] == '0' && rows[i+1] == '\0')
					return false;
			}
			for(int j = 0; j < strlen(col); j++){
				if(col[j] >= '0' && col[j] <= '9'){
					if(j == 0){
						if(col[j] == '0' && col[j+1] == '\0')
							return false;
				else
					return true;
					}
				}
			}
		}
	}
	return false;
}

void print_div_table(mult_div_values **table, int rows, int col){
	
	cout << endl << rows << " x " << col << " Division Table" << endl;
	cout << "-------------------------------" << endl;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < col; j++)
			cout << table[i][j].div << " ";
		cout << endl;
	}
	cout << endl << rows << " x " << col << " Multiplication Table" << endl;
	cout << "-------------------------------" << endl;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < col; j++)
			cout << table[i][j].mult << " ";
		cout << endl;
	}
}

void set_mult_values(mult_div_values **table, int rows, int col){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < col; j++){
			table[i][j].mult = (i+1)*(j+1);
		}
	}
}

void set_div_values(mult_div_values **table, int rows, int col){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < col; j++)
			table[i][j].div = float(i+1)/float(j+1);
	}
}

void delete_table(mult_div_values **table, int col){
	for(int i = 0; i < col; i++)
		delete [] table[i];
	delete [] table;
}

mult_div_values** create_table(int rows, int col){
	mult_div_values** table;
	table = new mult_div_values*[rows];
	for(int i = 0; i < rows; i++){
		table[i] = new mult_div_values[col];
	}
	return table;
}
