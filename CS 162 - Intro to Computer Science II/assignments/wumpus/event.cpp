#include "event.h"


Event::Event(){
	name = " ";
	found = false;
}

void Event::set_name(string n){
	name = n;	
}

string Event::get_name(){
	return name;
}

void Event::set_found(bool f){
	found = f;
}

bool Event::get_found(){
	return found;
}
