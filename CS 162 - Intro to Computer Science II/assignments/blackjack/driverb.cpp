#include "game.h"

int main(){
	srand(time(NULL));
	game b;
	bool cont = true;
	while(cont){
		b.start_game();
		cont = b.restart_game();
	}
}
