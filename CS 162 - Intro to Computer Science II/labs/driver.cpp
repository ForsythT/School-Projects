#include "./letters.h"

int main(){
	int *count;
	count = new int[26];
	ifstream input;
	string file;
	cout << "Input file: ";
	cin >> file; 
	input.open(file.c_str());
	if(input.fail()){
		cout << "No file" << endl;
		exit(0);
	}
	else{
		count_letters(input, count);
	}
	input.close();
	ofstream output;
	cout << "Output file: ";
	cin >> file;
	output.open(file.c_str());
	output_letters(output, count);
	output.close();
}
