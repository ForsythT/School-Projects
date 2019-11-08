#include "room.h"

Room::Room(){
	e = new Empty;
}

Room::~Room(){
	if(e != NULL)
		delete e;
}

void Room::set_event(char eve){
	delete e;
	if(eve == 'w')
		e = new Wumpus;
	else if(eve == 'b')
		e = new Bats;
	else if(eve == 'p')
		e = new Pit;
	else if(eve == 'g')
		e = new Gold;
	else if(eve == 'r')
		e = new Rope;
	else if(eve == 'e')
		e = new Empty;
}

string Room::get_event(){
	return e->get_name();
}

void Room::percept(){
	e->percept();
}

void Room::action(){
	e->action();
}

void Room::set_found(bool f){
	e->set_found(f);
}

bool Room::get_found(){
	return e->get_found();
}
