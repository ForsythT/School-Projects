#include "hand.h"

class player{
	hand p_hand;
	int playing_total;
	int bet;
	int card_total;
	bool turn;
	public:
		player();
		~player();
		player(const player&);
		void operator =(const player&);
		void set_playing_total(int);
		void set_bet(int);
		void set_card_total(int);
		void set_turn(bool);
		hand get_p_hand();
		int get_bet();
		int get_playing_total();
		int get_card_total();
		void set_p_hand(hand);
		int get_num_cards();
		bool check_hand(int);
		void set_loss();
		void blackjack();
		bool get_turn();
		void add_card(card);
		void show_hand();
		bool check_split();
		void split();
};
