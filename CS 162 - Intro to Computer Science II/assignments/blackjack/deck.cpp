#include "deck.h"

deck::deck(){
	num_cards = 52;
	cards = new card[num_cards];
	create_deck();
	shuffle();
}

deck::~deck(){
	delete [] cards;
}

void deck::set_cards(card *c){
	delete [] cards;
	cards = c;
}

void deck::set_num_cards(int num){
	num_cards = num;
}

card* deck::get_cards(){
	return cards;
}

int deck::get_num_cards(){
	return num_cards;
}

void deck::create_deck(){
	int i = 0;
	for(i; i < 13; i++){
		cards[i].set_suit("Clubs");
		cards[i].set_value(i+1);
		cards[i].set_type();
	}
	for(i; i < 26; i++){
		cards[i].set_suit("Spades");
		cards[i].set_value(i-12);
		cards[i].set_type();
	}
	for(i; i < 39; i++){
		cards[i].set_suit("Diamonds");
		cards[i].set_value(i-25);
		cards[i].set_type();
	}
	for(i; i < 52; i++){
		cards[i].set_suit("Hearts");
		cards[i].set_value(i-38);
		cards[i].set_type();
	}
}

void deck::shuffle(){
	int rnum;
	card temp;
	for(int x = 0; x < 500; x++){
		for(int i = 1; i < 52; i++){
			rnum = rand() % 11;
			if(rnum <= 9){
				temp = cards[i];
				cards[i] = cards[i-1];
				cards[i-1] = temp;
			}
		}
	}
}

card deck::give_card(){
	for(int i = 0; i < get_num_cards(); i++){
		if(!cards[i].get_given()){
			cards[i].set_given(true);
			return cards[i];
		}
	}
}

void deck::print_deck(){
	for(int i = 0; i < 52; i++){
		cards[i].print_card();
	}	
}
