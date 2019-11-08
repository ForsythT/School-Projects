/************************************************************************************************************************
 * Program: finance.cpp
 * Author: Tim Forsyth
 * Date: 1/18/2016
 * Description: A Financial Calculator that calculates loan balance, compounded interest and future value
 * Input: User finance information (intial, interest rates, payments, periods, etc. depending on choice of calculation
 * Output: Financial values of their choosing (loan balance, compounded interest balance, future value)
 * **********************************************************************************************************************/


#include <iostream>
#include <cmath>
#include <iomanip>

using  namespace std;


int loan()
{
	float balance, initial, rate, prate, payment, goal;
	int often, amount;
	cout << "You have chosen to calculate Loan Balance." << endl;
	cout << "What is the initial investment in dollars (eg. 500): ";
	cin >> initial;
	cout << "What is the interest rate in percentages (eg. 8): ";
	cin >> rate;
	cout << "How often are loan payments made?" << endl;
	cout << "1 - daily" << endl;
	cout << "2 - weekly" << endl;
	cout << "3 - monthly" << endl;
	cout << "4 - yearly" << endl;
	cin >> often;
	
	switch(often)
	{
		case 1: 
			prate = (rate/365.0);
			break;
		case 2:
			prate = (rate/52.0); 
			break;
		case 3:
			prate = (rate/12.0);
			break;
		case 4:
			prate = rate;
			break;
		default:
			cout << "Invalid input, try again." << endl;
	}
	prate = prate/100;
	cout << "What is the amount of each equal payment in dollars (eg. 500): ";
	cin >> payment;
	cout << "What is the amount of payments you have made: ";
	cin >> amount;
	balance = initial*pow((1+prate), amount)-(payment/prate)*(pow((1+prate), amount)-1);
	cout << "What is your goal for your loan balance: ";
	cin >> goal;
	if (goal >= balance)
	{
		cout << "Congratulations, you have met your goal!" << endl;
	}
	else if (goal < balance)
	{
		cout << "You have not met your goal, you are $" << balance - goal << " over your goal." << endl;
	}
	cout << "You have $" << balance << " to pay off on your loan." << endl;
	return 0;
}

int interest()
{
	int t;
	float p, r, g, a;
	cout << "You have chosen to calculate Continuosly Compounded Interest." << endl;
	cout << "What is your initial investment in dollars (eg. 500): ";
	cin >> p;
	cout << "What is the annual interest rate in percentages (eg. 8): ";
	cin >> r;
	r = r/100;
	cout << "How long in years will you be compounding: ";
	cin >> t;
	cout << "What is your goal amount in dollars by the provided time: ";
	cin >> g;
	a = p*exp(r*t);
	if (g <= a)
	{
		cout << "Congratulations, you will meet your goal!" << endl;
	}
	else if (g > a)
	{
		cout << "You will not meet your goal, you will be $" << g - a << " short." << endl;
	} 
	cout << "You will have $" << a << " by the end of " << t << " years." << endl;
	
	return 0;
}
int future()
{
	int n; 
	float c, r, g, f;
	cout << "You have chosen to calculate Future Value." << endl;
	cout << "What is your starting cash flow: ";
	cin >> c;
	cout << "What is the rate of return in percentages (eg. 1): ";
	cin >> r;
	cout << "What is the number of periods: ";
	cin >> n;
	cout << "What is your future value goal: ";
	cin >> g;
	r = r/100;
	f = c*pow((1+r), n);
	if (g <= f)
	{
		cout << "Congratulations, you will meet your goal!" << endl;
	}
	else if (g > f)
	{
		cout << "You will not meet your goal, you are $" << g - f << " short." << endl;
	}
	cout << "Your Future Value is $" << f << "." << endl; 
	return 0;
}

int again()
{
	while (true)
	{
		int ans;
		cout << "Do you want to use the Financial Calculator again?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl;
		cin >> ans;
		if (ans == 1)
		{
			return 1;
		}
		else if (ans == 2)
		{
			return 0;
		}
		else
		{
			cout << "Invalid input, try again." << endl;
		}	
	}
}

int main()
{
	bool quest;
	quest = true;
	while(quest)
	{
		int input;
		cout << fixed << setprecision(2);
		cout << endl;
		cout << "Welcome to the Financial Calculator!" << endl;
		cout << "What would you like to calculate?" << endl;
		cout << "1 - Loan Balance" << endl;
		cout << "2 - Continuously Compounded Interest" << endl;
		cout << "3 - Future Value" << endl;
		cin >> input;
		
		if (input == 1)
		{
			loan();
			quest = again();
		}
		else if (input == 2)
		{
			interest();
			quest = again();
		}
		else if (input == 3)
		{
			future();
			quest = again();
		}
		else
		{
			cout << "Invalid input, try again." << endl;
		}
	}
	return 0;
}
