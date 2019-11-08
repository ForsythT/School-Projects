/****************************************************************************************
** Program: state_info.cpp
** Author: Tim Forsyth
** Date: 04/08/2016
** Description: Prints out several facts based on a info in a txt file
** Input: Number of states and a text file
** Output: Prints out facts of the states
****************************************************************************************/

#include "./state_info.h"

/****************************************************************************************
** Function: help
** Description: Prints the help message
** Parameters: None
** Return values: None
** Pre-Conditions: None
** Post-Conditions: Prints help message (none)
****************************************************************************************/

void help(){
	cout << "state_info\t-f\t<FILENAME>\t-s\t<INT>\n\t-s\tNumber of states in the file\n\t-f\tName of the file to read from\n\t-h, --help\tPrint this message\n" << endl;
	exit(0);
}

/****************************************************************************************
** Function: is_valid_arguments
** Description: Checks if command line arguments are valid
** Parameters: char** (argv, the actual command line inputs) and int (argc, how many)
** Return values: Boolean value, but not really needed as if values are not valid, exits
** 		  program
** Pre-Conditions: Argv is a 2d char array and argc is an integer
** Post-Conditions: None
****************************************************************************************/

bool is_valid_arguments(char *argv[], int argc){
	int f = 0, s = 0;
	if(argc < 2){
		cout << "Invalid arguments." << endl;
		help();
	}
	else if(argc == 2){
		if((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0))
			help();
		else{
			cout << "Invalid arguments." << endl;
			help();
		}
	}
	else if(argc == 5){
		for(int i = 1; i < argc-1; i+=2){
			if(strcmp(argv[i], "-f") == 0 && f == 0){
				f++;
				if(is_valid_text_file(argv[i+1]) == true)
					help();
			}
			else if(strcmp(argv[i], "-s") == 0 && s == 0){
				s++;
				if(is_valid_int(argv[i+1], "number of states") == true)
					help();
			}
			else{
				cout << "Invalid arguments." << endl;
				help();
			}
		}
	}
	else{
		cout << "Invalid arguments." << endl;
		help();
	}
	return true;	
}

/****************************************************************************************
** Function: is_valid_text_file
** Description: Checks if it is a valid text file
** Parameters: file name
** Return values: Boolean value
** Pre-Conditions: file name must be a c-style string (char array)
** Post-Conditions: None
****************************************************************************************/

bool is_valid_text_file(char* file){
	ifstream input;
	input.open(file);
	if(input.fail()){
		cout << "Invalid file." << endl;
		return true;
	}
	input.close();
	return false;
}

/****************************************************************************************
** Function: is_valid_int
** Description: Checks if it is a valid int
** Parameters: num to check and the text (for error printing) 
** Return values: Boolean value
** Pre-Conditions: num must be a c-style string (char array)
** Post-Conditions: None
****************************************************************************************/

bool is_valid_int(char* num, string text){
	for(int i = 0; i < strlen(num); i++){
		if(num[i] < '0' || num[i] > '9'){
			cout << "Invalid " << text << "." << endl;
			return true;
		}
	}
	return false;
}

/****************************************************************************************
** Function: create_states
** Description: Creates array of state structs
** Parameters: Num of states
** Return values: Array of state structs
** Pre-Conditions: Num is an int
** Post-Conditions: Return states
****************************************************************************************/

state* create_states(int num){
	state *states;
	states = new state[num];
	return states;
}

/****************************************************************************************
** Function: get_state_data
** Description: Fills structs with data from text file
** Parameters: Array of state structs, num of states, ifstream input
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: Structs are filled
****************************************************************************************/

void get_state_data(state *s, int num, ifstream &input){
	for(int i = 0; i < num; i++){
		input >> s[i].name;
		input >> s[i].pop;
		input >> s[i].counties;
		s[i].c = create_counties(s[i].counties);
		for(int j = 0; j < s[i].counties; j++){
			input >> s[i].c[j].name;
			input >> s[i].c[j].pop;
			input >> s[i].c[j].avg_income;
			input >> s[i].c[j].avg_house;
			input >> s[i].c[j].cities;
			s[i].c[j].city = new string[s[i].c[j].cities];
			for(int k = 0; k < s[i].c[j].cities; k++){
				input >> s[i].c[j].city[k];
			}
		}
	}
}

/****************************************************************************************
** Function: create_counties
** Description: Creates the county structs
** Parameters: int num (number of states)
** Return values: Array of county structs
** Pre-Conditions: Num is an int
** Post-Conditions: Counties structs returned
****************************************************************************************/

county* create_counties(int num){
	county *counties;
	counties = new county[num];
	return counties;
}

/****************************************************************************************
** Function: delete_info
** Description: Deletes and frees up memory used
** Parameters: Array of state structs, int num (number of states)
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: Memory is freed
****************************************************************************************/

void delete_info(state *s, int num){
	for(int i = 0; i < num; i++){
		for(int j = 0; j < s[i].counties; j++){
			delete [] s[i].c[j].city;
		}
		delete [] s[i].c;
	}
	delete [] s;
}

/****************************************************************************************
** Function: largest_state 
** Description: Prints out state with largest pop
** Parameters: Array of state structs, int num (number of states)
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: None
****************************************************************************************/

void largest_state(state *s, int num){
	int large;
	for(int i = 0; i < num; i++){
		if(i == 0)
			large = 0;
		else if(s[i].pop > s[i-1].pop){
			large = i;
		}
	}
	cout << "State with largest population: " << endl; 
	cout << "------------------------------" << endl;
	cout << s[large].name << endl << endl;
}

/****************************************************************************************
** Function: largest_county 
** Description: Prints out county with the largest population
** Parameters: Array of state structs, int num (number of states)
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: None
****************************************************************************************/

void largest_county(state *s, int num){
	int state, county, large = 0;
	for(int i = 0; i < num; i++){
		for(int j = 0; j < s[i].counties; j++){
			if(num == 1 && s[i].counties == 1){
				state = 0;
				county = 0;
			}
			else if(s[i].c[j].pop > large){
				large = s[i].c[j].pop;
				state = i;
				county = j;
			}
		}
	}
	cout << "County with largest population: " << endl;
	cout << "-------------------------------" << endl;
	cout << s[state].c[county].name << endl << endl;
}

/****************************************************************************************
** Function: get_income
** Description: Gets the base income from user
** Parameters: None
** Return values: The base income (float)
** Pre-Conditions: None
** Post-Conditions: Returns float
****************************************************************************************/

float get_income(){
	string income;
	char *incomec;
	float inc;
	bool cont = true;
	while(cont){
		cout << "Enter base income to compare: ";
		cin >> income;
		incomec = change_string(income);
		cont = is_valid_int(incomec, "income");
	}
	inc = atoi(incomec);
	system("clear");
	return inc;
}

/****************************************************************************************
** Function: add_county
** Description: Adds county to array of strings (THIS FUNCTION DOES NOT WORK, I ended up
**		putting it inside of the function check_income because it would seg
**		fault otherwise)
** Parameters: Array of county strings (holds the counties that are above base), int size
**	       (address), int i (which state), int j (which county), Array of state
**	       structs
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: County is added to array of counties
****************************************************************************************/

void add_county(string *counties, int &size, int i, int j, state *s){
	string temp[size];
	for(int x = 0; x < size; x++){
		temp[x] = counties[x];
	}
	delete [] counties;	
	size++;
	counties = new string[size];
	for(int y = 0; y < size-1; y++){
		counties[y] = temp[y];
	}
	counties[size-1] = s[i].c[j].name;
}

/****************************************************************************************
** Function: check_income
** Description: Compares each counties income with a base income given by user
** Parameters: Array of state structs, int num (number of states)
** Return values: None
** Pre-Conditions: Parameters are of their respecitve types
** Post-Conditions: Prints out the counties with an income above the base (none)
****************************************************************************************/

void check_income(state *s, int num){
	int size = 1, first = 0;
	string *counties;
	counties = new string[size];
	counties[size-1] = "None";
	float income = get_income();
	for(int i = 0; i < num; i ++){
		for(int j = 0; j < s[i].counties; j++){
			if(s[i].c[j].avg_income > income && first == 0){
				counties[size-1] = s[i].c[j].name;
				first++;
			}	
			else if(s[i].c[j].avg_income > income){ // I tried to make this a separate function (as you can see the add_county function), but it would seg fault. It works like this.
				string temp[size];
				for(int x = 0; x < size; x++){
					temp[x] = counties[x];
				}
				delete [] counties;	
				size++;
				counties = new string[size];
				for(int y = 0; y < size-1; y++){
					counties[y] = temp[y];
				}
				counties[size-1] = s[i].c[j].name;
			}
		}
	}
	cout << "Counties with income above $" << income << ":" << endl;
	cout << "----------------------------";
	inc(income);
	cout << "-" << endl;
	for(int i = 0; i < size; i++){	
		cout << counties[i] << endl;
	}
	cout << endl;
	delete [] counties;
}

/****************************************************************************************
** Function: inc
** Description: Prints out extra "-" based on length of income
** Parameters: num (income)
** Return values: None
** Pre-Conditions: num is an int
** Post-Conditions: None
****************************************************************************************/

void inc(int num){
	int length = length_num(num);
	for(int i = 0; i < length; i++){
		cout << "-";
	}
}

/****************************************************************************************
** Function: length_num
** Description: Finds the length of a number
** Parameters: int number
** Return values: A number (the length)
** Pre-Conditions: Int number (is an int)
** Post-Conditions: Returns the length as an int
****************************************************************************************/

int length_num(int number){
	int counter = 0;
	while(number){
		number = number/10;
		counter++;
	}
	return counter;
}

/****************************************************************************************
** Function: avg_house_cost
** Description: Finds and prints the avg cost of houses for all counties in each state
**		(state average)
** Parameters: Array of state strcuts, int num (number of states)
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: Average for each state is printed out to screen 
****************************************************************************************/

void avg_house_cost(state *s, int num){
	float total, avg;
	cout << "States average household cost: " << endl;
	cout << "------------------------------" << endl;
	for(int i = 0; i < num; i ++){
		for(int j = 0; j < s[i].counties; j++){
			total += s[i].c[j].avg_house;	
		}
		avg = total/s[i].counties;
		cout << s[i].name << " $" << avg << endl;
		total = 0;
	}
	cout << endl;

}

/****************************************************************************************
** Function: sort_states_name
** Description: Sorts the states by name
** Parameters: Array of state structs, int num (number of states)
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: States are organized by population
****************************************************************************************/

void sort_states_name(state *s, int num){
	state temp;
	bool cont = true;
	while(cont){
		cont = false;
		for(int i = 0; i < num; i++){
			if(i != 0){
				if((s[i].name).compare(s[i-1].name) < (s[i-1].name).compare(s[i].name)){
					temp = s[i];
					s[i] = s[i-1];
					s[i-1] = temp;
					cont = true;
				}
			}	
			sort_counties_name(s, num, i);
		}
	}
	cout << "States and their counties organized by name (A-Z): " << endl;
	cout << "--------------------------------------------------" << endl;
	for(int i = 0; i < num; i++){
		cout << s[i].name << endl;
		for(int j = 0; j < s[i].counties; j++){
			cout << "      " << s[i].c[j].name << endl;
		}
	}
	cout << endl;
}

/****************************************************************************************
** Function: sort_states_pop
** Description: Sorts the states by population
** Parameters: Array of state structs, int num (number of states)
** Return values: None
** Pre-Conditions: Parameters are of their respective types
** Post-Conditions: States are organized by population
****************************************************************************************/

void sort_states_pop(state *s, int num){
	state temp;
	bool cont = true;
	while(cont){
		cont = false;
		for(int i = 0; i < num; i++){
			if(i != 0){
				if(s[i].pop < s[i-1].pop){
					temp = s[i];
					s[i] = s[i-1];
					s[i-1] = temp;
					cont = true;
				}
			}	
			sort_counties_pop(s, num, i);
		}
	}
	cout << "States and their counties organized by population (low to high): " << endl;
	cout << "----------------------------------------------------------------" << endl;
	for(int i = 0; i < num; i++){
		cout << s[i].name << " " << s[i].pop << endl;
		for(int j = 0; j < s[i].counties; j++){
			cout << "      " << s[i].c[j].name << " " << s[i].c[j].pop << endl;
		}
	}
	cout << endl;
}

/****************************************************************************************
** Function: sort_counties_pop
** Description: Sorts the counties by population (low to high)
** Parameters: Array of state structs, int num (number of states), int i (which state)
** Return values: None
** Pre-Conditions: All of the parameters are of their respective types
** Post-Conditions: Counties of the state is organized by population
****************************************************************************************/

void sort_counties_pop(state *s, int num, int i){
	county temp;
	bool cont = true;
	while(cont){
		cont = false;
		for(int j = 0; j < num; j++){
			if(j != 0){
				if(s[i].c[j].pop < s[i].c[j-1].pop){
					temp = s[i].c[j];
					s[i].c[j] = s[i].c[j-1];
					s[i].c[j-1] = temp;
					cont = true;
				}
			}	
		}
	}	
}

/****************************************************************************************
** Function: sort_counties_name
** Description: Sorts the counties by name (a-z)
** Parameters: Array of state structs, int num (number of states), int i (which state)
** Return values: None
** Pre-Conditions: All of the parameters are of their respective types
** Post-Conditions: Counties of the state is organized alphabetically 
****************************************************************************************/

void sort_counties_name(state *s, int num, int i){
	county temp;
	bool cont = true;
	while(cont){
		cont = false;
		for(int j = 0; j < num; j++){
			if(j != 0){
				if((s[i].c[j].name).compare(s[i].c[j-1].name) < (s[i].c[j-1].name).compare(s[i].c[j].name)){
					temp = s[i].c[j];
					s[i].c[j] = s[i].c[j-1];
					s[i].c[j-1] = temp;
					cont = true;
				}
			}	
		}
	}
}

/****************************************************************************************
** Function: start_again
** Description: Asks user if they want to continue/get new stat sheet
** Parameters: None
** Return values: Boolean values
** Pre-Conditions: None
** Post-Conditions: None
****************************************************************************************/

bool start_again(){
	char answer;
	while(true){
		cout << "Do you want to continue with a new text file?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl;
		cin >> answer;
		switch(answer){
			case '1':
				return true;
				break;
			case '2': 
				return false;
				break;
			default:
				cout << "Invalid entry. Try again." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				break;
		}
	}
}

/****************************************************************************************
** Function: change_string
** Description: Changes a string into a c-style string (char*)
** Parameters: A string
** Return values: A c-style string
** Pre-Conditions: The string is a string
** Post-Conditions: A new c-style string is returned
****************************************************************************************/

char* change_string(string str){
	char *newstring = new char[str.size() + 1];
	copy(str.begin(), str.end(), newstring);
	newstring[str.size()] = '\0';
	return newstring;
}

/****************************************************************************************
** Function: get_user_info 
** Description: Gets new text file and num of states from user
** Parameters: address of filename and num to change
** Return values: None
** Pre-Conditions: filename is address of a string and num is an address of an int
** Post-Conditions: filename and num are changed with user values if valid
****************************************************************************************/

void get_user_info(string &filename, int &num){
	string file, numb;
	char *filec, *numbc;
	ifstream input;
	bool cont = true, cont2 = true;
	while(cont){
		cout << "Enter new text file: ";
		cin >> file;
		filec = change_string(file);
		cont = is_valid_text_file(filec);
	}
	while(cont2){
		cout << "Enter number of states: ";
		cin >> numb;
		numbc = change_string(numb);
		cont2 = is_valid_int(numbc, "number of states");
	}
	filename = file;
	num = atoi(numbc);
	delete [] filec;
	delete [] numbc;
}
