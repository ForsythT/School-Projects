#include "game.h"

bool is_pos_int(char*);

int main(int argc, char *argv[]){
	int s;
	srand(time(NULL));
	if(argc > 3){
		cout << "Invalid arguments." << endl;
		cout << "argc" << endl;
		exit(0);
	}
	cout << argc << endl;
	if(strcmp(argv[1],"-s") == false){
		if(is_pos_int(argv[2]) == false){
			cout << "Invalid size." << endl;
			cout << "not int" << endl;
			exit(0);
		}
		else{
			s = atoi(argv[2]);
		}
	}
	else{
		cout << "Invalid arguments." << endl;
		cout << "you stupid" << endl;
		exit(0);
	}

	Game g;
	g.set_size(s);
	g.play_game();
}

bool is_pos_int(char *value){
	for(int i = 0; i < strlen(value); i++){
		if(!(value[i] >= '0' && value[i] <= '9')){
			return false;
		}
		if(i == 0 && value[i] <= '3'){
			return false;
		}
	}
	return true;
}
