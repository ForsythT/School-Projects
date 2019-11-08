#include "./vector.hpp"
#include <vector>
#include <iostream>
#include <string>

//We do not want to include either stmt. We wouldn't 
//be able to compare our vector template to the Standard 
//using namespace std;
//using std::vector;
using std::out_of_range;
using std::exception;
using std::cout;
using std::endl;

int main (){
	vector<int> v;   //Our vector class
	std::vector<int> stdv; //Standard vector
	
	//Compare operation of our vector to std
	v.push_back(23);
	stdv.push_back(23);

	try{
		cout << v.at(0) << endl;	
	}
	catch(out_of_range &e){
		cout << e.what() << endl;
	}

	try{
		cout << v.at(1) << endl;	
	}
	catch(out_of_range &e){
		cout << e.what() << endl;
	}

	return 0;
}
