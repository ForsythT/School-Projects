#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h> 
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>

// defining Room struct
struct Room { 
	char* name; // room name
	char* type; // room type
	char* connections[6]; // room connections
	int numCon; // num connections
};

void playGame(struct Room[]); // plays the game
void printTime(); // prints time to the user
void victory(char[512][32], int); // prints victory screen
bool checkIfConnected(struct Room[], char*, int, size_t); // checks if the rooms are connected
void printRoomInfo(struct Room[], int); // prints the info of the room they are in
void *writeTime(void*); // writes the time to a file

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER; // global mutex

void main()
{
	int newestDirTime = -1; // Modified timestamp of newest subdir examined
  	char targetDirPrefix[32] = "forsytht.rooms."; // Prefix we're looking for
  	char newestDirName[256]; // Holds the name of the newest dir that contains prefix
  	memset(newestDirName, '\0', sizeof(newestDirName));

  	DIR* dirToCheck; // Holds the directory we're starting in
  	struct dirent *fileInDir; // Holds the current subdir of the starting dir
  	struct stat dirAttributes; // Holds information we've gained about subdir

  	dirToCheck = opendir("."); // Open up the directory this program was run in

  	if (dirToCheck > 0) // Make sure the current directory could be opened
	{
    		while ((fileInDir = readdir(dirToCheck)) != NULL) // Check each entry in dir
		{
      			if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) // If entry has prefix
      			{
       			 	stat(fileInDir->d_name, &dirAttributes); // Get attributes of the entry

        			if ((int)dirAttributes.st_mtime > newestDirTime) // If this time is bigger
        			{
          				newestDirTime = (int)dirAttributes.st_mtime;
          				memset(newestDirName, '\0', sizeof(newestDirName));
          				strcpy(newestDirName, fileInDir->d_name);
        			}
      			}
    		}
  	}

  	closedir(dirToCheck); // Close the directory we opened

	char newDir[64] = "./"; // adds a ./ to the dir name (not sure if needed)
	strcat(newDir, newestDirName);

	int i = 0;
	char *roomArray[9];
  	DIR *roomDir;
  	struct dirent *ent;
  	if ((roomDir = opendir (newestDirName)) != NULL){ // puts the room files from the newest dir into an array
    		while ((ent = readdir (roomDir)) != NULL){
      			roomArray[i] = ent->d_name;
      			i++;
    		}
    		closedir (roomDir);
  	}
  	else{
  	perror ("Error");
  	}

	chdir(newDir); // changing directory to the new dir

	// ***MORE REPEATED CODE, FROM LINE 89 to 128, AGAIN HAD ISSUES WITH FUNCTIONS***

	struct Room rooms[7]; // creating a struct to hold the room data
	int fp, j, count, num, idx, c; // more variables
	ssize_t nread;
	char line[512]; // holds the data from the file in one string
	char *token; // token used to break up data
	count = 0;
	num = 1;
	fp = open(roomArray[2], O_RDWR, S_IRUSR | S_IWUSR); // opens the file
	if(fp == -1){
		printf("Opening file failed\n"); // error checking
	}	
	nread = read(fp, line, sizeof(line)); // reads the file into the string
	for(i = 0; i < strlen(line); i++){ // this gets how many lines are in the file, this is used for finding out how many connections the room has
		if(line[i] == '\n')
			count++;
	}
	token = strtok(line, " :\n");

	for(i = 0; i < 2; i++){ // go through the string until the name is tokened
		token = strtok(NULL, " :\n");
	}

	rooms[0].name = token; // store the name into the name string in room struct
	
	count = count - 2; // count - 2 to account for the lines containing room name and room type
	rooms[0].numCon = count; // storing numCon
	idx = 0;
	for(i = 0; i < (count*3); i++){ // this goes through and finds all of the connections, storing them into the array of strings
		token = strtok(NULL, " :\n");
		if(num % 3 == 0){ // every 3 tokens, store it into the array
			rooms[0].connections[idx] = token;	
			idx++;
		}
		num++;
	}
	
	for(i = 0; i < 2; i++){ // finally, to get the room type it keeps tokening
		token = strtok(NULL, " :\n");
	}

	token = strtok(NULL, " :\n");
	rooms[0].type = token; // and then stores it into the room type string
	close(fp); // closes file

	// *** END OF REPEAT *** GO TO LINE 387 FOR END OF REPEATS ***

	char line2[512];
	char *token2;
	count = 0;
	num = 1;
	fp = open(roomArray[3], O_RDWR, S_IRUSR | S_IWUSR);
	if(fp == -1){
		printf("Opening file failed\n");
	}	

	nread = read(fp, line2, sizeof(line2));
	for(i = 0; i < strlen(line2); i++){
		if(line2[i] == '\n')
			count++;
	}
	token2 = strtok(line2, " :\n");

	for(i = 0; i < 2; i++){
		token2 = strtok(NULL, " :\n");
	}

	rooms[1].name = token2;	

	count = count - 2;
	rooms[1].numCon = count;
	idx = 0;
	for(i = 0; i < (count*3); i++){
		token2 = strtok(NULL, " :\n");
		if(num % 3 == 0){
			rooms[1].connections[idx] = token2;	
			idx++;
		}
		num++;
	}

	for(i = 0; i < 2; i++){
		token2 = strtok(NULL, " :\n");
	}

	token2 = strtok(NULL, " :\n");
	rooms[1].type = token2;
	close(fp);

	char line3[512];
	char *token3;
	count = 0;
	num = 1;
	fp = open(roomArray[4], O_RDWR, S_IRUSR | S_IWUSR);
	if(fp == -1){
		printf("Opening file failed\n");
	}	

	nread = read(fp, line3, sizeof(line3));
	for(i = 0; i < strlen(line3); i++){
		if(line3[i] == '\n')
			count++;
	}
	token3 = strtok(line3, " :\n");

	for(i = 0; i < 2; i++){
		token3 = strtok(NULL, " :\n");
	}

	rooms[2].name = token3;
		
	count = count - 2;
	rooms[2].numCon = count;
	idx = 0;
	for(i = 0; i < (count*3); i++){
		token3 = strtok(NULL, " :\n");
		if(num % 3 == 0){
			rooms[2].connections[idx] = token3;	
			idx++;
		}
		num++;
	}

	for(i = 0; i < 2; i++){
		token3 = strtok(NULL, " :\n");
	}

	token3 = strtok(NULL, " :\n");
	rooms[2].type = token3;
	close(fp);

	char line4[512];
	char *token4;
	count = 0;
	num = 1;
	fp = open(roomArray[5], O_RDWR, S_IRUSR | S_IWUSR);
	if(fp == -1){
		printf("Opening file failed\n");
	}	

	nread = read(fp, line4, sizeof(line4));
	for(i = 0; i < strlen(line4); i++){
		if(line4[i] == '\n')
			count++;
	}
	token4 = strtok(line4, " :\n");

	for(i = 0; i < 2; i++){
		token4 = strtok(NULL, " :\n");
	}

	rooms[3].name = token4;
		
	count = count - 2;
	rooms[3].numCon = count;
	idx = 0;
	for(i = 0; i < (count*3); i++){
		token4 = strtok(NULL, " :\n");
		if(num % 3 == 0){
			rooms[3].connections[idx] = token4;	
			idx++;
		}
		num++;
	}

	for(i = 0; i < 2; i++){
		token4 = strtok(NULL, " :\n");
	}

	token4 = strtok(NULL, " :\n");
	rooms[3].type = token4;
	close(fp);

	char line5[512];
	char *token5;
	count = 0;
	num = 1;
	fp = open(roomArray[6], O_RDWR, S_IRUSR | S_IWUSR);
	if(fp == -1){
		printf("Opening file failed\n");
	}	

	nread = read(fp, line5, sizeof(line5));
	for(i = 0; i < strlen(line5); i++){
		if(line5[i] == '\n')
			count++;
	}
	token5 = strtok(line5, " :\n");

	for(i = 0; i < 2; i++){
		token5 = strtok(NULL, " :\n");
	}

	rooms[4].name = token5;
		
	count = count - 2;
	rooms[4].numCon = count;
	idx = 0;
	for(i = 0; i < (count*3); i++){
		token5 = strtok(NULL, " :\n");
		if(num % 3 == 0){
			rooms[4].connections[idx] = token5;	
			idx++;
		}
		num++;
	}

	for(i = 0; i < 2; i++){
		token5 = strtok(NULL, " :\n");
	}

	token5 = strtok(NULL, " :\n");
	rooms[4].type = token5;
	close(fp);

	char line6[512];
	char *token6;
	count = 0;
	num = 1;
	fp = open(roomArray[7], O_RDWR, S_IRUSR | S_IWUSR);
	if(fp == -1){
		printf("Opening file failed\n");
	}	

	nread = read(fp, line6, sizeof(line6));
	for(i = 0; i < strlen(line6); i++){
		if(line6[i] == '\n')
			count++;
	}
	token6 = strtok(line6, " :\n");

	for(i = 0; i < 2; i++){
		token6 = strtok(NULL, " :\n");
	}

	rooms[5].name = token6;
		
	count = count - 2;
	rooms[5].numCon = count;
	idx = 0;
	for(i = 0; i < (count*3); i++){
		token6 = strtok(NULL, " :\n");
		if(num % 3 == 0){
			rooms[5].connections[idx] = token6;	
			idx++;
		}
		num++;
	}

	for(i = 0; i < 2; i++){
		token6 = strtok(NULL, " :\n");
	}

	token6 = strtok(NULL, " :\n");
	rooms[5].type = token6;
	rooms[5].type[strlen(rooms[5].type)] = '\0';
	close(fp);

	char *token7;
	char line7[512];
	char temp7[36];
	count = 0;
	num = 1;
	fp = open(roomArray[8], O_RDWR, S_IRUSR | S_IWUSR);
	if(fp == -1){
		printf("Opening file failed\n");
	}	

	nread = read(fp, line7, sizeof(line7));
	for(i = 0; i < strlen(line7); i++){
		if(line7[i] == '\n')
			count++;
	}
	token7 = strtok(line7, " :\n");

	for(i = 0; i < 2; i++){
		token7 = strtok(NULL, " :\n");
	}

	rooms[6].name = token7;
		
	count = count - 2;
	rooms[6].numCon = count;
	idx = 0;
	for(i = 0; i < (count*3); i++){
		token7 = strtok(NULL, " :\n");
		if(num % 3 == 0){
			rooms[6].connections[idx] = token7;	
			idx++;
		}
		num++;
	}

	for(i = 0; i < 2; i++){
		token7 = strtok(NULL, " :\n");
	}

	token7 = strtok(NULL, " :\n");
	rooms[6].type = token7;
	close(fp);

	chdir(".."); // changing directory back to initial	
	playGame(rooms); // playing the game

}

void playGame(struct Room rooms[]){
	pthread_mutex_lock(&myMutex); // locking the mutex
	int pThreadResult; // then creating the time thread
	pthread_t timeThread;
	pThreadResult = pthread_create(&timeThread, NULL, writeTime, NULL);
	assert(0 == pThreadResult);
	
	int i, j, numMoves; // declaring vars
	size_t bufsize = 32;
	size_t input;
	char* buffer;
	char* str = "time";
	char path[512][32];
	numMoves = 0;
	buffer = malloc(bufsize * sizeof(char)); // allocating space
	if(buffer == NULL){ // error checking
		perror("Unable to allocate buffer.");
		exit(1);
	}
	for(i = 0; i < 7; i++){ // checks for the start room
		if(strcmp(rooms[i].type, "START_ROOM") == 0){
			break; // if so, it breaks with i being the index of the start room
		}
	}
	while(1){ // infinite loop that runs the game until victory or force quit
		printRoomInfo(rooms, i); // prints the current room info
		input = getline(&buffer, &bufsize, stdin); // gets the user input
		if(strncmp(buffer, str, input-1) == 0){ // checks if user wrote "time"
			pthread_mutex_unlock(&myMutex); // if so, unlocks the mutex
			pThreadResult = pthread_join(timeThread, NULL); //and joining the thread, allowing it to run (see end of code for timeThread function)
			assert(0 == pThreadResult); // error checking
			pthread_mutex_lock(&myMutex); // locks the mutex again
			pThreadResult = pthread_create(&timeThread, NULL, writeTime, NULL); // creates a new thread to allow infinite time checks
			printTime(); // prints the time to the user
		}
		else if(checkIfConnected(rooms, buffer, i, input-1) == true){ //checks if user input is actually a connected room
			sprintf(path[numMoves],"%s", buffer); // if so, writes the name of connection to the path
			numMoves++; // and increases amount of moves
			for(j = 0; j < 7; j++){
				if(strncmp(rooms[j].name, buffer, input-1) == 0){ // this figures out the index of the chosen connected room
					break;
				}
			}
			if(strcmp(rooms[j].type, "END_ROOM") == 0){ // checks if the connected room is the end room
				victory(path, numMoves); // if so, victory
			}
			else{ // else it replaces the current index with the new room index and continues the infinite loop
				i = j;
				j = 0;
				printf("\n");
				continue;
			}

		}
		else // otherwise, invalid entry
			printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
	}
}

// you won! victory screen
void victory(char path[512][32], int numMoves){
	int i;
	printf("\nYOU HAVE FOUND THE END ROOM! CONGRATULATIONS!\n"); // victory format
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", numMoves);
	for(i = 0; i < numMoves; i++){ // prints the path
		printf("%s", path[i]);
	}

	exit(0); // exit the program
}

// checks if the rooms are connected, if so, return true, otherwise return false
bool checkIfConnected(struct Room rooms[], char* buffer, int idx, size_t n){
	int i;
	for(i = 0; i < rooms[idx].numCon; i++){
		if(strncmp(buffer, rooms[idx].connections[i], n) == 0){
			return true;
		}
	}
	return false;
}

// prints out the room info in the correct format
void printRoomInfo(struct Room rooms[], int idx){
	int i;
	printf("CURRENT LOCATION: %s\n", rooms[idx].name);
	printf("POSSIBLE CONNECTIONS: ");
	for(i = 0; i < rooms[idx].numCon; i++){
		if(i == (rooms[idx].numCon-1))
			printf("%s.", rooms[idx].connections[i]);
		else
			printf("%s, ", rooms[idx].connections[i]);
	}
	printf("\n");
	printf("WHERE TO? >");
}

// prints out the current time in the correct format
void printTime(){
	time_t rawtime;
	struct tm *info;
	char buffer[80];
	
	time(&rawtime);
	info = localtime(&rawtime);

	strftime(buffer, 80, " %I:%M%p, %A, %B %d, %Y", info);
	printf("%s\n\n", buffer);
}

// writes the current time to a new file
void *writeTime(void *vargp){
	pthread_mutex_lock(&myMutex);
	FILE* fp;
	
	fp = fopen("currentTime.txt", "w+");
	
	time_t rawtime;
	struct tm *info;
	char buffer[80];
	
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(buffer, 80, " %I:%M%p, %A, %B %d, %Y", info);
	fprintf(fp, "%s\n", buffer);

	pthread_mutex_unlock(&myMutex);
	return NULL;
}
