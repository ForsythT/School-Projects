#include "player.h"

player::player(){
	p_hand = p_hand;
	bet = 0;
	playing_total = 0;
	card_total = 0;
	turn = false;
}

player::player(const player &other){
	p_hand = other.p_hand;
	bet = other.bet;
	playing_total = other.playing_total;
	card_total = other.card_total;
}

player::~player(){
}

void player::operator =(const player &other){
	p_hand = other.p_hand;
	bet = other.bet;
	playing_total = other.playing_total;
	card_total = other.card_total;
}

void player::set_bet(int b){
	bet = b;
}

void player::set_p_hand(hand p){
	p_hand = p;
}

void player::set_playing_total(int p){
	playing_total = p;
}

void player::set_card_total(int c){
	card_total = c;
}

void player::set_turn(bool t){
	turn = t;
}

hand player::get_p_hand(){
	return p_hand;
}

int player::get_bet(){
	return bet;
}

int  player::get_playing_total(){
	return playing_total;
}

int player::get_card_total(){
	card_total = p_hand.get_total();
	return card_total;
}

bool player::get_turn(){
	return turn;
}

void player::add_card(card c){
	p_hand.add_card(c);
}

void player::show_hand(){
	p_hand.display();
}

bool player::check_split(){
	if(p_hand.check_split() == true){
		return true;
	}
}

void player::blackjack(){
	if(p_hand.get_num_cards() == 2){
		cout << "For a Blackjack, you get 1.5x your bet in reward." << endl;
		set_playing_total((get_bet()*1.5) + get_playing_total());
	}
	else
		set_playing_total((get_bet() + get_playing_total()));
	cout << "Playing Total: " << get_playing_total() << endl;
}

void player::set_loss(){
	set_playing_total(get_playing_total() - get_bet());
	cout << "Playing Total: " << get_playing_total() << endl;
}

int player::get_num_cards(){
	int p = p_hand.get_num_cards();
	return p;
}

bool player::check_hand(int i){
	if(get_card_total() == 21){	
		cout << "Player " << i+1 << "- Current Bet: " << get_bet() << endl;
		cout << "---------" << endl;
		show_hand();
		cout << "Congratulations! You got 21!" << endl;
		blackjack();
		return false;	
	}
	else if(get_card_total() > 21){
		cout << "Player " << i+1 << "- Current Bet: " << get_bet() << endl;
		cout << "---------" << endl;
		show_hand();
		cout << "Oh no! You've busted. :(" << endl;
		set_loss();
		return false;
	}
	return true;
}
