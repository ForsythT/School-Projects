#include <stdlib.h>
#include <stdio.h>

void dot_delay(int*, int);
void dash_delay(int*, int);
void space_delay(int*, int);
void char_delay(int*, int);

// Morse code alphabet
static char *alphabet[] = {
	".-",	// A .-
	"-...",	// B -...
	"-.-.",	// C -.-.
	"-..",	// D -..
	".",	// E .
	"..-.",	// F ..-.
	"--.",	// G --.
	"....",	// H ....
	"..",	// I ..
	".---",	// J .---
	"-.-",	// K -.-
	".-..",	// L .-..
	"--",	// M --
	"-.",	// N -.
	"---",	// O ---
	".--.",	// P .--.
	"--.-",	// Q --.-
	".-.",	// R .-.
	"...",	// S ...
	"-",	// T -
	"..-",	// U ..-
	"...-",	// V ...-
	".--",	// W .--
	"-..-",	// X -..-
	"-.--",	// Y -.--
	"--.."	// Z --..
};

int main(int argc, char **argv){
	// gets the message from command line (not needed)
	char *message = argv[1];

	// converts the message to lowercase
	int i = 0;	
	while(message[i] != '\0'){
		message[i] = tolower(message[i]);
		i++;
	}

	// converts the message into morse code dots and dashes (./-)
	char *morse_message[i];
	i = 0;
	int dec; // decimal integer value of ascii character
	while(message[i] != '\0'){
		dec = (int)message[i];
		if(dec == 32){
			morse_message[i] = " ";
		}
		else{
			dec -= 97;
			morse_message[i] = alphabet[dec];
		}
		i++;
	}
	
	// counts how many delays will be needed for the message
	int len = i;	
	int j = 0;
	int count = 0;
	for(i = 0; i < len; i++){
		j = 0;
		while(morse_message[i][j] != '\0'){
			if(morse_message[i][j] == '.' || morse_message[i][j] == '-'){
				count += 2;
			}
			j++;
		}
	}
	
	// puts the delays into an array
	int delay[count];
	int idx = 0;
	for(i = 0; i < len; i++){
		j = 0;
		while(morse_message[i][j] != '\0'){
			if(morse_message[i][j] == '.'){
				dot_delay(delay, idx);
				idx += 2;
			} 
			else if(morse_message[i][j] == '-'){
				dash_delay(delay, idx);
				idx += 2;
			}
			else{
				space_delay(delay, idx-1);
			}	
			j++;
		}
		if(morse_message[i] != " "){
			char_delay(delay, idx-1);
		}
	}
	space_delay(delay, idx-1);
}

// adds delays for dots/dashes/spaces/character ending
void dot_delay(int *delay, int idx){
	delay[idx] = 500;
	idx++;
	delay[idx] = 250;
}

void dash_delay(int *delay, int idx){
	delay[idx] = 1500;
	idx++;
	delay[idx] = 250;
}

void space_delay(int *delay, int idx){
	delay[idx] = 3500;
}

void char_delay(int *delay, int idx){
	delay[idx] = 1500;
}
