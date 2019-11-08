#include "zoo.h"

Zoo::Zoo(){
	tigers = NULL;
	num_t = 0;
	num_tavail = 2;
	polarbears = NULL;
	num_pb = 0;
	num_pbavail = 2;
	monkeys = NULL;
	num_m = 0;
	num_mavail = 2;
	penguins = NULL;
	num_p = 0;
	num_pavail = 2;
	bank = 0;
	day_num = 1;
	feed_modifier = 1;
	feed_type = 'g';
	tbonus = false;
}

Zoo::~Zoo(){
	if(tigers != NULL)
		delete [] tigers;
	if(polarbears != NULL)
		delete [] polarbears;
	if(monkeys != NULL)
		delete [] monkeys;
	if(penguins != NULL)
		delete [] penguins;
}

Zoo::Zoo(Zoo &other){
	tigers = new Tiger[other.get_num_t()];
	for(int i = 0; i < other.get_num_t(); i++){
		tigers[i] = other.tigers[i];
	}
	num_t = other.get_num_t();
	num_tavail = other.get_num_tavail();
	polarbears = new PolarBear[other.get_num_pb()];
	for(int i = 0; i < other.get_num_pb(); i++){
		polarbears[i] = other.polarbears[i];
	}
	num_pb = other.get_num_pb();
	num_pbavail = other.get_num_pbavail();
	monkeys = new Monkey[other.get_num_m()];
	for(int i = 0; i < other.get_num_m(); i++){
		monkeys[i] = other.monkeys[i];
	}
	num_m = other.get_num_m();
	num_mavail = other.get_num_mavail();
	penguins = new Penguin[other.get_num_p()];
	for(int i = 0; i < other.get_num_p(); i++){
		penguins[i] = other.penguins[i];
	}
	num_p = other.get_num_p();
	num_pavail = other.get_num_pavail();
	bank = other.get_bank();
	day_num = other.get_day_num();
	feed_modifier = other.get_feed_modifier();
	feed_type = other.get_feed_type();
	tbonus = other.get_tbonus();
}

void Zoo::operator=(Zoo &other){
	if(tigers != NULL)
		delete [] tigers;
	if(polarbears != NULL)
		delete [] polarbears;
	if(monkeys != NULL)
		delete [] monkeys;
	if(penguins != NULL)
		delete [] penguins;
	
	tigers = new Tiger[other.get_num_t()];
	for(int i = 0; i < other.get_num_t(); i++){
		tigers[i] = other.tigers[i];
	}
	num_t = other.get_num_t();
	num_tavail = other.get_num_tavail();
	polarbears = new PolarBear[other.get_num_pb()];
	for(int i = 0; i < other.get_num_pb(); i++){
		polarbears[i] = other.polarbears[i];
	}
	num_pb = other.get_num_pb();
	num_pbavail = other.get_num_pbavail();
	monkeys = new Monkey[other.get_num_m()];
	for(int i = 0; i < other.get_num_m(); i++){
		monkeys[i] = other.monkeys[i];
	}
	num_m = other.get_num_m();
	num_mavail = other.get_num_mavail();
	penguins = new Penguin[other.get_num_p()];
	for(int i = 0; i < other.get_num_p(); i++){
		penguins[i] = other.penguins[i];
	}
	num_p = other.get_num_p();
	num_pavail = other.get_num_pavail();
	bank = other.get_bank();
	day_num = other.get_day_num();
	feed_modifier = other.get_feed_modifier();
	feed_type = other.get_feed_type();
	tbonus = other.get_tbonus();
}

Tiger* Zoo::get_tigers(){
	return tigers;
}

PolarBear* Zoo::get_polarbears(){
	return polarbears;
}

Monkey* Zoo::get_monkeys(){
	return monkeys;
}

Penguin* Zoo::get_penguins(){
	return penguins;
}

int Zoo::get_day_num(){
	return day_num;
}

void Zoo::set_day_num(int d){
	day_num = d;
}

int Zoo::get_num_t(){
	return num_t;
}

int Zoo::get_num_pb(){
	return num_pb;
}

int Zoo::get_num_m(){
	return num_m;
}

int Zoo::get_num_p(){
	return num_p;
}

int Zoo::get_bank(){
	return bank;
}

int Zoo::get_num_tavail(){
	return num_tavail;
}

int Zoo::get_num_pbavail(){
	return num_pbavail;
}

int Zoo::get_num_mavail(){
	return num_mavail;
}

int Zoo::get_num_pavail(){
	return num_pavail;
}

float Zoo::get_feed_modifier(){
	return feed_modifier;
}

char Zoo::get_feed_type(){
	return feed_type;
}

bool Zoo::get_tbonus(){
	return tbonus;
}

void Zoo::set_tbonus(bool t){
	tbonus = t;
}

void Zoo::set_num_t(int t){
	num_t = t;
}

void Zoo::set_num_pb(int pb){
	num_pb = pb;
}

void Zoo::set_num_m(int m){
	num_m = m;
}

void Zoo::set_num_p(int p){
	num_p = p;
}

void Zoo::set_bank(int b){
	bank = b;
}

void Zoo::set_num_tavail(int t){
	num_tavail = t;
}

void Zoo::set_num_pbavail(int pb){
	num_pbavail = pb;
}

void Zoo::set_num_mavail(int m){
	num_mavail = m;
}

void Zoo::set_num_pavail(int p){
	num_pavail = p;
}

void Zoo::set_feed_modifier(float f){
	feed_modifier = f;
}

void Zoo::set_feed_type(char f){
	feed_type = f;
}

void Zoo::add_tiger(Tiger t){
	Tiger *new_data = new Tiger[num_t+1];
	for(int i = 0; i < num_t; i++){
		new_data[i] = tigers[i];
	}
	if(tigers != NULL){
		delete [] tigers;
	}
	new_data[num_t] = t;
	num_t++;
	tigers = new_data;
}

void Zoo::add_polarbear(PolarBear pb){
	PolarBear *new_data = new PolarBear[num_pb+1];
	for(int i = 0; i < num_pb; i++){
		new_data[i] = polarbears[i];
	}
	if(polarbears != NULL){
		delete [] polarbears;
	}
	new_data[num_pb] = pb;
	num_pb++;
	polarbears = new_data;
}

void Zoo::add_monkey(Monkey m){
	Monkey *new_data = new Monkey[num_m+1];
	for(int i = 0; i < num_m; i++){
		new_data[i] = monkeys[i];
	}
	if(monkeys != NULL){
		delete [] monkeys;
	}
	new_data[num_m] = m;
	num_m++;
	monkeys = new_data;
}

void Zoo::add_penguin(Penguin p){
	Penguin *new_data = new Penguin[num_p+1];
	for(int i = 0; i < num_p; i++){
		new_data[i] = penguins[i];
	}
	if(penguins != NULL){
		delete [] penguins;
	}
	new_data[num_p] = p;
	num_p++;
	penguins = new_data;
}

void Zoo::buy_tiger(){
	Tiger t;
	char g;
	string c;
	string n;
	string pronoun;
	bool cont = true;
	while(cont){
		cout << "What gender would you like?" << endl;
		cout << "1 - Male\n2 - Female" << endl;
		cin >> g;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch(g){
			case '1':
				t.set_gender('m'); 
				cont = false;
				break;
			case '2': 
				t.set_gender('f'); 
				cont = false;
				break;
			default:
				cout << "Invalid entry." << endl;
		}
	}
	cout << "Name your new tiger: ";
	cin >> n;
	t.set_name(n);
	add_tiger(t);
	bank = bank - t.get_cost();
	if(t.get_gender() == 'm')
		pronoun = "his";
	else
		pronoun = "her";
	cout << t.get_name() << " will love " << pronoun << " new home!" << endl << endl; 
}

void Zoo::buy_polarbear(){
	PolarBear p;
	char g;
	string n;
	string pronoun;
	bool cont = true;
	while(cont){
		cout << "What gender would you like?" << endl;
		cout << "1 - Male\n2 - Female" << endl;
		cin >> g;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch(g){
			case '1':
				p.set_gender('m'); 
				cont = false;
				break;
			case '2': 
				p.set_gender('f'); 
				cont = false;
				break;
			default:	
				cout << "Invalid entry." << endl;
		}
	}
	cout << "Name your new polar bear: ";
	cin >> n;
	p.set_name(n);
	add_polarbear(p);
	bank = bank - p.get_cost();
	if(p.get_gender() == 'm')
		pronoun = "his";
	else
		pronoun = "her";
	cout << p.get_name() << " will love " << pronoun << " new home!" << endl << endl; 
}

void Zoo::buy_monkey(){
	Monkey m;
	char g;
	string n;
	string pronoun;
	bool cont = true;
	while(cont){
		cout << "What gender would you like?" << endl;
		cout << "1 - Male\n2 - Female" << endl;
		cin >> g;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch(g){
			case '1':
				m.set_gender('m'); 
				cont = false;
				break;
			case '2': 
				m.set_gender('f'); 
				cont = false;
				break;
			default:
				cout << "Invalid entry." << endl;
		}
	}
	cout << "Name your new monkey: ";
	cin >> n;
	m.set_name(n);
	add_monkey(m);
	bank = bank - m.get_cost();
	if(m.get_gender() == 'm')
		pronoun = "his";
	else
		pronoun = "her";
	cout << m.get_name() << " will love " << pronoun << " new home!" << endl << endl;	
}
void Zoo::buy_penguin(){
	Penguin p;
	char g;
	string n;
	string pronoun;
	bool cont = true;
	while(cont){
		cout << "What gender would you like?" << endl;
		cout << "1 - Male\n2 - Female" << endl;
		cin >> g;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch(g){
			case '1':
				p.set_gender('m'); 
				cont = false;
				break;
			case '2': 
				p.set_gender('f');
				cont = false;	
				break;
			default:
				cout << "Invalid entry." << endl;
		}
	}
	cout << "Name your new penguin: ";
	cin >> n;
	p.set_name(n);
	add_penguin(p);
	bank = bank - p.get_cost();
	if(p.get_gender() == 'm')
		pronoun = "his";
	else
		pronoun = "her";
	cout << p.get_name() << " will love " << pronoun << " new home!" << endl << endl; 
}

bool Zoo::shop_animals(){
	char choice;
	cout << endl;
	cout << "Which animal would you like to buy?" << endl;
	cout << "1 - Tiger(" << num_tavail << " left) $10,000\n2 - Polar Bear(" << num_pbavail << " left) $5,000\n3 - Monkey(" << num_mavail << " left) $2,500\n4 - Penguin(" << num_pavail << " left) $1,000\n5 - Go Back\n0 - Exit Shop" << endl;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	switch(choice){
		case '1':
			if(bank >= 10000 && num_tavail > 0){
				buy_tiger();
				num_tavail--;
				}
			else{
				cout << "You can't do that (not enough money or no tigers left)." << endl << endl;
				return false;	
			}
			break;
		case '2':
			if(bank >= 5000 && num_pbavail > 0){
				buy_polarbear();
		       		num_pbavail--;	
			}
			else{
				cout << "You can't do that (not enough money or no polar bears left)." << endl << endl;
				return false;	
			}
			break;
		case '3':
			if(bank >= 2500 && num_mavail > 0){
				buy_monkey();
				num_mavail--;
			}	
			else{
				cout << "You can't do that (not enough money or no monkeys left)." << endl << endl;
				return false;	
			}
			break;
		case '4':
			if(bank >= 1000 && num_pavail > 0){
				buy_penguin();
				num_pavail--;
			}	
			else{
				cout << "You can't do that (not enough money or no penguins left)." << endl << endl;
				return false;	
			}
			break;
		case '5':
			break;
		case '0':
			return true;
		default:
			cout << "Invalid entry." << endl;
			return false;
	}
	cout << endl;
	return false;
}

void Zoo::feed_help(){
	cout << "Generic Feed - Your average feed, doesn't do anything special." << endl;
	cout << "Cheap Feed - Comes at a cheaper price for the cost of less healthy feed." << endl;
	cout << "Premium Feed - A more expensive feed that gives additional nutritional value." << endl << endl;
}

bool Zoo::shop_feed(){	
	char choice;
	cout << endl;
	cout << "Which feed would you like to buy?" << endl;	
	cout << "1 - Generic Feed $10\n2 - Cheap Feed $5\n3 - Premium Feed $20\n4 - Help\n5 - Go Back\n0 - Exit Shop" << endl;
	cin >> choice;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	switch(choice){
		case '1':
			feed_modifier = 1;
			feed_type = 'g';
			break;
		case '2':
			feed_modifier = .5;
			feed_type = 'c';
			break;
		case '3':
			feed_modifier = 2; 
			feed_type = 'p';
			break;
		case '4':
			feed_help();
		case '5':
			break;
		case '0':
			return true;
		default:
			cout << "Invalid entry." << endl << endl;
	}
	cout << endl;
	return false;
}

bool Zoo::shop(char choice){
	switch(choice){
		case '1':
			if(shop_animals() == true)
				return true;
			return false;
		case '2':
			if(shop_feed() == true)
				return true;
			return false;
		case '0':
			return true;
	}
}

void Zoo::age_animals(){
	for(int i = 0; i < num_t; i++){
		tigers[i].set_age(tigers[i].get_age()+1);
		if(tigers[i].get_sick() == true)
			tigers[i].set_days_sick(tigers[i].get_days_sick()+1);
	}
	for(int i = 0; i < num_pb; i++){
		polarbears[i].set_age(polarbears[i].get_age()+1);
		if(polarbears[i].get_sick() == true)
			polarbears[i].set_days_sick(polarbears[i].get_days_sick()+1);
	}
	for(int i = 0; i < num_m; i++){
		monkeys[i].set_age(monkeys[i].get_age()+1);
		if(monkeys[i].get_sick() == true)
			monkeys[i].set_days_sick(monkeys[i].get_days_sick()+1);
	}
	for(int i = 0; i < num_p; i++){
		penguins[i].set_age(penguins[i].get_age()+1);
		if(penguins[i].get_sick() == true)
			penguins[i].set_days_sick(penguins[i].get_days_sick()+1);
	}
}

void Zoo::tiger_death(int idx){
	if(tigers[idx].get_age() >= 25)
		cout << tigers[idx].get_name() << " (tiger) has passed away from old age." << endl << endl;
	else
		cout << tigers[idx].get_name() << " (tiger) has fallen sick with a deadly illness and did not survive." << endl << endl;
	Tiger *temp = new Tiger[num_t-1];
	int insert_idx = 0;
	for(int i = 0; i < num_t; i++){
		if(i != idx){
			temp[insert_idx] = tigers[i];
			insert_idx++;
		}
	}
	num_t--;
	delete [] tigers;
	tigers = temp;
}

void Zoo::tiger_sick(int idx){
	cout << tigers[idx].get_name() << " (tiger) has fallen sick with a severe illness, but will still live. (Payoff from " << tigers[idx].get_name() << " is half of the normal payoff while sick)" << endl << endl;
	tigers[idx].set_profit(500);
}

void Zoo::polarbear_death(int idx){
	if(polarbears[idx].get_age() >= 20)
		cout << polarbears[idx].get_name() << " (polar bear) has passed away from old age." << endl << endl;
	else
		cout << polarbears[idx].get_name() << " (polar bear) has fallen sick with a deadly illness and did not survive." << endl << endl;
	PolarBear *temp = new PolarBear[num_pb-1];
	int insert_idx = 0;
	for(int i = 0; i < num_pb; i++){
		if(i != idx){
			temp[insert_idx] = polarbears[i];
			insert_idx++;
		}
	}
	num_pb--;
	delete [] polarbears;
	polarbears = temp;
}

void Zoo::polarbear_sick(int idx){
	cout << polarbears[idx].get_name() << " (polar bear) has fallen sick with a severe illness, but will still live. (Payoff from " << polarbears[idx].get_name() << " is half of the normal payoff while sick)" << endl << endl;
	polarbears[idx].set_profit(125);
}

void Zoo::monkey_death(int idx){
	if(monkeys[idx].get_age() >= 15)
		cout << monkeys[idx].get_name() << " (monkey) has passed away from old age." << endl << endl;
	else
		cout << monkeys[idx].get_name() << " (monkey) has fallen sick with a deadly illness and did not survive." << endl << endl;
	Monkey *temp = new Monkey[num_m-1];
	int insert_idx = 0;
	for(int i = 0; i < num_m; i++){
		if(i != idx){
			temp[insert_idx] = monkeys[i];
			insert_idx++;
		}
	}
	num_m--;
	delete [] monkeys;
	monkeys = temp;
}

void Zoo::monkey_sick(int idx){
	cout << monkeys[idx].get_name() << " (monkey) has fallen sick with a severe illness, but will still live. (Payoff from " << monkeys[idx].get_name() << " is half of the normal payoff while sick)" << endl << endl;
	monkeys[idx].set_profit(62.5);
}

void Zoo::penguin_death(int idx){
	if(penguins[idx].get_age() >= 10)
		cout << penguins[idx].get_name() << " (penguin) has passed away from old age." << endl << endl;
	else
		cout << penguins[idx].get_name() << " (penguin) has fallen sick with a deadly illness and did not survive." << endl << endl;
	Penguin *temp = new Penguin[num_p-1];
	int insert_idx = 0;
	for(int i = 0; i < num_p; i++){
		if(i != idx){
			temp[insert_idx] = penguins[i];
			insert_idx++;
		}
	}
	num_p--;
	delete [] penguins;
	penguins = temp;
}

void Zoo::penguin_sick(int idx){
	cout << penguins[idx].get_name() << " (penguin) has fallen sick with a severe illness, but will still live. (Payoff from " << penguins[idx].get_name() << " is half of the normal payoff while sick)" << endl << endl;
	penguins[idx].set_profit(25);
}

void Zoo::sick(){
	int rnum, rnum2, num_sick = 0;
	while(true){
		rnum = rand() % 4;
		if(rnum == 0 && num_t > 0){
			rnum2 = rand() % num_t;
			if(tigers[rnum2].get_age() > 9){
				tiger_death(rnum2);
				return;
			}
			else if(tigers[rnum2].get_sick() == false){
				tiger_sick(rnum2);
				tigers[rnum2].set_sick(true);
				return;
			}
		}
		else if(rnum == 1 && num_pb > 0){
			rnum2 = rand() % num_pb;
			if(polarbears[rnum2].get_age() > 9){
				polarbear_death(rnum2);
				return;
			}
			else if(polarbears[rnum2].get_sick() == false){
				polarbear_sick(rnum2);
				polarbears[rnum2].set_sick(true);
				return;
			}
		}
		else if(rnum == 2 && num_m > 0){
			rnum2 = rand() % num_m;
			if(monkeys[rnum2].get_age() > 9){
				monkey_death(rnum2);
				return;
			}
			else if(monkeys[rnum2].get_sick() == false){
				monkey_sick(rnum2);
				monkeys[rnum2].set_sick(true);
				return;
			}
		}
		else if(rnum == 3 && num_p > 0){
			rnum2 = rand() % num_p;
			if(penguins[rnum2].get_age() > 9){
				penguin_death(rnum2);
				return;
			}
			else if(penguins[rnum2].get_sick() == false){
				penguin_sick(rnum2);
				penguins[rnum2].set_sick(true);
				return;
			}
		}
		for(int i = 0; i < num_t; i++){
			if(tigers[i].get_sick() == true)
				num_sick++;
		}
		for(int i = 0; i < num_p; i++){
			if(polarbears[i].get_sick() == true)
				num_sick++;
		}
		for(int i = 0; i < num_m; i++){
			if(monkeys[i].get_sick() == true)
				num_sick++;
		}
		for(int i = 0; i < num_p; i++){
			if(penguins[i].get_sick() == true)
				num_sick++;
		}
		int tot = num_t + num_pb + num_m + num_p;
		if(tot != num_sick)	
			continue;
		else{
			return;
		}
	}
}

float Zoo::bonus(){
	int rnum = rand() % 251;
	float bonus = 250 + rnum; 
	cout << "Today is National Tiger Day! Your tigers will earn a bonus $" << bonus << " today!" << endl << endl;
	return bonus;
}

void Zoo::pregnant(){
	int t_m = 0, t_f = 0, pb_m = 0, pb_f = 0, m_m = 0, m_f = 0, p_m = 0, p_f = 0, rnum;
	bool cont = true;
	cout << "In pregnancy" << endl;
	for(int i = 0; i < num_t; i++){
		if(tigers[i].get_gender() == 'm' && tigers[i].get_age() >= 3)
			t_m++;
		else if(tigers[i].get_gender() == 'f' && tigers[i].get_age() >= 3)
			t_f++;
	}	
	for(int i = 0; i < num_pb; i++){
		if(polarbears[i].get_gender() == 'm' && polarbears[i].get_age() >= 3)
			pb_m++;
		else if(polarbears[i].get_gender() == 'f' && polarbears[i].get_age() >= 3)
			pb_f++;
	}	
	for(int i = 0; i < num_m; i++){
		if(monkeys[i].get_gender() == 'm' && monkeys[i].get_age() >= 3)
			m_m++;
		else if(monkeys[i].get_gender() == 'f' && monkeys[i].get_age() >= 3)
			m_f++;
	}	
	for(int i = 0; i < num_p; i++){
		if(penguins[i].get_gender() == 'm' && penguins[i].get_age() >= 3)
			p_m++;
		else if(penguins[i].get_gender() == 'f' && penguins[i].get_age() >= 3)
			p_f++;
	}
	if((t_m > 0 && t_f > 0) || (pb_m > 0 && pb_f > 0) || (m_m > 0 && m_f > 0) || (p_m > 0 && p_f > 0)){
		while(cont){
			rnum = rand() % 4;
			switch(rnum){
				case 0:
					if(t_m > 0 && t_f > 0){
						tiger_preg(t_f);
						cont = false;
						return;
					}
					break;
				case 1:
					if(pb_m > 0 && pb_f > 0){
						polarbear_preg(pb_f);
						cont = false;
						return;
					}
					break;
				case 2:
					if(m_m > 0 && m_f > 0){
						monkey_preg(m_f);
						cont = false;
						return;
					}
					break;
				case 3:
					if(p_m > 0 && p_f > 0){
						penguin_preg(p_f);
						cont = false;
						return;
					}
					break;
				default:
					continue;
			}
		}	
	}
	else
		return;
}

char Zoo::random_gender(){
	int rnum = rand() % 2;
	char m = 'm';
	char f = 'f';
	if(rnum == 1)
		return m;
	else 
		return f;
			
}

void Zoo::tiger_preg(int t_f){
	int rnum, idx;
	Tiger t;
	if(t_f > 1){
		rnum = rand() % t_f;
	}
	else rnum = 0;
	for(int i = 0; i < num_t; i++){
		if(tigers[i].get_gender() == 'f'){
			if(rnum == 0){
				idx = i;
				rnum = -1;
			}
			else
				rnum--;
		}
	}
	t.set_gender(random_gender());
	t.set_age(0);
	string gender;
	if(t.get_gender() == 'm')
		gender = "boy";
	else 
		gender = "girl";
	cout << tigers[idx].get_name() << " (tiger) was pregnant and gave birth to a newborn baby " << gender << " tiger!" << endl << endl;
	cout << "Name the new baby tiger: " << endl;
	string n;
	cin >> n;
	t.set_name(n);
	add_tiger(t);
}

void Zoo::polarbear_preg(int t_f){
	int rnum, idx;
	PolarBear t, t2;
	if(t_f > 1){
		rnum = rand() % t_f;
	}
	else rnum = 0;
	for(int i = 0; i < num_pb; i++){
		if(polarbears[i].get_gender() == 'f'){
			if(rnum == 0){
				idx = i;
				rnum = -1;
			}
			else
				rnum--;
		}
	}
	t.set_gender(random_gender());
	t.set_age(0);
	string gender, gender2;
	t2.set_gender(random_gender());
	t2.set_age(0);
	if(t.get_gender() == 'm')
		gender = "boy";
	else  
		gender = "girl";
	if(t2.get_gender() == 'm')
		gender2 = "boy";
	else
		gender2 = "girl";
	cout << polarbears[idx].get_name() << " (polar bear) was pregnant and gave birth to 2 newborn baby polar bears!" << endl << endl;
	cout << "Name the first new baby polar bear (" << gender << "): " << endl;
	string n;
	cin >> n;
	t.set_name(n);
	add_polarbear(t);
	cout << "Name the second new baby polar bear (" << gender2 << "): " << endl;
	string n2;
	cin >> n2;
	t2.set_name(n2);
	add_polarbear(t2);
}

void Zoo::monkey_preg(int t_f){
	int rnum, idx;
	Monkey t, t2;
	if(t_f > 1){
		rnum = rand() % t_f;
	}
	else rnum = 0;
	for(int i = 0; i < num_m; i++){
		if(monkeys[i].get_gender() == 'f'){
			if(rnum == 0){
				idx = i;
				rnum = -1;
			}
			else
				rnum--;
		}
	}
	t.set_gender(random_gender());
	t.set_age(0);
	string gender, gender2;
	t2.set_gender(random_gender());
	t2.set_age(0);
	if(t.get_gender() == 'm')
		gender = "boy";
	else  
		gender = "girl";
	if(t2.get_gender() == 'm')
		gender2 = "boy";
	else
		gender2 = "girl";
	cout << monkeys[idx].get_name() << " (monkey) was pregnant and gave birth to 2 newborn baby monkeys!" << endl << endl;
	cout << "Name the first new baby monkey (" << gender << "): " << endl;
	string n;
	cin >> n;
	t.set_name(n);
	add_monkey(t);
	cout << "Name the second new baby monkey (" << gender2 << "): " << endl;
	string n2;
	cin >> n2;
	t2.set_name(n2);
	add_monkey(t2);
}

void Zoo::penguin_preg(int t_f){
	int rnum, idx;
	Penguin t, t2, t3;
	if(t_f > 1){
		rnum = rand() % t_f;
	}
	else rnum = 0;
	for(int i = 0; i < num_p; i++){
		if(penguins[i].get_gender() == 'f'){
			if(rnum == 0){
				idx = i;
				rnum = -1;
			}
			else
				rnum--;
		}
	}
	t.set_gender(random_gender());
	t.set_age(0);
	string gender, gender2, gender3;
	t2.set_gender(random_gender());
	t2.set_age(0);
	t3.set_gender(random_gender());
	t3.set_age(0);
	if(t.get_gender() == 'm')
		gender = "boy";
	else  
		gender = "girl";
	if(t2.get_gender() == 'm')
		gender2 = "boy";
	else
		gender2 = "girl";
	if(t3.get_gender() == 'm')
		gender3 = "boy";
	else
		gender3 = "girl";
	cout << penguins[idx].get_name() << " (penguin) was pregnant and gave birth to 3 newborn baby penguins!" << endl << endl;
	cout << "Name the first new baby penguin (" << gender << "): " << endl;
	string n;
	cin >> n;
	t.set_name(n);
	add_penguin(t);
	cout << "Name the second new baby penguin (" << gender2 << "): " << endl;
	string n2;
	cin >> n2;
	t2.set_name(n2);
	add_penguin(t2);
	cout << "Name the third new baby penguin (" << gender3 << "): " << endl;
	string n3;
	cin >> n3;
	t3.set_name(n3);
	add_penguin(t3);
}

bool Zoo::feed_animals(){
	float pay = 0;
	for(int i = 0; i < num_t; i++){
		if(tigers[i].get_age() < 3)
			pay = pay + (tigers[i].get_feed_cost() * 2);
		else
			pay = pay + tigers[i].get_feed_cost();
	}
	for(int i = 0; i < num_pb; i++){
		if(polarbears[i].get_age() < 3)
			pay = pay + (polarbears[i].get_feed_cost() * 2);
		else	
			pay = pay + polarbears[i].get_feed_cost();
	}
	for(int i = 0; i < num_m; i++){
		if(monkeys[i].get_age() < 3)
			pay = pay + (monkeys[i].get_feed_cost() * 2);
		else
			pay = pay + monkeys[i].get_feed_cost();
	}
	for(int i = 0; i < num_p; i++){
		if(penguins[i].get_age() < 3)
			pay = pay + (penguins[i].get_feed_cost() * 2);
		else
			pay = pay + penguins[i].get_feed_cost();
	}
	if(bank - pay >= 0){
		bank = bank - pay;
		return true;
	}
	else 
		return false;
}

void Zoo::bankrupt(){
	cout << "You've gone bankrupt! You don't have enough money to feed your animals! Luckily, PBS offered a sizeable donation of $25,000 to keep your zoo alive!" << endl << endl;
	bank = bank + 25000;
}

void Zoo::payoff(){
	float pay = 0, b = 0;
	if(tbonus == true)
		b = bonus();
	for(int i = 0; i < num_t; i++){
		if(tigers[i].get_age() < 3)
			pay = pay + (tigers[i].get_profit() * 2) + b;
		else
			pay = pay + tigers[i].get_profit() + b;
	}
	for(int i = 0; i < num_pb; i++){
		if(polarbears[i].get_age() < 3)
			pay = pay + (polarbears[i].get_profit() * 2);
		else	
			pay = pay + polarbears[i].get_profit();
	}
	for(int i = 0; i < num_m; i++){
		if(monkeys[i].get_age() < 3)
			pay = pay + (monkeys[i].get_profit() * 2);
		else
			pay = pay + monkeys[i].get_profit();
	}
	for(int i = 0; i < num_p; i++){
		if(penguins[i].get_age() < 3)
			pay = pay + (penguins[i].get_profit() * 2);
		else
			pay = pay + penguins[i].get_profit();
	}
	bank = bank + pay;
}

void Zoo::check_sick(){
	int rnum;
	for(int i = 0; i < num_t; i++){
		if(tigers[i].get_sick() == true && tigers[i].get_days_sick() > 2){
			cout << tigers[i].get_name() << " (tiger) has recovered from their sickness!" << endl << endl;
			tigers[i].set_sick(false);
			tigers[i].set_days_sick(0);
		}
		else if(tigers[i].get_age() >= 25){
			rnum = rand() % 2;
			if(rnum == 1)
				tiger_death(i);
		}
	}
	for(int i = 0; i < num_pb; i++){
		if(polarbears[i].get_sick() == true && polarbears[i].get_days_sick() > 2){
			cout << polarbears[i].get_name() << " (polar bear) has recovered from their sickness!" << endl << endl;
			polarbears[i].set_sick(false);
			polarbears[i].set_days_sick(0);
		}
		else if(polarbears[i].get_age() >= 20){
			rnum = rand() % 2;
			if(rnum == 1)
				polarbear_death(i);
		}
	}
	for(int i = 0; i < num_m; i++){
		if(monkeys[i].get_sick() == true && monkeys[i].get_days_sick() > 2){
			cout << monkeys[i].get_name() << " (monkey) has recovered from their sickness!" << endl << endl;
			monkeys[i].set_sick(false);
			monkeys[i].set_days_sick(0);
		}
		else if(monkeys[i].get_age() >= 15){
			rnum = rand() % 2;
			if(rnum == 1)
				monkey_death(i);
		}
	}
	for(int i = 0; i < num_p; i++){
		if(penguins[i].get_sick() == true && penguins[i].get_days_sick() > 2){
			cout << penguins[i].get_name() << " (penguin) has recovered from their sickness!" << endl << endl;
			penguins[i].set_sick(false);
			penguins[i].set_days_sick(0);
		}
		else if(penguins[i].get_age() >= 10){
			rnum = rand() % 2;
			if(rnum == 1)
				penguin_death(i);
		}
	}
}

void Zoo::print_info(){
	cout << "Current Balance: $" << bank << endl;
	cout << endl;
	if(num_t > 0){
		cout << "Tiger Exhibit" << endl;
		cout << "-------------" << endl;
		for(int i = 0; i < num_t; i++){
			if(tigers[i].get_sick() == true)
				cout << tigers[i].get_name() << "(sick) age " << tigers[i].get_age() << endl;
			else
				cout << tigers[i].get_name() << " age " << tigers[i].get_age() << endl;
		}
	}
	if(num_pb > 0){
		cout << endl;
		cout << "Polar Bear Exhibit" << endl;
		cout << "------------------" << endl;
		for(int i = 0; i < num_pb; i++){
			if(polarbears[i].get_sick() == true)
				cout << polarbears[i].get_name() << "(sick) age " << polarbears[i].get_age() << endl;
			else
				cout << polarbears[i].get_name() << " age " << polarbears[i].get_age() << endl;
		}
	}
	if(num_m > 0){
		cout << endl;
		cout << "Monkey Exhibit" << endl;
		cout << "--------------" << endl;
		for(int i = 0; i < num_m; i++){
			if(monkeys[i].get_sick() == true)
				cout << monkeys[i].get_name() << "(sick) age " << monkeys[i].get_age() << endl;
			else
				cout << monkeys[i].get_name() << " age " << monkeys[i].get_age() << endl;
		}
	}
	if(num_p > 0){ 
		cout << endl;
		cout << "Penguin Exhibit" << endl;
		cout << "---------------" << endl;
		for(int i = 0; i < num_p; i++){
			if(penguins[i].get_sick() == true)
				cout << penguins[i].get_name() << "(sick) age " << penguins[i].get_age() << endl;
			else
				cout << penguins[i].get_name() << " age " << penguins[i].get_age() << endl;
		}
	}
	cout << endl;
}
