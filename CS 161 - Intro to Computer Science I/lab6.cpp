/**********************************************************************************
** Program: lab6.cpp
** Author: Tim and Chandler
** Date: 2/17/2016
** Description: Checks if palindrome and can replace strings
** Input: Strings
** Output: Strings
**********************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void get_sentence(string&);
bool determine_palidrome(string);
void result_palindrome(string);
void get_replace_string(string&, int&);
void new_string(string&);
void user_decision(string&, int&);
void check(int&, string&);

/**********************************************************************************
** Function: main
** Description: Calls the other functions
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
**********************************************************************************/

int main(){
	string sentence;
	int count = 1;
	get_sentence(sentence);
	user_decision(sentence, count);
	return 0;
}

/**********************************************************************************
** Function: get_sentence
** Description: Gets a string from user
** Parameters: string address 
** Pre-Conditions: Parameter is a string
** Post-Conditions: Change string
**********************************************************************************/

void get_sentence(string &str){
	cout << "Enter a string: ";
	getline(cin, str);
}

/**********************************************************************************
** Function: determine_palindrome
** Description: Determines if string is a palindrome
** Parameters: string
** Pre-Conditions: parameter is string
** Post-Conditions: returns boolean value
**********************************************************************************/

bool determine_palindrome(string str){
	int len;
	len = str.length() - 1;	
	for(int i = 0; i != len; i++){
		if (str[i] == str[len]){
			if (len == 0)
				return true;
		}
		else
			return false;
		len = len - 1;	
	}
	return true;
}

/**********************************************************************************
** Function: result_palindrome
** Description: Prints out message if it is or is not a palindrome
** Parameters: string
** Pre-Conditions: parameter is string
** Post-Conditions: None
**********************************************************************************/

void result_palindrome(string str){
	if (determine_palindrome(str) == true)
		cout << "It is a palindrome!" << endl;
	else if (determine_palindrome(str) == false)
		cout << "It is not a palindrome!" << endl;
}

/**********************************************************************************
** Function: get_replace_string
** Description: gets replacement strings from user and replaces in string
** Parameters: string address, int address
** Pre-Conditions: parameter is string and int
** Post-Conditions: Edits string
**********************************************************************************/

void get_replace_string(string &str, int &count){
	string search, replacement, edit;
	int position;
	cout << "Enter a search string: ";
	getline(cin.ignore(), search);
	check(count, search);
	position = str.find(search);
	cout << "Enter the replacement: ";
	getline(cin, replacement);
	edit = str.replace(position, search.length(), replacement);
	cout << "You made " << count << " replacement(s), and your new string is: " << edit << endl;
}

/**********************************************************************************
** Function: check
** Description: checks for number of spaces in string
** Parameters: int address, string address
** Pre-Conditions: int and string
** Post-Conditions: change count value
**********************************************************************************/

void check(int &count, string &str){
	for(int i = 0; i < str.length(); i++){
		if(str[i] == ' ')
			count++;
	}	
}

/**********************************************************************************
** Function: new_string
** Description: Gets new string from user
** Parameters: String address
** Pre-Conditions: parameter is a string
** Post-Conditions: Replaces old string with new string
**********************************************************************************/

void new_string(string &str){
	cin.ignore();
	get_sentence(str);
	cout << "Your new string is " << str << endl;
}

/**********************************************************************************
** Function: user_decision
** Description: Calls function based on user response
** Parameters: string address, int address
** Pre-Conditions: parameters are string and int
** Post-Conditions: None
**********************************************************************************/

void user_decision(string &str, int &count){
	int answer;
	while(true){
		cout << "Do you want to: " << endl;
		cout << "Determine if palindrome (1), replace string (2), enter new string (3), or quit (0)?" << endl;
		cin >> answer;
		switch(answer){
			case 0:{ 
				exit(0);	
			}
			case 1:{
				result_palindrome(str);
				break;	
			}
			case 2:{
				get_replace_string(str, count);
				break;
			}
			case 3:{
				new_string(str);
				break;	
			}
			default:{
				cout << "Invalid option." << endl;	
			}
		}	
	}
}
