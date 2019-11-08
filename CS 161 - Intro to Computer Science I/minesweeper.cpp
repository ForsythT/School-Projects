#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <limits>

using namespace std;

bool is_pos_int(char*);
bool is_pos_inte(char);
void empty_board(char**, int, int);
void place_mines(int, int, int, char**);
void place_numbers(int, int, char**);
void print_board(char**, int, int);
void count_mines_top(int, int, int, int, int&, char**);
void count_mines_bot(int, int, int, int, int&, char**);
void player_choice(int, int, char**, char**);
void flag_cell(int, int, int, int, char**);
void open_cell(int, int, int, int, char**, char**, bool&);
void get_coord(int&, int&, int, int);
bool check_cell(char**, int, int);
bool win_conditions(int, int, char**, char**);
void open_cell_recursion_bot(int, int, int, int, char**, char**, bool&);
void open_cell_recursion_top(int, int, int, int, char**, char**, bool&);
void won_game(char**, int, int);
void get_rows_cols_mines(int&, int&, int&);
bool play_again();
bool check_cell_open(char**, int x, int y);
void game_setup(int, int, int, char**, char**);

int main(int argc, char *argv[]){
	int rows = 0, cols = 0, mines = 0;
	char **mineboard, **playerboard;
	
	srand(time(NULL));
	if(argc != 7){
		cout << "usage: incorrect number of arguments" << endl;
		exit(1);
	}
	for(int i = 1; i < argc - 1; i++){
		if(strcmp(argv[i], "-r") == 0){
			if(is_pos_int(argv[i+1]) == true && rows == 0){
				rows = atoi(argv[i+1]);
			}
			else{
				cout << "usage: invalid row input" << endl;
				exit(1);
			}
		}
		else if(strcmp(argv[i], "-c") == 0){
			if(is_pos_int(argv[i+1]) == true && cols == 0){
				cols = atoi(argv[i+1]);
			}
			else{
				cout << "usage: invalid collumn input" << endl;
				exit(1);
			}
		}
		else if(strcmp(argv[i], "-m") == 0){
			if(is_pos_int(argv[i+1]) == true && mines == 0){
				mines = atoi(argv[i+1]);
			}
			else{
				cout << "usage: invalid mine input" << endl;
				exit(1);
			}
		}
	}
	game_setup(rows, cols, mines, mineboard, playerboard);
}

void game_setup(int rows, int cols, int mines, char **mineboard, char **playerboard){
	bool cont = true;
	while(cont == true){
		mineboard = new char*[rows];
		for(int i = 0; i < rows; i++){
			mineboard[i] = new char[cols];
		}
		playerboard = new char*[rows];
		for(int i = 0; i < rows; i++){
			playerboard[i] = new char[cols];
		}
		empty_board(playerboard, rows, cols);
		place_mines(rows, cols, mines, mineboard);
		place_numbers(rows, cols, mineboard);
		player_choice(rows, cols, playerboard, mineboard);
		for(int i = 0; i < rows; i++){
			delete []mineboard[i];
			delete []playerboard[i];
		}
		delete []mineboard;
		delete []playerboard;
		cont = play_again();
		if(cont == true){
			get_rows_cols_mines(rows, cols, mines);
		}
	}
}

void get_rows_cols_mines(int &rows, int &cols, int &mines){
	int x, y, z;
	while(true){
		cout << "How many rows? ";
		cin >> x;
		if(x > 0){
			rows = x;
			break;
		}
		else{
			cout << "Invalid input, must be greater than 0." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	while(true){
		cout << "How many cols? ";
		cin >> y;
		if(y > 0){
			cols = y;
			break;
		}
		else{
			cout << "Invalid input, must be greater than 0." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	while(true){	
		cout << "How many mines? ";
		cin >> z;
		if(z > 0){
			mines = z;
			break;
		}
		else{
			cout << "Invalid input, must be greater than 0." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

void player_choice(int rows, int cols, char **board, char **mineboard){
	char ans;
	int x = 1, y = 1;
	bool win = false, lose = false;
	while(win == false && lose == false){
		print_board(board, rows, cols);
		cout << "Flag(1) or Open(2): ";
		cin >> ans;
		switch(ans){
			case '1':
				flag_cell(rows, cols, x, y, board);
				break;
			case '2':
				get_coord(x, y, rows, cols);
				open_cell(rows, cols, x, y, board, mineboard, lose);
				win = win_conditions(rows, cols, mineboard, board);
				break;
			default:
				cout << "Invalid input. Enter 1 or 2." << endl;
		}
	}
}	

bool play_again(){
	char ans;	
	cout << "Do you want to play again? (1 - yes, 2 - no): ";
	cin >> ans;
	switch(ans){
		case '1':
			return true;
			break;
		case '2':
			return false;
			break;
		default:
			cout << "Invalid input. Enter 1 or 2." << endl;
	}
}

void empty_board(char **board, int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			board[i][j] = ' ';
		}
	}
}

bool is_pos_int(char *value){
	for(int i = 0; i < strlen(value); i++){
		if(!(value[i] >= '0' && value[i] <= '9')){
			return false;
		}
	}
	return true;
}

void place_mines(int rows, int cols, int mines, char **mineboard){
	int rnum, cnum, minecounter = 0;
	while(minecounter < mines){
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				rnum = rand()%rows;
				if(mineboard[i][j] != '*'){
					if(minecounter < mines){
						if(rnum == 1){
							mineboard[i][j] = '*';
							minecounter++;
						}
						else
							mineboard[i][j] = '0';
					}
					else{
							mineboard[i][j] = '0';
					}
			
				}
			}
		}	
	}
}

void place_numbers(int rows, int cols, char **mineboard){
	int minecounter;
	char c;
  	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			minecounter = 0;
			count_mines_top(i, j, rows, cols, minecounter, mineboard);
			count_mines_bot(i, j, rows, cols, minecounter, mineboard);
		}
	}
}


void count_mines_top(int i, int j, int rows, int cols, int &minecounter, char **mineboard){	
	if(mineboard[i][j] != '*'){
		if((i-1) >= 0){
			if(mineboard[i-1][j] == '*')
				minecounter++;
			if((j-1) >= 0){
				if(mineboard[i-1][j-1] == '*')
					minecounter++;
			}
			if((j+1) < cols){
				if(mineboard[i-1][j+1] == '*')
					minecounter++;
			}
		}
		if((j-1) >= 0){
			if(mineboard[i][j-1] == '*')
					minecounter++;
		}
	}
}

void count_mines_bot(int i, int j, int rows, int cols, int &minecounter, char **mineboard){
	if(mineboard[i][j] != '*'){	
		if((i+1) < rows){
			if(mineboard[i+1][j] == '*')
				minecounter++;
			if((j-1) >= 0){
				if(mineboard[i+1][j-1] == '*')
					minecounter++;
			}	
			if((j+1) < cols){		
				if(mineboard[i+1][j+1] == '*')
					minecounter++;	
			}
		}
		if((j+1) < cols){
			if(mineboard[i][j+1] == '*')
				minecounter++;
		}
		mineboard[i][j] = minecounter+48;
	}	
}

void open_cell_recursion_top(int rows, int cols, int i, int j, char **board, char **mineboard, bool &lose){
	if((i-1) >= 0){
		if(mineboard[i-1][j] != '*' && board[i-1][j] == ' ')
			open_cell(rows, cols, i-1, j, board, mineboard, lose);
		if((j-1) >= 0){
			if(mineboard[i-1][j-1] != '*' && board[i-1][j-1] == ' ')
				open_cell(rows, cols, i-1, j-1, board, mineboard, lose);
		}
		if((j+1) < cols){
			if(mineboard[i-1][j+1] != '*' && board[i-1][j+1] == ' ')
				open_cell(rows, cols, i-1, j+1, board, mineboard, lose);
		}
	}
	if((j-1) >= 0){
		if(mineboard[i][j-1] != '*' && board[i][j-1] == ' ')
			open_cell(rows, cols, i, j-1, board, mineboard, lose);
	}
}

void open_cell_recursion_bot(int rows, int cols, int i, int j, char **board, char **mineboard, bool &lose){
	if((i+1) < rows){
		if(mineboard[i+1][j] != '*' && board[i+1][j] == ' ')
			open_cell(rows, cols, i+1, j, board, mineboard, lose);
		if((j-1) >= 0){
			if(mineboard[i+1][j-1] != '*' && board[i+1][j-1] == ' ')
				open_cell(rows, cols, i+1, j-1, board, mineboard, lose);
		}	
		if((j+1) < cols){		
			if(mineboard[i+1][j+1] != '*' && board[i+1][j+1] == ' ')
				open_cell(rows, cols, i+1, j+1, board, mineboard, lose);
		}
	}
	if((j+1) < cols){
		if(mineboard[i][j+1] != '*' && board[i][j+1] == ' ')
			open_cell(rows, cols, i, j+1, board, mineboard, lose);
	}	
}

void print_board(char **board, int rows, int cols){
	for(int i = 0; i < rows; i++){
		cout << "  ";
		for(int x = 0; x < cols; x++){
			cout << "--"; 
		}
		cout << "-" << endl;
		if(i+1 > 9)
			cout << i+1;
		else
			cout << i+1 << " ";
		for(int j = 0; j < cols; j++){
			cout << "|";
			cout << board[i][j];
			if(j == cols - 1)
				cout << "|";
		}
		cout << endl;
	}
	cout << "  ";
	for(int x = 0; x < cols; x++){
		cout << "--"; 
	}
	cout << "-" << endl;
	cout << "   ";
	for(int x = 0; x < cols; x++){
		cout << x+1 << " "; 
	}
	cout << endl;
}

void get_coord(int &x, int &y, int rows, int cols){
	while(true){
		cout << "Rows: ";
		cin >> x;
		if(x <= rows && x >= 1 && y % 1 == 0){
			x--;
			break;
		}
		else{
			cout << "Out of range (1 to " << rows << ")" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	while(true){
		cout << "Cols: ";
		cin >> y;
		if(y <= cols && y >= 1 && y % 1 == 0){
			y--;
			break;	
		}
		else{
			cout << "Out of range (1 to " << cols << ")" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

bool check_cell(char **board, int x, int y){
	if(board[x][y] != ' ')
		return false;
	else
		return true;
}

bool check_cell_open(char **board, int x, int y){
	if(board[x][y] != ' ' && board[x][y] != '!')
		return false;
	else
		return true;
}

void flag_cell(int rows, int cols, int x, int y, char **board){
	while(true){
		get_coord(x, y, rows, cols);
		if(check_cell(board, x, y) == true){
			board[x][y] = '!';
			break;		
		}
		else
			cout << "You've already flagged or opened this cell. Try again." << endl;
	}
}

void open_cell(int rows, int cols, int x, int y, char **board, char **minefield, bool &lose){
	if(check_cell_open(board, x, y) == true){
		if(minefield[x][y] == '*'){
			cout << "BOOM!" << endl;
			print_board(minefield, rows, cols);
			cout << "You lose!" << endl;
			lose = true;
		}
		else if(minefield[x][y] == '0'){
			board[x][y] = minefield[x][y];
			open_cell_recursion_top(rows, cols, x, y, board, minefield, lose);
			open_cell_recursion_bot(rows, cols, x, y, board, minefield, lose);
		}
		else
			board[x][y] = minefield[x][y];
	}
}

bool win_conditions(int rows, int cols, char **mineboard, char **board){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(mineboard[i][j] != '*'){
	if(mineboard[i][j] == board[i][j])
					continue;
				else
					return false;

			}
		}
	}
	cout << "Congratulations!" << endl;
	print_board(mineboard, rows, cols);
	return true;
}
