#include "penguin.h"

class Zoo{
	Tiger *tigers;
	PolarBear *polarbears;
	Monkey *monkeys;
	Penguin *penguins;
	int num_t;
	int num_pb;
	int num_m;
	int num_p;
	int num_tavail;
	int num_pbavail;
	int num_mavail;
	int num_pavail;
	int day_num;
	float bank;
	float feed_modifier;
	char feed_type;
	bool tbonus;
	public:
		Zoo();
		~Zoo();
		Zoo(Zoo&);
		void operator=(Zoo&);
		Tiger* get_tigers();
		PolarBear* get_polarbears();
		Monkey* get_monkeys();
		Penguin* get_penguins();
		int get_num_t();
		int get_num_pb();
		int get_num_m();
		int get_num_p();
		int get_bank();
		int get_num_tavail();
		int get_num_pbavail();
		int get_num_mavail();
		int get_num_pavail();
		float get_feed_modifier();
		char get_feed_type();
		bool get_tbonus();
		int get_day_num();
		void set_day_num(int);
		void set_tbonus(bool);
		void set_num_t(int);
		void set_num_pb(int);
		void set_num_m(int);
		void set_num_p(int);
		void set_bank(int);
		void set_num_tavail(int);
		void set_num_pbavail(int);
		void set_num_mavail(int);
		void set_num_pavail(int);
		void set_feed_modifier(float);
		void set_feed_type(char);
		bool shop_animals();
		bool shop_feed();
		bool shop(char);
		void feed_help();
		void add_tiger(Tiger);
		void add_polarbear(PolarBear);
		void add_monkey(Monkey);
		void add_penguin(Penguin);
		void buy_tiger();
		void buy_polarbear();
		void buy_monkey();
		void buy_penguin();
		void age_animals();
		void sick();
		void check_sick();
		void tiger_sick(int);
		void tiger_death(int);
		void polarbear_sick(int);
		void polarbear_death(int);
		void monkey_sick(int);
		void monkey_death(int);
		void penguin_sick(int);
		void penguin_death(int);
		float bonus();
		void pregnant();
		void tiger_birth();
		void polarbear_birth();
		void monkey_birth();
		void penguin_birth();
		char random_gender();
		void tiger_preg(int);
		void polarbear_preg(int);
		void monkey_preg(int);
		void penguin_preg(int);
		bool feed_animals();
		void bankrupt();
		void payoff();
		void print_info();
};