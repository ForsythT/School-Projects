#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <cstring>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

class card{
	int value;
	int valuet;
	string type;
	string suit;
	bool given;
	public:
		card();
		void set_value(int);
		void set_suit(string);
		void set_valuet(int);
		void set_type();
		card(const card&);
		void operator =(const card&);
		void set_given(bool);
		int get_valuet();
		int get_value();
		void print_card();
		string get_suit();
		string get_type();
		bool get_given();
};
