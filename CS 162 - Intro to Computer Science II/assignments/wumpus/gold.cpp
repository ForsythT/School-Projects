#include "gold.h"

Gold::Gold(){
	set_name("$$$");
}

void Gold::action(){
	if(get_found() == false)
		cout << "Your face lights up as you realize what you've stumbled across, the legendary treasure of the Wumpus. \nYou pick up the golden idol and place it in your backpack." << endl;
}

void Gold::percept(){
	if(get_found() == false)
		cout << "You see a glimmer nearby." << endl;
}
