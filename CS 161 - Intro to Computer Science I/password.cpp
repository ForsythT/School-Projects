#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

int randnum(float len, float percent);
int randlower(float len, float percent);
int randspecial(float len, float percent);
int randupper(float len, float percent);
int is_positive_int(string testInt);
bool prompt_again();
string decision(string x);

int main()
{
	float percentupper, percentlower, percentnum, percentspecial, len;
	string letters, upper, lower, number, special, length;
	srand(time(NULL));
	bool cont = true;
	while (cont == true)
	{
		cout << "How long do you want the password to be? ";
		cin >> length;
		len = is_positive_int(length);	
		letters = decision("letters");
		if (letters == "Yes")
		{
			upper = decision("uppercase letters");
			if (upper == "Yes")
			{
				cout << "What percent of the password should be uppercase?(eg. 10) ";
				cin >> percentupper;
				if (upper == "No")
				{
					percentupper = 0;
				}
			}
			lower = decision("lowercase letters");
			if (lower == "Yes")
			{
				cout << "What percent of the password should be lowercase?(eg. 10) ";
				cin >> percentlower;
				if (lower == "No")
				{
					percentlower = 0;
				}
			}
			if (letters == "No")
			{
				percentupper = 0;
				percentlower = 0;
			}
		}
		number = decision("numbers");
		if (number == "Yes")
		{
			cout << "What percent of the password should be numbers? ";
			cin >> percentnum;
		}
		if (number == "No")
		{
			percentnum = 0;	
		}
		special = decision("special characters");
		if (special == "Yes")
		{
			cout << "What percent of the password should be special characters? ";		
			cin >> percentspecial;
		}
		if (special == "No")
		{
			percentspecial = 0;
		}
		cout << "Your password is ";
		randnum(len, percentnum);
		randlower(len, percentlower);
		randupper(len, percentupper);
		randspecial(len, percentspecial);
		cout << endl;
		cont = prompt_again();
	}	
}

int randupper(float len, float percent)
{
	float x, rnum;
	percent = percent/100;
	x = len * percent;
	for(int i = 0; i < x; i++)
	{
		rnum = rand()%25+65;
		cout << (char)rnum;
	}
	return 0;
}

int randspecial(float len, float percent)
{
	float x, rnum;
	percent = percent/100;
	x = len * percent;
	for(int i = 0; i < x; i++)
	{
		rnum = rand()%13+33;
		cout << (char)rnum;
	}
	return 0;
}

int randlower(float len, float percent)
{
	float x, rnum;
	percent = percent/100;
	x = len * percent;
	for(int i = 0; i < x; i++)
	{
		rnum = rand()%25+97;
		cout << (char)rnum;
	}
	return 0;
}

int randnum(float len, float percent)
{
	float x, rnum;
	percent = percent/100;
	x = len * percent;
	for(int i = 0; i < x; i++)
	{
		rnum = rand()%10;
		cout << rnum;
	}
	return 0;
}

bool prompt_again()
{
	bool cont = true;
	string answer;
	while(cont == true)
	{
		cout << "Would you like to create another password? ";
		cin >> answer;	
		if (answer == "Yes")
		{	
			return "Yes";
		}
		else if (answer == "No")
		{	
			return "No";
		}
		else
			continue;
	}	

}

string decision(string x)
{	
	string answer;
	while(true)
	{	
		cout << "Do you want " << x << "(Yes/No?) ";
		cin >> answer;
		if (answer == "Yes")
		{	
			return "Yes";
		}
		else if (answer == "No")
		{	
			return "No";
		}
		else
			continue;
	}
}

int is_positive_int(string testInt)
{
	int unum;
	for(int i = 0; i < testInt.length(); i++)

		if (!(testInt.at(i)) > '0'   || (unum = atoi(testInt.c_str())) > '9')
		{
			cout << "Please enter a valid positive integer: ";
			cin >> testInt;
			i = -1;
		}
		else
			return atoi(testInt.c_str());	
}
