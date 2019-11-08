#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

int first(int x)
{
	cout << "x = " << x << ", 3^sin(" << x << ")" << endl;
	cout << "sin(" << x << ") = " << sin(x) << endl;
	cout << "3^" << sin(x) << " = " << pow (3, sin(x)) << endl;
	return 0;
}

int second(int x)
{
	int y;
	cout << "x = " << x << ", log2(" << x << "^2 + 1)" << endl;
	y = pow(x, 2) + 1;
	cout << x << "^2 + 1 = " << y << endl;
	cout << "log2(" << y << ") = (ln(" << y << "))/(ln(2))" << endl;
	cout << "ln(" << y << ") = " << log(y) << endl;
	cout << "ln(2) = " << log(2) << endl;
	cout << log(y) << "/" << log(2) << " = " << log(y)/log(2) << endl;
	return 0;
}

int limits()
{
	short num1 = SHRT_MIN;
	cout << SHRT_MIN << endl;
	num1 = (short)pow(2, (sizeof(short)*8)-1);
	cout << num1 << endl;
	cout << endl; 
	
	short num2 = SHRT_MAX;
	cout << SHRT_MAX << endl;
	num2 = (short)pow(2, (sizeof(short)*8)-1)-1;
	cout << num2 << endl;
	cout << endl;

	unsigned short num3 = USHRT_MAX;
	cout << USHRT_MAX << endl;
	num3 = (unsigned short)pow(2, sizeof(unsigned short)*8)-1;
	cout << num3 << endl;
	cout << endl;
	
	int num4 = INT_MIN;
	cout << INT_MIN << endl;
	num4 = (int)pow(2, (sizeof(int)*8)-1);
	cout << num4 << endl;
	cout << endl;
	
	int num5 = INT_MAX;
	cout << INT_MAX << endl;
	num5 = (int)pow(2, (sizeof(int)*8)-1)-1; 
	cout << num5 << endl;
	cout << endl;

	unsigned int num6 = UINT_MAX;
	cout << UINT_MAX << endl;
	num6 = (unsigned int)pow(2, sizeof(int)*8)-1;
	cout << num6 << endl;
	cout << endl;

	long num7 = LONG_MIN;
	cout << LONG_MIN << endl;
	num7 = (long)pow(2, (sizeof(long)*8)-1);
	cout << num7 << endl;
	cout << endl;

	long num8 = LONG_MAX;
	cout << LONG_MAX << endl;
	num8 = (long)pow(2,(sizeof(long)*8)-1)-1;
	cout << num8 << endl;
	cout << endl;
	
	unsigned long num9 = ULONG_MAX;
	cout << ULONG_MAX << endl;
	num9 = (unsigned long)pow(2, sizeof(unsigned long)*8)-1;
	cout << num9 << endl;
	cout << endl;
		
	return 0;
}
 
int main()
{
	cout << "cos(2*PI/3) = " << cos(2*M_PI/3) << endl; 
	cout << "2sin(2*PI/3) = " << 2*sin(2*M_PI/3) << endl;
	cout << "tan(-3*PI/4) = " << tan(-3*M_PI/4) << endl;
	cout << "log10(55) = " << log10(55) << endl;
	cout << "ln(60) = " << log(60) << endl;
	cout << endl;
	cout << "log2(15) = (ln(15))/(ln(2))" << endl;
	cout << "ln(15) = " << log(15) << endl;
	cout << "ln(2) = " << log(2) << endl;
	cout << log(15) << "/" << log(2) << " = " << log(15)/log(2) << endl;
	cout << endl;
	cout << "log4(40) = (ln(40))/(ln(4))" << endl;
	cout << "ln(40) = " << log(40) << endl;
	cout << "ln(4) = " << log(4) << endl;
	cout << log(40) << "/" << log(4) << " = " << log(40)/log(4) << endl;
	cout << endl;
	cout << "Solve 3^sinx for x = 1, x = 10, x = 100" << endl;
	cout << endl;
	first(1);
	cout << endl;
	first(10);
	cout << endl;
	first(100);
	cout << endl;
	cout << "Solve log2(x^2 + 1) for x = 1, x = 10, x = 100" << endl;
	cout << endl;
	second(1);
	cout << endl;
	second(10);
	cout << endl;
	second(100); 
	cout << endl;
	limits();
	return 0;
}

