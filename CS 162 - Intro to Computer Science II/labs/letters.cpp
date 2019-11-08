#include "./letters.h"

void count_letters(ifstream &input, int *count){
	char c;
	while(input.get(c)){
		c = tolower(c);
		if(input.eof())
			break;	
		else{
			for(int i = 0; i < 26; i++){
				if(c-'a' == i){
					count[i]++;
				}
			}
		}
	}
}

void output_letters(ofstream &input, int *count){
	char c[26];
	for(int i = 0; i < 26; i++){
		c[i] = 65+i;
		input << c[i] << " " << count[i] << endl;
		cout << c[i] << " " << count[i] << endl;
	}
}
