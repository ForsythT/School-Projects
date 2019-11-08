#include <iostream>

using namespace std;

#define PI 3.1415926
class shape{
	string name;
	string color;
	double area;
	public:
		shape();
		string get_name() {return name;}
		string get_color() {return color;}
		double get_area() {return area;}
		void set_name(string s) {name = s;}
		void set_color(string c) {color = c;}
		void set_area(double a) {area = a;}
		virtual void calculate_area() = 0;
};

shape::shape(){
	name = " ";
	color = " ";
}

class circle : public shape{
	double radius;
	public:
		circle(); 
		double get_radius() {return radius;}
		void set_radius(double r) {radius = r;}
		void calculate_area();
};

circle::circle(){
	set_name("Circle");
	radius = 0;
}

void circle::calculate_area(){
	set_area((radius * radius) * PI);
}

class rectangle : public shape{
	double length;
	double width;
	public:
		rectangle();
		double get_length() {return length;} 
		double get_width() {return width;}
		void set_length(double l) {length = l;}
		void set_width(double w) {width = w;}
		void calculate_area();
};


rectangle::rectangle(){
	set_name("Rectangle");
	length = 0;
	width = 0;
}

void rectangle::calculate_area(){
	set_area((length * width)); 
}

void print_shape_info(shape &s){
	cout << s.get_name() << endl;
	cout << s.get_color() << endl;
	cout << s.get_area() << endl;
}

int main(){
	shape *s;
	circle c;
	rectangle r;
	c.set_color("Green");
	r.set_color("Yellow");
	c.set_radius(4);
	r.set_length(3);
	r.set_width(4);
	c.calculate_area();
	r.calculate_area();
	s = &c;
	print_shape_info(c);
	print_shape_info(r);
	print_shape_info(*s);
	s = &r;
	print_shape_info(*s);
}
