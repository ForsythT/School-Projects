#include "game.h"

Game::Game(){
	cave = NULL;
	size = 5;
	dead = false;
	move = false;
}

Game::~Game(){
	if(cave != NULL){
		for(int i = 0; i < size; i++){
			delete [] cave[i];
		}
		delete [] cave;
	}
}

void Game::set_size(int s){
	size = s;
}

int Game::get_size(){
	return size;
}

void Game::win(){
	cout << "Congratulations! You won!\nIt took you " << jeremy.get_num_moves() << " moves to kill the Wumpus, find the gold, and escape." << endl;
}

void Game::play_game(){
	bool alive = true, same = false, cont;
	char c;
	cont = true;
	while(cont){
		if(same == false)
			create_cave();
		cout << "Welcome to Hunt the Wumpus!\nYour mission is to find and kill the Wumpus and collect the legenday treasure hidden within his home." << endl;
		while(alive){
			system("clear");
			print_cave();
			alive = check_rooms();
			if(alive == true)
				player_turn();
		}
		if(jeremy.get_gold() == true && jeremy.get_wumpus() == true && jeremy.get_alive() == true)
			win();
		c = restart();
		if(c == 's'){
			same = true;
			cont = true;
			reset();
			alive = true;
		}
		else if(c == 'n'){
			same = false;	
			cont = true;
			reset();
			alive = true;
		}
		else
			cont = false;
	}
}

void Game::reset(){
	int x, y;
	jeremy.set_wumpus(false);
	jeremy.set_gold(false);
	jeremy.set_arrows(3);
	jeremy.set_num_moves(0);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			cave[i][j].set_found(false);
			if(cave[i][j].get_event() == "R"){
				x = i;
				y = j;
			}
		}
	}
	jeremy.set_x(x);
	jeremy.set_y(y);
	dead = false;
	move = false;
}

char Game::restart(){
	char ans;
	while(true){
		cout << "Do you want to play again?" << endl;
		cout << "1 - Yes (Same Map)\n2 - Yes (New Map)\n3 - No" << endl;
		cin >> ans;
		cin.ignore(INT_MAX, '\n');
		switch(ans){
			case '1':
				return 's';
				break;
			case '2':
				return 'n';
				break;
			case '3':
				return 0;
			default:
				cout << "Invalid entry." << endl;
		}
	}
}

void Game::create_cave(){
	if(cave != NULL){
		for(int i = 0; i < size; i++)
			delete [] cave[i];
		delete [] cave;
	}
	cave = new Room*[size];
	for(int i = 0; i < size; i++){
		cave[i] = new Room[size];
	}
	set_events();
	place_jeremy();
}

void Game::place_jeremy(){
	int rnum, rnum2, p, count = 1;
	p = 0;
	while(count != 0){
		rnum = rand() % size;
		rnum2 = rand() % size;
		if(cave[rnum][rnum2].get_event() == " " && p == 0){
			jeremy.set_x(rnum2);
			jeremy.set_y(rnum);
			cave[rnum][rnum2].set_event('r');
			p = 1;
			cout << "Placed Jeremy" << endl;
			cout << jeremy.get_x() << " " << jeremy.get_y() << endl;
			count = 0;
		}
	}
}

void Game::set_events(){
	int rnum, rnum2, rnum3, w, b, p, g, count;
	w = 0;
	b = 0;
	p = 0;
	g = 0;
	count = 0;
	while(count < 6){
		rnum = rand() % size;
		rnum2 = rand() % size;
		rnum3 = rand() % 4;
		if(rnum3 == 0){
			if(cave[rnum][rnum2].get_event() == " " && w < 1){
				cave[rnum][rnum2].set_event('w');
				w++;
				count++;
			}
		}
		else if(rnum3 == 1){
			if(cave[rnum][rnum2].get_event() == " " && b < 2){
				cave[rnum][rnum2].set_event('b');
				b++;
				count++;
			}
		}
		else if(rnum3 == 2){
			if(cave[rnum][rnum2].get_event() == " " && p < 2){
				cave[rnum][rnum2].set_event('p');
				p++;
				count++;
			}
		}
		else if(rnum3 == 3){
			if(cave[rnum][rnum2].get_event() == " " && g < 1){
				cave[rnum][rnum2].set_event('g');
				g++;
				count++;
			}
		}	
	}
}

void Game::print_cave(){
	for(int i = size-1; i >= 0; i--){
		for(int j = 0; j < size; j++){
			if(j == 0)
				cout << "| ";
			if(jeremy.get_x() == j && jeremy.get_y() == i){
				cout << "YOU";
			}
			else if(cave[i][j].get_found() == true && cave[i][j].get_event() != "W")
				cout << cave[i][j].get_event();
			else
				cout << "   ";
			cout << " | ";
		}
		cout << endl;
	}
}

void Game::shoot_north(){
	int rnum, count = 0;
	for(int i = jeremy.get_y()+1; i < size; i++){
		count++;
		if(cave[i][jeremy.get_x()].get_event() == "W"){
			wumpus_death();
			jeremy.set_wumpus(true);
			dead = true;
		}
		if(count > 2)
			break;
	}
	if(jeremy.get_wumpus() == false){
		cout << "You missed!" << endl;
		rnum = rand() % 10;
		if(rnum != 0 && rnum != 1 && rnum != 2){
			wumpus_move();
		}
	}
	jeremy.set_arrows(jeremy.get_arrows()-1);
}

void Game::shoot_south(){
	int rnum, count = 0;
	for(int i = jeremy.get_y()-1; i >= 0; i--){
		if(cave[i][jeremy.get_x()].get_event() == "W"){
			wumpus_death();
			jeremy.set_wumpus(true);
			dead = true;
		}
		if(count > 2)
			break;
	}
	if(jeremy.get_wumpus() == false){
		cout << "You missed!" << endl;
		rnum = rand() % 10;
		if(rnum != 0 && rnum != 1 && rnum != 2){
			wumpus_move();
		}
	}
	jeremy.set_arrows(jeremy.get_arrows()-1);
}

void Game::shoot_east(){
	int rnum, count = 0;
	for(int i = jeremy.get_x()+1; i < size; i++){
		count++;
		if(cave[jeremy.get_y()][i].get_event() == "W"){
			wumpus_death();
			jeremy.set_wumpus(true);
			dead = true;
		}
		if(count > 2)
			break;
	}
	if(jeremy.get_wumpus() == false){
		cout << "You missed!" << endl;
		rnum = rand() % 10;
		if(rnum != 0 && rnum != 1 && rnum != 2){
			wumpus_move();
		}
	}
	jeremy.set_arrows(jeremy.get_arrows()-1);
}

void Game::shoot_west(){
	int rnum, count = 0;
	for(int i = jeremy.get_x()-1; i >= 0; i--){
		count++;
		if(cave[jeremy.get_y()][i].get_event() == "W"){
			cout << "You have slain the Wumpus!" << endl;
			wumpus_death();
			jeremy.set_wumpus(true);
			dead = true;
		}
		if(count > 2)
			break;
	}
	if(jeremy.get_wumpus() == false){
		cout << "You missed!" << endl;
		rnum = rand() % 10;
		if(rnum != 0 && rnum != 1 && rnum != 2){
			wumpus_move();
		}
	}
	jeremy.set_arrows(jeremy.get_arrows()-1);
}

void Game::wumpus_move(){
	int rnum, rnum2;
	rnum = rand() % size;
	rnum2 = rand() % size;
	move = true;
	if(cave[rnum][rnum2].get_event() == " "){
		wumpus_death();
		cave[rnum][rnum2].set_event('w');
	}
}

void Game::wumpus_death(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(cave[i][j].get_event() == "W"){
				cave[i][j].set_found(true);
			}
		}
	}
}

void Game::player_turn(){
	char direction, action;
	bool cont = true;
	action = player_choice();
	action = tolower(action);
	while(cont){
		direction = player_direction();
		direction = tolower(direction);
		switch(direction){
			case 'n':
				if(jeremy.get_y() < size-1){
					if(action == 'm'){
						jeremy.move_north();
						jeremy.set_num_moves(jeremy.get_num_moves()+1);
					}
					else if(action == 's')
						shoot_north();
					cont = false;
					break;
				}
				cout << "Invalid entry." << endl;       
				break;
			case 's':
				if(jeremy.get_y() > 0){
					if(action == 'm'){
						jeremy.move_south();
						jeremy.set_num_moves(jeremy.get_num_moves()+1);
					}
					else if(action == 's')
						shoot_south();
					cont = false;
					break;
				}
				cout << "Invalid entry." << endl;    
				break;	
			case 'e':
				if(jeremy.get_x() < size-1){
					if(action == 'm'){
						jeremy.move_east();
						jeremy.set_num_moves(jeremy.get_num_moves()+1);
					}
					else if(action == 's')
						shoot_east();
					cont = false;
					break;
				}
				cout << "Invalid entry." << endl;       
				break;
			case 'w':
				if(jeremy.get_x() > 0){
					if(action == 'm'){
						jeremy.move_west();
						jeremy.set_num_moves(jeremy.get_num_moves()+1);
					}
					else if(action == 's')
						shoot_west();
					cont = false;
					break;
				}
				cout << "Invalid entry." << endl;       
				break;
			default:
				cout << "Invalid entry." << endl;       
		}
	}
}

char Game::player_choice(){
	char choice;
	bool cont = true;
	while(cont){
		cout << "Do something:" << endl;
		cout << "(M)ove" << endl;
		if(jeremy.get_arrows() > 0)
			cout << "(S)hoot Bow" << endl;
		cin >> choice;
		cin.ignore(INT_MAX, '\n');
		switch(choice){
			case 'm':
				cont = false;
				break;
			case 's':
				if(jeremy.get_arrows() > 0){
					cont = false;
					break;
				}
				else
					cout << "You're out of arrows." << endl;
				break;
			default:
				cout << "Invalid entry." << endl;
		}
	}
	return choice;
}

char Game::player_direction(){
	char direction;
	cout << "Which direction:" << endl;
	if(jeremy.get_y() < size-1)
		cout << "(N)orth" << endl;
	if(jeremy.get_y() > 0)
		cout << "(S)outh" << endl;
	if(jeremy.get_x() < size-1)
		cout << "(E)ast" << endl;
	if(jeremy.get_x() > 0)
		cout << "(W)est" << endl;
	cin >> direction;
	cin.ignore(INT_MAX, '\n');
	return direction;
}

void Game::jeremy_move(){
	int rnum, rnum2;
	bool cont = true;
	while(cont){
		rnum = rand() % size;
		rnum2 = rand() % size;
		if(rnum != jeremy.get_y() && rnum2 != jeremy.get_x() && cave[rnum][rnum2].get_event() != "B"){
			jeremy.set_y(rnum);
			jeremy.set_x(rnum2);
			cont = false;
		}
	}
	print_cave();
}

bool Game::check_rooms(){
	if(dead == true)
		cout << "You have slain the Wumpus!" << endl;
	else if(dead == false && move == true){
		cout << "The Wumpus has ran away and moved to a new room." << endl;
		move = false;
	}
	if(jeremy.get_arrows() == 0 && dead == false){
		cout << "You ran out of arrows and the Wumpus has not been slain! You lose." << endl;
		return false;
	}
	if(cave[jeremy.get_y()][jeremy.get_x()].get_event() == "BAT"){
		system("clear");
		cave[jeremy.get_y()][jeremy.get_x()].action();
		cave[jeremy.get_y()][jeremy.get_x()].set_found(true);	
		jeremy_move();
	}
	if(cave[jeremy.get_y()][jeremy.get_x()].get_event() == "R"){
		if(jeremy.get_gold() == true && jeremy.get_wumpus() == true){
			cave[jeremy.get_y()][jeremy.get_x()].action();
			return false;
		}
		else if(jeremy.get_num_moves() > 0)
			cave[jeremy.get_y()][jeremy.get_x()].percept();
	}
	if(cave[jeremy.get_y()][jeremy.get_x()].get_event() == "$$$"){
		cave[jeremy.get_y()][jeremy.get_x()].action();
		cave[jeremy.get_y()][jeremy.get_x()].set_found(true);	
		jeremy.set_gold(true);	
	}
	if(cave[jeremy.get_y()][jeremy.get_x()].get_event() == "P"){
		cave[jeremy.get_y()][jeremy.get_x()].action();
		jeremy.set_alive(false);
		return false;
	}
	if(cave[jeremy.get_y()][jeremy.get_x()].get_event() == "W"){
		cave[jeremy.get_y()][jeremy.get_x()].action();
		if(cave[jeremy.get_y()][jeremy.get_x()].get_found() == false){
			jeremy.set_alive(false);
			return false;
		}
	}
	if(jeremy.get_y() < size-1)
		if(cave[jeremy.get_y()+1][jeremy.get_x()].get_event() != "R")
			cave[jeremy.get_y()+1][jeremy.get_x()].percept();
	if(jeremy.get_y() > 0)
		if(cave[jeremy.get_y()-1][jeremy.get_x()].get_event() != "R")
			cave[jeremy.get_y()-1][jeremy.get_x()].percept();
	if(jeremy.get_x() < size-1)
		if(cave[jeremy.get_y()][jeremy.get_x()+1].get_event() != "R")
			cave[jeremy.get_y()][jeremy.get_x()+1].percept();
	if(jeremy.get_x() > 0)
		if(cave[jeremy.get_y()][jeremy.get_x()-1].get_event() != "R")
			cave[jeremy.get_y()][jeremy.get_x()-1].percept();
	return true;
}
