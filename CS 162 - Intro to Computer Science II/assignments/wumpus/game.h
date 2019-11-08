#include "room.h"

class Game{
	Room **cave; //2d array
	Player jeremy;
	int size;
	bool move;
	bool dead;
	public:
		Game();
		~Game();
		void win();
		void set_size(int s);
		int get_size();
		void play_game();
		void create_cave();
		void place_jeremy();
		void set_events();
		void player_turn();
		char player_direction();
		char player_choice();
		bool check_rooms();
		void print_cave();
		void shoot_north();
		void shoot_south();
		void shoot_east();
		void shoot_west();
		void jeremy_move();
		void jeremy_death();
		void wumpus_move();
		void wumpus_death();
		char restart();
		void reset();
};
