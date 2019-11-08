#include "bats.h"

class Pit : public Event{
	public:
		Pit();
		void action();
		void percept();
};
