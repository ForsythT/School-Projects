/**************************************************************************
** Program Filename: morsecode
** Author: Tim Forsyth
** Date: 2/28/2016
** Description: A translator that translates from english to morse and vice versa
** Input: English or morse code phrase to be translated
** Output: Translated morse code or english phrase
**************************************************************************/

#include <iostream>
#include <stdlib.h>

using namespace std;

int get_array(int, int, char*, char*);
void morse_to_english(int, char*, char*, char[][6], char*);
void convert_morse_letter(char *letter, char[][6], char*);
void english_to_morse(int, char*, char[], char[][6]);
void print_morse_letter(int, char[][6]);
void str_upper(char*, int);
void decision_choices(int, int, int length, int, char *array, char *alphabet, char morse[][6], char *letter, char*);
void replace_array(char *array, char *arraynew, int x);
int decision();

/**************************************************************************
** Function: main
** Description: Runs the program
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: None(program executes)
**************************************************************************/

int main(){
	char *arraynew, *array, letter[6] = {' ',' ',' ',' ',' ','\0'};	
	char morse[26][6] = {{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},{".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},{"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."}};
	char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int i, size;

	system("clear");
	cout << "Welcome to the Morse Code Translator." << endl;
	
	while(true){
		size = 1;
		array = new char[size];
		int answer = decision(), length;
		decision_choices(size, i, length, answer, array, alphabet, morse, letter, arraynew);		
	}
		
	return 0;
}

/**************************************************************************
** Function: decision_choices
** Description: Switch cases that rely on answer from decision function 
** Parameters: length of input, answer, input, alphabet array, morse code array, letter array
** Pre-Conditions: All parameters are of their respective types
** Post-Conditions: None (functions are called, prints out invalid input if answer != 0, 1, 2)
**************************************************************************/

void decision_choices(int size, int i, int length, int answer, char *array, char *alphabet, char morse[][6], char *letter, char *arraynew){
	switch(answer){
		case 0:
			exit(0);
		case 1:
			length = get_array(i, size, array, arraynew);
			str_upper(array, length);
			english_to_morse(length, array, alphabet, morse);
			break;
		case 2:
			length = get_array(i, size, array, arraynew);
			morse_to_english(length, array, letter, morse, alphabet);
			break;
		default:
			cout << "Invalid input." << endl;
	}		
}

/**************************************************************************
** Function: get_array
** Description: Gets an array phrase
** Parameters: Char array that can be changed
** Pre-Conditions: Array is a pointer char array
** Post-Conditions: Array is filled with user input
**************************************************************************/

int get_array(int i, int size, char *array, char *arraynew){
	char c;
	i = 0;
	cout << "Enter a phrase: ";	
	cin.ignore();
	while(c != '\n'){
		c = cin.get();
		array[i] = c;
		size++;
		arraynew = new char[size];
		i++;
		replace_array(array, arraynew, i);
		delete[] array;
		array = new char[size];
		replace_array(arraynew, array, i);
		delete[] arraynew;
	}
	array[i+1] = '\0';
	return i;
}

void replace_array(char *array, char *arraynew, int x){
	for(int i = 0; i < x; i++){
		arraynew[i] = array[i];
	}
}

/**************************************************************************
** Function: decision
** Description: Asks the user for what they want to do
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns an int depending on user response
**************************************************************************/

int decision(){
	int answer;
	cout << endl;
	cout << "Select what you would like to do: " << endl;
	cout << "1 - Translate English text to Morse Code\n2 - Translate Morse Code to English text\n0 - Quit"<< endl;
	cin >> answer;
	return answer;
}

/**************************************************************************
** Function: str_upper
** Description: Sets all letters in phrase to uppercase 
** Parameters: array string, int length
** Pre-Conditions: All parameters must be of their respective types
** Post-Conditions: All characters in char array string are uppercase 
**************************************************************************/

void str_upper(char *string, int length){
	for(int i = 0; i < length; i++){
		string[i] = toupper(string[i]);
	}
}

/**************************************************************************
** Function: english_to_morse
** Description: Converts an english phrase to morse code
** Parameters: int lenght(lenght of phrase), array phrase, alphabet array 
**	       and morse code array
** Pre-Conditions: Parameters need to be of their respective types
** Post-Conditions: None(translation is printed out)
**************************************************************************/

void english_to_morse(int length, char *phrase, char alphabet[], char morse[][6]){
	cout << "Your translated phrase is: ";
	for(int i = 0; i < length; i++){
		for(int x = 0; x < 26; x++){
			if(phrase[i] == alphabet[x]){
				print_morse_letter(x, morse);
				cout << "  ";
				break;
			}
		}
		if(phrase[i] == ' '){
			cout << "      ";
		}
	}
	cout << endl;
}

/**************************************************************************
** Function: morse_to_english
** Description: Translate morse code into english text 
** Parameters: Length of input, input, letter array, morse code array, alphabet array
** Pre-Conditions: They are all their respective types
** Post-Conditions: None(translation is printed)
**************************************************************************/

void morse_to_english(int length, char *phrase, char *letter, char morse[][6], char *alphabet){
	int i = 0, x = 0;
	cout << "Your translated phrase is: ";
	for(i; i < length; i++){
		if(phrase[i] == '-' || phrase[i] == '.'){
			letter[x] = phrase[i];
			x++;
		}
		else if(phrase[i] == '\n' || phrase[i] == ' '){
			letter[x] = ' ';
			convert_morse_letter(letter, morse, alphabet);
			x = 0;
			if(phrase[i+1] == ' ' && phrase[i+2] == ' ' && phrase[i+3] == ' ' && phrase[i+4] == ' ' && phrase[i+5] == ' ' && phrase[i+6] == ' '){ 
				cout << ' ';
				i += 6;
			}
		}
	}
	cout << endl;
}

/**************************************************************************
** Function: convert_morse_letter 
** Description: Converts a single morse letter array into the corresponding alphabetic letter
** Parameters: Array containing morse letter, array containing all morse letters, array containing all alphabet letters
** Pre-Conditions: All parameters are of their respective types
** Post-Conditions: None(letter is printed out)
**************************************************************************/

void convert_morse_letter(char *letter, char morse[][6], char *alphabet){
	for(int x = 0; x < 26; x++){
		for(int i = 0; i < 6; i++){
			if(letter[i] == morse[x][i]){
				continue;
			}
			else if(morse[x][i] == '\0' && letter[i] == ' '){
				cout << alphabet[x];
				return;
			}
			else{
				i = 0;
				break;	
			}
		}	
	}
}

/**************************************************************************
** Function: print_morse_letter
** Description: Prints out a morse code letter
** Parameters: int x(which letter to print), and array of morse letters
** Pre-Conditions: x must be an int, morse must be a 2d array of chars
** Post-Conditions: None (prints letter)
**************************************************************************/

void print_morse_letter(int x, char morse[][6]){
	int i = 0;
	
	while(morse[x][i] != '\0'){
		cout << morse[x][i];
		i++;
	}
	cout << ' ';
	return;
}
