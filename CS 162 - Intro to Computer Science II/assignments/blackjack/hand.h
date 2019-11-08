#include "deck.h"

class hand{
	card *cards;
	int num_cards;
	public:
		//void deal();
		void set_num_cards_hand(int);
		hand();
		~hand();
		hand(const hand&);
		void operator =(const hand&);
		void add_card(card);
		void set_cards(card*);
		void set_num_cards(int);
		card* get_cards();
		int get_num_cards();
		void display();
		void display_dealer();
		int get_total();
		bool check_split();
};
