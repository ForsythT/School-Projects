#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
	char morse[26][6] = {{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},{".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},{"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."}};
	char letter;
	
	int i = 0, x;
	cout << "Give letter: ";
	cin >> letter;

	x = letter - 97;
	
	while(morse[x][i] != '\0'){
		cout << morse[x][i];
		i++;
	}
	cout << endl;

	return 0;
}
