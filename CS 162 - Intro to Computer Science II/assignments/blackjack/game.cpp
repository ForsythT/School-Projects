#include "game.h"

game::game(){
	count = 1;
	cards = cards;
	players = new player[num_players];
	game_dealer = game_dealer;
	num_players = 0;
}

game::~game(){
	delete [] players;
}

void game::set_num_players(int n){
	num_players = n;
}

int game::get_num_players(){
	return num_players;
}

bool game::is_valid_int(int num){
	if(num <= 0){
		cout << "Invalid int, try again." << endl;
		return true;
	}
	return false;
}

void game::get_info(){
	int p, b;
	bool cont = true, cont2 = true;
	if(count == 1){
		while(cont){
			cout << "How many players are there? ";
			cin >> p;
			cont = is_valid_int(p);
		}
		set_num_players(p);
		for(int i = 0; i < get_num_players(); i++){
			cont2 = true;
			while(cont2){
				cout << "Player " << i+1 << ", enter your starting balance: ";
				cin >> b;
				cont2 = is_valid_int(b);
			}
			players[i].set_playing_total(b);
		}
	}
	get_bets();
}

void game::get_bets(){
	int b;
	bool cont = true;
	for(int i = 0; i < get_num_players(); i++){
		cont = true;
		while(cont){
			cout << "Player " << i+1 << ", enter your bet: ";
			cin >> b;
			cont = is_valid_int(b);
		}
		players[i].set_bet(b);
	}
}

void game::start_game(){
	system("clear");
	get_info();
	system("clear");
	deal();
	for(int i = 0; i < num_players; i++){
		show_player_hand(i);
		cout << endl;
	}
	deal_dealer();
	peek_dealer();
	player_turn();
	dealer_turn();
	check_win();
	reset();
	count++;
}

void game::reset(){
	player *play;
	dealer deal;
	game_dealer = deal;
	play = new player[num_players];
	for(int i = 0; i < num_players; i++){
		play[i].set_playing_total(players[i].get_playing_total());
		players[i] = play[i];
	}
}

bool game::restart_game(){
	char answer;
	while(true){
		cout << "Do you want to play again?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl;
		cin >> answer;
		switch(answer){
			case '1':
				return true;
				break;
			case '2': 
				return false;
				break;
			default:
				cout << "Invalid entry. Try again." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				break;
		}
	}
}

void game::peek_dealer(){
	if(game_dealer.get_card_total() == 21){
		cout << "Dealer has Blackjack! Better luck next time." << endl;
	}
}

void game::set_win(int i){
	if(players[i].get_card_total() < 21 && players[i].get_num_cards() == 2){
		players[i].set_playing_total(players[i].get_playing_total() + players[i].get_bet());
	}
}

void game::set_loss(int i){
	if(players[i].get_card_total() < 21){
		players[i].set_playing_total(players[i].get_playing_total() - players[i].get_bet());
	}
	cout << "Playing Total: " << players[i].get_playing_total() << endl << endl;
}

void game::check_win(){
	int winners = 0;
	for(int i = 0; i < num_players; i++){
		if(players[i].get_card_total() == game_dealer.get_card_total()){
			cout << "Player " << i+1 << " pushes." << endl;
			cout << "Playing Total: " << players[i].get_playing_total() << endl;
		}
		else if(players[i].get_card_total() >= game_dealer.get_card_total() && players[i].get_card_total() <= 21 || game_dealer.get_card_total() > 21 && players[i].get_card_total() <= 21){
			cout << "Player " << i+1 << " wins!" << endl;
			winners++;
			set_win(i);
			cout << "Playing Total: " << players[i].get_playing_total() << endl;
		}
		else{
			cout << "Player " << i+1 << " loses." << endl;
			set_loss(i);
		}
	}
	if(winners > 0){
		cout << "Congratulations to the winners!" << endl;
	}
	else if(winners == 0){
		cout << "Better luck next time." << endl;
	}
}

void game::deal(){
	for(int i = 0; i < num_players; i++){
		for(int j = 0; j < 2; j++ ){
			players[i].add_card(cards.give_card());
		}
	}
}

void game::deal_dealer(){
	for(int i = 0; i < 2; i++){
		game_dealer.add_card(cards.give_card());
	}
	game_dealer.show_top();
	cout << endl;
}

void game::show_player_hand(int i){
	cout << "Player " << i+1 << " - Playing Total: " << players[i].get_playing_total() << " - Current Bet: " << players[i].get_bet() << endl;
	cout << "---------" << endl;
	players[i].show_hand();
	cout << "(" << players[i].get_card_total() << ")" << endl;	
}

void game::help(int i){
	cout << endl << "1 - Hit: Get another card\n2 - Stand: End turn\n3 - Double Down: Double your bet, get one card and end your turn" << endl;
	cout << "4 - Help: Prints this message" << endl << endl;
}

void game::dealer_turn(){
	while(true){
		if(game_dealer.get_card_total() == 21){
			cout << "Dealer wins!" << endl << endl;
			break;
		}
		else if(game_dealer.get_card_total() >= 17 && game_dealer.get_card_total() <= 21){	
			break;
		}
		else if(game_dealer.get_card_total() >= 21){
			cout << "Dealer busts!" << endl << endl;
			break;
		}
		else{
			game_dealer.add_card(cards.give_card());
		}
	}
	game_dealer.show_hand();
	cout << "(" << game_dealer.get_card_total() << ")" << endl;
	cout << endl;
}

void game::player_action(char choice, int i){
	switch(choice){
		case '1':
			players[i].add_card(cards.give_card());
			break;
		case '2':
			players[i].set_turn(false);
			break;
		case '3':
			players[i].set_bet((players[i].get_bet())*2);
			players[i].add_card(cards.give_card());
			players[i].set_turn(false);
			if(players[i].check_hand(i) == true){
				show_player_hand(i);
				cout << endl;
			}
			break;
		case '4':
			help(i);
			break;
		default:
			cout << "Invalid entry. Try again." << endl;
	}
}

void game::player_turn(){
	char choice;
	for(int i = 0; i < get_num_players(); i++){
		players[i].set_turn(true);
		while(players[i].get_turn()){
			if(players[i].check_hand(i) == false){
				break;
			}
			show_player_hand(i);
			cout << "Player " << i+1 << ", what would you like to do?" << endl;
			cout << "1 - Hit" << endl;
			cout << "2 - Stand" << endl;
			cout << "3 - Double Down" << endl;
			cout << "4 - Help" << endl;
			cin >> choice;
			cout << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			player_action(choice, i);
		}
	}
}
