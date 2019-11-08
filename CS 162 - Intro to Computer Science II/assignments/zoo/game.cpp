#include "game.h"

Game::Game(){
	z = z;
}

void Game::shop(){
	char c;
	bool exit = false;
	while(!exit){
		cout << "Welcome to the zoo shop. Choose what you would like to do." << endl;
		cout << "1 - Buy Animals\n2 - Buy Feed\n0 - Exit Shop" << endl;
		cin >> c;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		exit = z.shop(c);		
	}
}

void Game::get_info(){
	char c;
	bool good = false;
	while(!good){
		cout << "Welcome to Zoo Tycoon! Please choose a starting balance for your zoo." << endl;
		cout << "1 - $100,000 (Beginner)\n2 - $50,000 (Average)\n3 - $20,000 (Expert)\n4 - $5,000 (Insane)" << endl;
		cin >> c;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		good = set_balance(c);
	}
}

bool Game::set_balance(char c){
	switch(c){
		case '1':
			z.set_bank(100000);
			break;
		case '2':
			z.set_bank(50000);
			break;
		case '3':
			z.set_bank(20000);
			break;
		case '4':
			z.set_bank(5000);
			break;
		default: 
			cout << "Invalid entry." << endl;
			return false;
	}
	return true;
}

void Game::play_game(){
	bool cont = true;
	while(cont){
		cont = day();
	}
}

bool Game::day(){
	if(z.get_day_num() == 1){
		system("clear");
		get_info();
		player_decision();
		z.set_day_num(z.get_day_num()+1);	
		return true;
	}
	z.set_num_tavail(2);
	z.set_num_pbavail(2);
	z.set_num_mavail(2);
	z.set_num_pavail(2);
	z.set_tbonus(false);
	z.age_animals();
	if(z.feed_animals() == false){
		z.bankrupt();
		return false;
	}
	else{
		system("clear");
		cout << "Day " << z.get_day_num() << endl;
		random_event();
		z.check_sick();
		z.payoff();
		z.print_info();
		player_decision();
	}
	z.set_day_num(z.get_day_num()+1);	
	return true;
}

void Game::player_decision(){
	char c, c2;
	bool next = false;
	int num_a;
	while(!next){
		num_a = z.get_num_t() + z.get_num_pb() + z.get_num_m() + z.get_num_p();
		cout << "What would you like to do?" << endl;
		cout << "1 - Open Shop" << endl;
		if(num_a > 0){
			cout << "2 - Continue to Next Day" << endl;
			cout << "0 - Exit Game" << endl;
			cin >> c;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			switch(c){
				case '1':
					shop();
					break;
				case '2':
					next = true;
					break;
				case '0':
					cout << "Are you sure you would like to quit the game, losing all progress? (y or n) ";
					cin >> c2;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					switch(c2){
						case 'y':
							exit(0);
						case 'n':
							next = false;
							break;
						default:
							cout << "Invalid entry." << endl;
					}
				default:
					cout << "Invalid entry." << endl;
			}
		}
		else{
			cout << "0 - Exit Game" << endl;
			cin >> c;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			switch(c){
				case '1':
					shop();
					break;
				case '0':
					cout << "Are you sure you would like to quit the game, losing all progress? (y or n) ";
					cin >> c2;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					switch(c2){
						case 'y':
							exit(0);
						case 'n':
							next = false;
							break;
						default:
							cout << "Invalid entry." << endl;
					}
				default:
					cout << "Invalid entry." << endl;
			}
		}
	}
}

void Game::random_event(){
	int rnum;
	bool cont = true;
	while(cont){
		rnum = rand() % 10;
		if(z.get_feed_type() == 'g'){
			if(rnum >= 2 && rnum <= 4){
				cout << "sick" << endl;
				z.sick();
				cont = false;
			}
			else if(rnum == 6){
				cout << "bonus" << endl;
				z.set_tbonus(true);
				cont = false;
			}
			else if(rnum == 9){
				cout << "pregnant" << endl;
				z.pregnant();
				cont = false;
			}
			else{
				cout << "nothing" << endl;
				cont = false;
			}
		}
		else if(z.get_feed_type() == 'c'){
			if(rnum >= 0 && rnum <= 5){
				z.sick();
				cont = false;
			}
			else if(rnum == 6){
				z.set_tbonus(true);
				cont = false;
			}
			else if(rnum == 8){
				z.pregnant();
				cont = false;
			}
			else 
				cont = false;
		}
		else if(z.get_feed_type() == 'p'){
			if(rnum == 5 || rnum == 4){
				z.sick();
				cont = false;
			}
			else if(rnum == 6){
				z.set_tbonus(true);
				cont = false;
			}
			else if(rnum == 8){
				z.pregnant();
				cont = false;
			}
			else 
				cont = false;
		}
	}
}
