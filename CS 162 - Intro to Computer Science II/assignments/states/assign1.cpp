#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){

}

void sort_states_name(){
	bool cont = true;
	while(cont){
		cont = false;
		for(int i = 0; i < 5; i++){
			if(i != 0){
				if(states[i].compare(states[i-1]) < states[i-1].compare(states[i])){
					states[i].swap(states[i-1]);
					cont = true;
				}
			}	
		}
	}
	for(int i = 0; i < 5; i++){
		cout << states[i] << endl;
	}
	delete [] states;
}
