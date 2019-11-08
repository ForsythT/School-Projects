#include "rope.h"

class Player{
	bool gold; //Jeremy needs the gold to win
	bool w_kill;
	bool alive;
	int num_moves; //mostly a score tracker
	int arrows;
	int x;
	int y;
	public:
		Player();
		void set_alive(bool a);
		bool get_alive();
		void set_wumpus(bool w);
		bool get_wumpus();
		void set_gold(bool g);
		bool get_gold();
		void set_num_moves(int n);
		int get_num_moves();
		void set_x(int xpos);
		void set_y(int ypos);
		int get_x();
		int get_y();
		int get_arrows();
		void set_arrows(int a);
		void move_north();
		void move_south();
		void move_east();
		void move_west();
		void fire_arrow_north();
		void fire_arrow_south();
		void fire_arrow_east();
		void fire_arrow_west();
};
