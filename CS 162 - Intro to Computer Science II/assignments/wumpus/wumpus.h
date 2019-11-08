#include "empty.h"

class Wumpus : public Event{
	public:
		Wumpus();
		void action();
		void move();
		void die();
		void percept();
};
