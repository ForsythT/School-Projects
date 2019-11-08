/**************************************************************************
** Program Name: rover.cpp
** Author: Tim Forsyth
** Date: 1/31/2016
** Description: Finds and prints the path that the rover needs to take 
**		based on the starting and ending x and y coordinates the
**		user inputs
** Input: Starting and ending x, y coordinates and yes/no (end of program)
** Output: Prints the path that the rover needs to take to reach the end
**         coordinates from the starting coordinates
**************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string convert(string s);
void print_topbot();
void print_grid(string row1, string row2, string row3, string row4);
void find_path(int xStart, int yStart, int xEnd, int yEnd);
bool check_int(string s);
bool restart();

/**************************************************************************
** Function: main
** Description: Main function of the program that calls other functions.
**		Also gets the starting and ending x, y coordinates and 
**		changes them from strings to ints with atoi after they have 
**		been checked
** Parameters: None
** Return: None
** Pre-Conditions: None
** Post-Conditions: Program will have ran as many times as user wished to
**************************************************************************/

int main(){
	bool check;
	do{	
		string xStarting, yStarting, xEnding, yEnding;
		int unum, xStart, yStart, xEnd, yEnd;
		cout << "Starting X coordinate: ";
		cin >> xStarting;
		while(!check_int(xStarting) || (unum = atoi(xStarting.c_str())) > 3){
			cout << "Out of range. Try again: ";
			cin >> xStarting;
		}
		cout << "Starting Y coordinate: ";
		cin >> yStarting;
		while(!check_int(yStarting) || (unum = atoi(yStarting.c_str())) > 3){
			cout << "Out of range. Try again: ";
			cin >> yStarting;
		}
		cout << "Ending X coordinate: ";
		cin >> xEnding;
		while(!check_int(xEnding) || (unum = atoi(xEnding.c_str())) > 3){
			cout << "Out of range. Try again: ";
			cin >> xEnding;
		}
		cout << "Ending Y coordinate: ";
		cin >> yEnding;
		while(!check_int(yEnding) || (unum = atoi(yEnding.c_str())) > 3){
			cout << "Out of range. Try again: ";
			cin >> yEnding;
		}
		xStart = atoi(xStarting.c_str());
		yStart = atoi(yStarting.c_str());
		xEnd = atoi(xEnding.c_str());
		yEnd = atoi(yEnding.c_str());
		find_path(xStart, yStart, xEnd, yEnd);
		check = restart();
	}while(check);
	return 0;
}

/**************************************************************************
** Function: find_path
** Description: Finds the path from the starting position to the ending
**		position, also prints the path by way of calling print_grid
** Parameters: 4 ints; xStart, yStart, xEnd, yEnd
** Return: None
** Pre-Conditions: The parameters are all valid ints
** Post-Conditions: Parameters remain unchanged, path will be printed
**************************************************************************/

void find_path(int xStart, int yStart, int xEnd, int yEnd){
	string row1, row2, row3, row4;
	int horizontal, vertical, i, x, val1, val3, val5;
	horizontal = xEnd - xStart; 			//how much it needs to move left/right from starting point
	vertical = yEnd - yStart; 			//how much it needs to move up/down from starting point
	
	row1 = row2 = row3 = row4 = "| | | | |";	 //starts empty
	
	if(yStart == 0){ 				//since y value is in columns, its harder to 'edit' a string compared to x values that are all in one row, or one string
		if(xStart ==0){ 			//depending on the value of x, some variables change
			x = 1; 				//the starting point of x based on the rows char. Each row is a string containing 9 characters, 
							//and the spaces are chars 1,3,5,7 row ex: "|1|3|5|7|" 
			 			
			val1 = 0;			//how many spaces to go to char 1, these vals are different possibilities depending on ending x, y coordinates
		 	val3 = 1;			//how many spaces to go to char 3
			val5 = 2;			//how many spaces to go to char 5
			row1.at(x) = 'X'; 		//starts are row1 because y = 0, as y goes up, it will be row2, row3, row4
			print_grid(row1, row2, row3, row4); 
							//notice no 7, there is only one left possibility for xEnd - xStart (from the range of 0-3), so it is left as else
		}
		else if(xStart == 1){			 //else if statements are for if x is 1, 2, or 3
			x = 3;
			val1 = -1;
			val3 = 0;
			val5 = 1;
			row1.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 2){
			x = 5;
			val1 = -2;
			val3 = -1;
			val5 = 0;
			row1.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 3){
			x = 7;
			val1 = -3;
			val3 = -2;
			val5 = -1;
			row1.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		for(i = 0; i < horizontal; i++){ 	//x value is much easier since it's horizontal, so 2 for loops can used (neg and pos or left and right)
			x += 2; 			//+2 because the spaces are every other char
			row1.at(x) = 'X'; 		//replaces the space with an 'X' at the correct location
			print_grid(row1, row2, row3, row4); //print_grid inside the loop so it prints every step
		}
		for(i = 0; i > horizontal; i--){ 	//same as first loop except negative, small changes
			x -= 2; 			//-2 instead of + because negative horizontal value
			row1.at(x) = 'X';
			print_grid(row1, row2, row3, row4);	
		}		
		if(horizontal == val1){  						//each if/else if statements check if the calculated horizontal value is equal to
			if(vertical >= 1){						//the value needed to get to a certain coordinate in the grid (char value 1,3,5,7)
				row2.at(1) = 'X';					//If it matches, then it goes on the figuring out the y value and how much it needs
				print_grid(row1, row2, row3, row4);			//to print. It goes in order depending on the starting y value so it will print in the
				if(vertical >= 2){					//correct order. Similarly to the x values, it replaces the space with an 'X' depending on
					row3.at(1) = 'X';				//which column it is in.
					print_grid(row1, row2, row3, row4);		//
					if(vertical >= 3){				//It will continue to do this for each val(1,3,5; 7 = else statement)
						row4.at(1) = 'X';			//There are 4 of these chunks of code (1 for each possible starting y value) that differ
						print_grid(row1, row2, row3, row4);	//slightly, such as y values 1 and 2 needing both positive and negative vertical options
					}
				}
			}
		}
		else if(horizontal == val3){
			if(vertical >= 1){
				row2.at(3) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical >= 2){
					row3.at(3) = 'X';
					print_grid(row1, row2, row3, row4);
					if(vertical >= 3){
						row4.at(3) = 'X';
						print_grid(row1, row2, row3, row4);
					}
				}
			}
		}
		else if(horizontal == val5){
			if(vertical >= 1){
				row2.at(5) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical >= 2){
					row3.at(5) = 'X';
					print_grid(row1, row2, row3, row4);
					if(vertical >= 3){
						row4.at(5) = 'X';
						print_grid(row1, row2, row3, row4);
					}
				}
			}
		}
		else{
			if(vertical >= 1){
				row2.at(7) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical >= 2){
					row3.at(7) = 'X';
					print_grid(row1, row2, row3, row4);
					if(vertical >= 3){
						row4.at(7) = 'X';
						print_grid(row1, row2, row3, row4);
					}
				}	
			}	
		}
	}
	if(yStart == 1){
		if(xStart ==0){
			x = 1;
			val1 = 0;
			val3 = 1;
			val5 = 2;
			row2.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 1){
			x = 3;
			val1 = -1;
			val3 = 0;
			val5 = 1;
			row2.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 2){
			x = 5;
			val1 = -2;
			val3 = -1;
			val5 = 0;
			row2.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 3){
			x = 7;
			val1 = -3;
			val3 = -2;
			val5 = -1;
			row2.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		for(i = 0; i < horizontal; i++){
			x += 2;
			row2.at(x) = 'X';
			print_grid(row1, row2, row3, row4);	
		}
		for(i = 0; i > horizontal; i--){
			x -= 2;
			row2.at(x) = 'X';
			print_grid(row1, row2, row3, row4);	
		}		
		if(horizontal == val1){  
			if(vertical >= 1){
				row3.at(1) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical >= 2){
					row4.at(1) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
			else if(vertical <= -1){
				row1.at(1) = 'X';
				print_grid(row1, row2, row3, row4);
			}	
		}
		else if(horizontal == val3){  
			if(vertical >= 1){
				row3.at(3) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical >= 2){
					row4.at(3) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
			else if(vertical <= -1){
				row1.at(3) = 'X';
				print_grid(row1, row2, row3, row4);
			}	
		}
		else if(horizontal == val5){  
			if(vertical >= 1){
				row3.at(5) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical >= 2){
					row4.at(5) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
			else if(vertical <= -1){
				row1.at(5) = 'X';
				print_grid(row1, row2, row3, row4);
			}	
		}
		else{  
			if(vertical >= 1){
				row3.at(7) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical >= 2){
					row4.at(7) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
			else if(vertical <= -1){
				row1.at(7) = 'X';
				print_grid(row1, row2, row3, row4);
			}	
		}
	}
	if(yStart == 2){
		if(xStart ==0){
			x = 1;
			val1 = 0;
			val3 = 1;
			val5 = 2;
			row3.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 1){
			x = 3;
			val1 = -1;
			val3 = 0;
			val5 = 1;
			row3.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 2){
			x = 5;
			val1 = -2;
			val3 = -1;
			val5 = 0;
			row3.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 3){
			x = 7;
			val1 = -3;
			val3 = -2;
			val5 = -1;
			row3.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		for(i = 0; i < horizontal; i++){
			x += 2;
			row3.at(x) = 'X';
			print_grid(row1, row2, row3, row4);	
		}
		for(i = 0; i > horizontal; i--){
			x -= 2;
			row3.at(x) = 'X';
			print_grid(row1, row2, row3, row4);	
		}		
		if(horizontal == val1){  
			if(vertical >= 1){
				row4.at(1) = 'X';
				print_grid(row1, row2, row3, row4);
			}
			else if(vertical <= -1){
				row2.at(1) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row1.at(1) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
		}
		else if(horizontal == val3){  
			if(vertical >= 1){
				row4.at(3) = 'X';
				print_grid(row1, row2, row3, row4);
			}
			else if(vertical <= -1){
				row2.at(3) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row1.at(3) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
		}
		else if(horizontal == val5){  
			if(vertical >= 1){
				row4.at(5) = 'X';
				print_grid(row1, row2, row3, row4);
			}
			else if(vertical <= -1){
				row2.at(5) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row1.at(5) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
		}
		else{  
			if(vertical >= 1){
				row4.at(7) = 'X';
				print_grid(row1, row2, row3, row4);
			}
			else if(vertical <= -1){
				row2.at(7) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row1.at(7) = 'X';
					print_grid(row1, row2, row3, row4);
				}
			}
		}
	}	
	if(yStart == 3){
		if(xStart ==0){
			x = 1;
			val1 = 0;
			val3 = 1;
			val5 = 2;
			row4.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 1){
			x = 3;
			val1 = -1;
			val3 = 0;
			val5 = 1;
			row4.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 2){
			x = 5;
			val1 = -2;
			val3 = -1;
			val5 = 0;
			row4.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		else if(xStart == 3){
			x = 7;
			val1 = -3;
			val3 = -2;
			val5 = -1;
			row4.at(x) = 'X';
			print_grid(row1, row2, row3, row4);
		}
		for(i = 0; i < horizontal; i++){
			x += 2;
			row4.at(x) = 'X';
			print_grid(row1, row2, row3, row4);	
		}
		for(i = 0; i > horizontal; i--){
			x -= 2;
			row4.at(x) = 'X';
			print_grid(row1, row2, row3, row4);	
		}		
		if(horizontal == val1){  
			if(vertical <= -1){
				row3.at(1) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row2.at(1) = 'X';
					print_grid(row1, row2, row3, row4);
					if(vertical <= -3){
						row1.at(1) = 'X';
						print_grid(row1, row2, row3, row4);
					}
				}
			}
		}
		else if(horizontal == val3){
			if(vertical <= -1){
				row3.at(3) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row2.at(3) = 'X';
					print_grid(row1, row2, row3, row4);
					if(vertical <= -3){
						row1.at(3) = 'X';
						print_grid(row1, row2, row3, row4);
					}
				}
			}
		}
		else if(horizontal == val5){
			if(vertical <= -1){
				row3.at(5) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row2.at(5) = 'X';
					print_grid(row1, row2, row3, row4);
					if(vertical <= -3){
						row1.at(5) = 'X';
						print_grid(row1, row2, row3, row4);
					}
				}
			}
		}
		else{
			if(vertical <= -1){
				row3.at(7) = 'X';
				print_grid(row1, row2, row3, row4);
				if(vertical <= -2){
					row2.at(7) = 'X';
					print_grid(row1, row2, row3, row4);
					if(vertical <= -3){
						row1.at(7) = 'X';
						print_grid(row1, row2, row3, row4);
					}
				}	
			}	
		}
	}
}

/**************************************************************************
** Function: print_topbot
** Description: Prints out a line of 9 dashes
** Parameters: None
** Return: None
** Pre-Conditions: None
** Post-Conditions: A line will be printed
**************************************************************************/

void print_topbot(){
	cout << "---------" << endl;
}

/**************************************************************************
** Function: print_grid
** Description: Prints a 4 x 4 grid
** Parameters: 4 strings; row1, row2, row3, row4
** Return: None
** Pre-Conditions: The parameters are all strings
** Post-Conditions: Parameters remain unchanged, a grid will be printed
**************************************************************************/

void print_grid(string row1, string row2, string row3, string row4){
	cout << endl;
	print_topbot();
	cout << row4 << endl;
	print_topbot();
	cout << row3 << endl;
	print_topbot();
	cout << row2 << endl;
	print_topbot();
	cout << row1 << endl;
	print_topbot();
}

/**************************************************************************
** Function: check_int
** Description: Checks each character of a string to ensure it's an int
** Parameters: A string s
** Return: true or false (boolean)
** Pre-Conditions: The parameter is a string
** Post-Conditions: Parameter remains unchanged, returns a boolean value
**************************************************************************/

bool check_int(string s){  
	for(int i = 0; i < s.length(); i++){
		if(!(s.at(i) >= '0' && s.at(i) <= '9'))
			return false;
	}
	return true;
}

/**************************************************************************
** Function: restart
** Description: Asks the user if they want to restart the program and 
**		returns a boolean value depending on their answer
** Parameters: None
** Return: true or false (boolean)
** Pre-Conditions: None
** Post-Conditions: Returns a boolean value
**************************************************************************/

bool restart(){
	bool cont = true;
	string answer;
	while(cont){
		cout << "Would you like to enter new coordinates? ";
		cin >> answer;
		answer = convert(answer);
		if(answer == "yes" || answer == "y" || answer == "ye"){ //incase user doesnt input in exactly 'yes'
			return true;
		}
		else if(answer == "no" || answer == "n"){
			return false;
		}
		else{
			cout << "Please enter 'yes' or 'no'." << endl;
			continue;
		}
	}	
}

/**************************************************************************
** Function: convert
** Description: Converts all characters in a string into lowercase letters
** Parameters: string s
** Return: A string in all lowercase
** Pre-Conditions: The parameter is a string
** Post-Conditions: Parameter is changed into lowercase version
**************************************************************************/

string convert(string s){ //incase user inputs some capital letter when answering 'yes' or 'no'			
	for(int i = 0; i<s.length(); i++){
		s.at(i) = tolower(s.at(i));
	}
	return s;
}


