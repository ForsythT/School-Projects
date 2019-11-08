#include "wumpus.h"

Wumpus::Wumpus(){
	set_name("W");
}

void Wumpus::action(){
	if(get_found() == false)
		cout << "You hear a low growl and within a second a giant beast is on top of you. You struggle for your life, but the Wumpus is too powerful and eats you alive." << endl;
}

void Wumpus::percept(){
	if(get_found() == false)	
		cout << "You smell a terrible stench." << endl;
}
