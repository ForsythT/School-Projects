#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

void create_key(int, char*);

int main(int argc, char *argv[]){
	srand(time(NULL));
	if (argc < 2){ // Check usage and args
		fprintf(stderr, "USAGE: %s keylength\n", argv[0]);
		exit(1);
	}

	int keylength = atoi(argv[1]); // Convert key length from string to int
	char key[keylength+1];
	create_key(keylength, key);
	printf("%s", key);

	return 0;
}

void create_key(int keylength, char *key){
	char *characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	int i, r_num;
	for(i = 0; i < keylength; i++){
		r_num = rand() % 27;
		key[i] = characters[r_num];
	}
	key[keylength] = '\n';
	key[keylength+1] = '\0';


}
