#include "rope.h"

Rope::Rope(){
	set_name("R");
}

void Rope::action(){
	cout << "You have successfully made it back to your escape rope with the Wumpus dead and the golden idol in your possession. \nYou climb back up the escape rope to safety." << endl;	
}

void Rope::percept(){
	cout << "You're back at your escape rope, but your mission is yet to be complete. You continue on." << endl;
}
