#include "player.h"

class dealer{
	hand d_hand;
	int card_total;
	public:
		dealer();
		~dealer();
		dealer(const dealer&);
		void operator =(const dealer&);
		void show_top();
		void show_hand();
		void add_card(card);
		int get_card_total();
		void deal();
};
