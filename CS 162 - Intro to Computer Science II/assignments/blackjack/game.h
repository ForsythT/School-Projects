#include "dealer.h"

class game{
	deck cards;
	player *players;
	dealer game_dealer;
	int num_players;
	int count;
	public:
		game();
		game(const game&);
		~game();
		void operator =(const game&);
		void set_num_players(int);
		int get_num_players();
		void player_turn();
		void dealer_turn();
		void start_game();
		bool restart_game();
		void get_info();
		void get_bets();
		void reset();
		void deal();
		void show_player_hand(int);
		bool is_valid_int(int);
		void set_loss(int);
		void set_win(int);
		void player_action(char, int);
		void peek_dealer();
		void check_win();
		void deal_dealer();
		void help(int);
};
