#include "card.h"

class deck{
	card *cards;
	int num_cards;
	public:
		deck();
		~deck();
		void set_cards(card*);
		void set_num_cards(int);
		card* get_cards();
		card give_card();
		int get_num_cards();
		void print_deck();
		void shuffle();
		void create_deck();
};
