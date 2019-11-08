#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <string>
#include <climits>

using namespace std;

struct county{
	string name;
	string *city;
	int cities;
	int pop;
	float avg_income;
	float avg_house;
};

struct state{
	string name;
	struct county *c;
	int counties;
	int pop;
};

void help();
bool is_valid_arguments(char*[], int);
bool is_valid_text_file(char*);
bool is_valid_int(char*, string);
state* create_states(int);
void get_state_data(state*, int, ifstream&);
county* create_counties(int);
void get_county_data(county*, int, ifstream&);
void delete_info(state*, int);
void largest_state(state*, int);
void largest_county(state*, int);
float get_income();
void add_county(string*, int&, int, int, state*);
void check_income(state*, int);
void avg_house_cost(state*, int);
void sort_states_name(state*, int);
void sort_states_pop(state*, int);
void sort_counties_name(state*, int, int);
void sort_counties_pop(state*, int, int);
void inc(int);
int length_num(int);
bool start_again();
char* change_string(string);
void get_user_info(string&, int&);
