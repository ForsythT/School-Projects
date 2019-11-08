#include "./state_info.h"

int main(int argc, char *argv[]){
	int statenum, count = 1;
	string filename;
	state *states;
	ifstream input;
	is_valid_arguments(argv, argc);
	for(int i = 1; i < argc-1; i+=2){
		if(strcmp(argv[i], "-f") == 0){
			filename = argv[i+1];
		}
		else if(strcmp(argv[i], "-s") == 0){
			statenum = atoi(argv[i+1]);
		}
	}
	bool cont = true;	
	while(cont){
		if(count > 1){
			get_user_info(filename, statenum);
		}
		states = create_states(statenum);
		input.open(filename.c_str());
		get_state_data(states, statenum, input);
		input.close();
		check_income(states, statenum);
		largest_state(states, statenum);
		largest_county(states, statenum);
		avg_house_cost(states, statenum);
		sort_states_name(states, statenum);
		sort_states_pop(states, statenum);
		delete_info(states, statenum);
		cont = start_again();
		count++;
	}
}
