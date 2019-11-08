#include "pit.h"

class Gold : public Event{
	public:
		Gold();
		void action();
		void percept();
};
