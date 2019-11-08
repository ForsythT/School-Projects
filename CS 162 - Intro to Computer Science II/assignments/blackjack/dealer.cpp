#include "dealer.h"

dealer::dealer(){
	d_hand = d_hand;
}

dealer::dealer(const dealer &other){
	d_hand = other.d_hand;
	card_total = other.card_total;
}

dealer::~dealer(){

}

void dealer::operator =(const dealer &other){
	d_hand = other.d_hand;
	card_total = other.card_total;
}

void dealer::show_top(){
	d_hand.display_dealer();
	cout << "???" << endl;
}

void dealer::show_hand(){
	cout << "Dealer" << endl;
	cout << "------" << endl;
	d_hand.display();
}

void dealer::add_card(card c){
	d_hand.add_card(c);
}

int dealer::get_card_total(){
	int card_total = d_hand.get_total();
	return card_total;
}
