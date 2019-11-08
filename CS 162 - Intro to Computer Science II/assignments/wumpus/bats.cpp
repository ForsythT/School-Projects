#include "bats.h"

Bats::Bats(){
	set_name("BAT");
}

void Bats::action(){
	cout << "The flapping gets louder and then 2 large bats swoop down from the roof of the caves and grabs you and flys away. \nYou struggle and manage to break free of their grasp, but notice a change in scenery." << endl;
}

void Bats::percept(){
	if(get_found() == false)
		cout << "You hear wings flapping." << endl;
}
