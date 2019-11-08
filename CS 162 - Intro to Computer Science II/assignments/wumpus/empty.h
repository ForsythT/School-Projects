#include "event.h"

class Empty : public Event{
	public:
		Empty();
		void action();
		void percept();
};
