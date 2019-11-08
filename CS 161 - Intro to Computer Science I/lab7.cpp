/**********************************************************************************
** Program: lab6.cpp
** Author: Tim and Chandler
** Date: 2/17/2016
** Description: Checks if palindrome and can replace strings
** Input: Strings
** Output: Strings
**********************************************************************************/

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

void get_sentence(char*);
void print(char *str);
bool recursive(char *str, char *replace, char *search, int &i, int &n);
bool determine_palidrome(char*);
void result_palindrome(char*);
void get_search_replace_strings(char*, char*, char*);
int search_replace(char*, char*, char*);
void new_string(char*);
void user_decision(char*);
//void check(int&, string&);

/**********************************************************************************
** Function: main
** Description: Calls the other functions
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None
**********************************************************************************/

int main(){
	char sentence[256];
	get_sentence(sentence);
	user_decision(sentence);
	return 0;
}

/**********************************************************************************
** Function: get_sentence
** Description: Gets a string from user
** Parameters: string address 
** Pre-Conditions: Parameter is a string
** Post-Conditions: Change string
**********************************************************************************/

void get_sentence(char *str){
	cout << "Enter a string: ";
	cin.getline(str, 256);
}

/**********************************************************************************
** Function: determine_palindrome
** Description: Determines if string is a palindrome
** Parameters: string
** Pre-Conditions: parameter is string
** Post-Conditions: returns boolean value
**********************************************************************************/

bool determine_palindrome(char *str){
	int len;
	len = strlen(str) - 1;	
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

void result_palindrome(char *str){
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

void get_search_replace_strings(char *str, char *search, char *replace){
	cout << "Enter a search string: ";
	cin.ignore();
	cin.getline(search, 256);
	cout << "Enter the replacement string: ";
	cin.getline(replace, 256);
	search_replace(str, replace, search);
}

bool recursive(char *str, char *replace, char *search){
	int i = 0, n = 0;
	for(i; i < strlen(str); i++){
		if(str[i] == search[n]){
			if(search[n])
			n++;
			if(search[n] == '\0')
				return true;
		}	
		else if(search[n] == '\0'){
			return true;
		}
	}
	if(str[i] != search[n])
		return false;
}

int search_replace(char *str, char *replace, char *search){
	char *pch;
	bool check;
	check = recursive(str, replace, search);
	pch = strstr(str, search);
	strncpy(pch, replace, strlen(replace)); //strlen(search)
	cout << "Your new string is: " << str << endl;
}

/**********************************************************************************
** Function: new_string
** Description: Gets new string from user
** Parameters: String address
** Pre-Conditions: parameter is a string
** Post-Conditions: Replaces old string with new string
**********************************************************************************/

void new_string(char *str){
	cin.ignore();
	get_sentence(str);
	cout << "Your new string is ";
	print(str);
}

void print(char *str){
	for(int i = 0; i < strlen(str); i++){
		cout << str[i];
	}
	cout << endl;
}

/**********************************************************************************
** Function: user_decision
** Description: Calls function based on user response
** Parameters: string address, int address
** Pre-Conditions: parameters are string and int
** Post-Conditions: None
**********************************************************************************/

void user_decision(char *str){
	int answer;
	char search[256], replace[256];
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
				get_search_replace_strings(str, search, replace);
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
