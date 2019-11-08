#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <climits>
#include <ctype.h>
#include <stdio.h>
#include <cstring>

using namespace std;

class Event{
	string name;
	bool found;
	public:
		Event();
		void set_name(string n);
		string get_name();
		void set_found(bool f);
		bool get_found();
		virtual void action() = 0; //each event action occurs when Jeremy is in the same room
		virtual void percept() = 0; //each event percept occurs when Jeremy is adjacent to their room
		
};
