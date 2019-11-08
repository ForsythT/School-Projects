#include "player.h"

class Room{
	Event *e;
	public:
		Room();
		~Room();
		void set_event(char eve);
		string get_event();
		void percept();
		void action();
		void set_found(bool f);
		bool get_found();
};
