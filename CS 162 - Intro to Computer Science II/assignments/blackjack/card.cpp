#include "card.h"

card::card(){
	valuet = 0;
	value = 0;
	type = " ";
	suit = " ";
	given = false;
}

void card::set_value(int v){
	value = v;
}

void card::set_valuet(int v){
	valuet = v;
}


void card::set_suit(string s){
	suit = s;
}

void card::set_given(bool g){
	given = g;
}

card::card(const card &other){
	value = other.value;
	valuet = other.valuet;
	type = other.type;
	suit = other.suit;
	given = other.given;
}

void card::operator =(const card &other){
	value = other.value;
	valuet = other.valuet;
	type = other.type;
	suit = other.suit;
	given = other.given;
}

void card::set_type(){
	ostringstream sin;
	string t;
	if(get_value() <= 10 && get_value() != 1){
		sin << get_value();
		t = sin.str();
		type = t;
		set_valuet(get_value());
	}
	else if(get_value() == 1){
		t = "Ace";
		type = t;
		set_valuet(11);
	}
	else if(get_value() == 11){
		t = "Jack";
		type = t;
		set_valuet(10);
	}
	else if(get_value() == 12){
		t = "Queen";
		type = t;
		set_valuet(10);
	}
	else{
		t = "King";
		type = t;
		set_valuet(10);
	}
}

int card::get_value(){
	return value;
}

int card::get_valuet(){
	return valuet;
}

string card::get_suit(){
	return suit;
}

string card::get_type(){
	return type;
}

bool card::get_given(){
	return given;
}

void card::print_card(){
	cout << get_type() << " of " << get_suit() << endl;
}
