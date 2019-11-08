#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

class Animal{
	string name;
	char gender;
	int age;
	float cost;
	float feed_cost;
	int profit;
	bool sick;
	int days_sick;
	public:
		Animal();
		Animal(const string, const char, const int, const float, const float, const int, const bool, const int);
		string get_name();
		char get_gender();
		int get_age();
		float get_cost();
		float get_feed_cost();
		int get_profit();
		bool get_sick();
		int get_days_sick();
		void set_name(const string);
		void set_gender(const char);
		void set_age(const int);
		void set_cost(const float);
		void set_feed_cost(const float);
		void set_profit(const int);
		void set_sick(bool);
		void set_days_sick(int);
};
