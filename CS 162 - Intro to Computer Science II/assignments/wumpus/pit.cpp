#include "pit.h"

Pit::Pit(){
	set_name("P");
}

void Pit::action(){
	cout << "You hear a crack and then suddenly the ground breaks beneath you and you fall to your death." << endl;
}

void Pit::percept(){
	cout << "You feel a breeze." << endl;
}
