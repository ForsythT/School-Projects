#include "hand.h"

void hand::set_num_cards_hand(int n){
	num_cards = n;
}

hand::hand(){
	num_cards = 0;
	cards = new card[0];
}

hand::~hand(){
	delete [] cards;
}

hand::hand(const hand &other){
	delete [] cards;
	cards = new card[other.num_cards];
	cards = other.cards;
	num_cards = other.num_cards;
}

void hand::set_cards(card* c){
	delete [] cards;
	cards = new card[2];
	cards = c;
}

void hand::set_num_cards(int n){
	num_cards = n;
}

card* hand::get_cards(){
	return cards;
}

void hand::operator =(const hand &other){
	delete [] cards;
	cards = new card[num_cards];
	cards = other.cards;
	num_cards = other.num_cards;
	
}

void hand::add_card(card c){
	card *temp;
	temp = new card[num_cards];
	for(int i = 0; i < num_cards; i++){
		temp[i].set_suit(cards[i].get_suit());
		temp[i].set_value(cards[i].get_value());
		temp[i].set_given(cards[i].get_given());
		temp[i].set_type();
	}
	delete [] cards;
	set_num_cards_hand(num_cards+1);	
	cards = new card[num_cards];
	for(int i = 0; i < num_cards-1; i++){
		cards[i].set_suit(temp[i].get_suit());
		cards[i].set_value(temp[i].get_value());
		cards[i].set_given(temp[i].get_given());
		cards[i].set_type();
	}
	cards[num_cards-1] = c;
}

void hand::display(){
	for(int i = 0; i < num_cards; i++){
		cards[i].print_card();
	}
}

void hand::display_dealer(){
	cout << "Dealer" << endl;
	cout << "------" << endl;
	cards[0].print_card();
}

bool hand::check_split(){
	if(num_cards == 2 && cards[0].get_type() == cards[1].get_type()){
		return true;
	}
}

int hand::get_num_cards(){
	return num_cards;
}

int hand::get_total(){
	int total = 0;
	while(true){
		for(int i = 0; i < num_cards; i++){
			total += cards[i].get_valuet();
		}
		if(total > 21){
			for(int j = 0; j < num_cards; j++){
				if(cards[j].get_type() == "Ace"){
					cards[j].set_valuet(1);
					break;
				}
			}
		}
		break;
	}
	return total;
}
