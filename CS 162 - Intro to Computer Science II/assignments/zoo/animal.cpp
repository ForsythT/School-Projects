#include "animal.h"

Animal::Animal(){
	name = " ";
	gender = ' ';
	age = 3;
	cost = 1000;
	feed_cost = 10;
	profit = 50;
	sick = false;
	days_sick = 0;
}

Animal::Animal(const string n, const char g, const int a, const float c, const float f, const int p, const bool s, const int d){
	name = n;
	gender = g;
	age = a;
	cost = c;
	feed_cost = f;
	profit = p;
	sick = s;
	days_sick = d;
}

string Animal::get_name(){
	return name;
}

char Animal::get_gender(){
	return gender;
}

int Animal::get_age(){
	return age;
}

float Animal::get_cost(){
	return cost;
}

float Animal::get_feed_cost(){
	return feed_cost;
}

int Animal::get_profit(){
	return profit;
}

bool Animal::get_sick(){
	return sick;
}

int Animal::get_days_sick(){
	return days_sick;
}

void Animal::set_name(string const n){
	name = n;
}

void Animal::set_gender(const char g){
	gender = g;
}

void Animal::set_age(const int a){
	age = a;
}

void Animal::set_cost(const float c){
	cost = c;
}

void Animal::set_feed_cost(const float f){
	feed_cost = f;
}

void Animal::set_profit(const int p){
	profit = p;
}

void Animal::set_sick(bool s){
	sick = s;
}

void Animal::set_days_sick(int s){
	days_sick = s;
}
