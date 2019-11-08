#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>


// Defining the Room struct
struct Room {
	char* name; // name of room
	char* type; // type of room
	int numConnections; // how many connections
	char* roomConnections[6]; //name of connections
};

bool IsGraphFull(struct Room[]); // checks if all rooms are connected (3>6)
void AddRandomConnection(struct Room[]); // adds a connection to a random room
bool CanAddConnectionFrom(struct Room*); // checks if a connection is valid
bool ConnectionAlreadyExists(struct Room*, struct Room*); //checks if a connection exists
void ConnectRoom(struct Room*, struct Room*); // performs the connection
struct Room* GetRandomRoom(struct Room[]); // returns a random room
bool IsSameRoom(struct Room*, struct Room*); // checks if the rooms are the same
void shuffleArray(int[]); // shuffles an array of ints
void getRooms(struct Room[], char*[], int[]); // gets a random array of 7 rooms
void getType(struct Room[]); // assigns random types to each room

int main(){
	srand(time(NULL)); // seeding time
	char* roomNames[10] = {"Disneyland", "Cellar", "Dungeon", "Forest", "Brickleberry", "Murica", "Mountain", "Gotham", "Ocean", "Lair"}; // constant room names
	int roomIndex[10]; // used for randomization
	int i, j;

	for(i = 0; i < 10; i++){ // assigning the index values
		roomIndex[i] = i;
	}

	shuffleArray(roomIndex); // shuffles the array of ints (0-9);
	struct Room* roomList = malloc(7 * sizeof(struct Room)); // allocating space for struct
	getRooms(roomList, roomNames, roomIndex); //get the rooms by using first 7 nums from random num array
	getType(roomList); // gets random types

	for(i = 0; i < 7; i++){ // setting room connections to null
		for(j = 0; j < 6; j++){
			roomList[i].roomConnections[j] = '\0';
		}
	}
	while(!IsGraphFull(roomList)){ // makes random connections until each room has at least 3 connections
		AddRandomConnection(roomList);
	}

	struct stat st = {0};
	
	int pint = getpid(); // get the process id
	
	char pid[12]; // putting the pid into a string
	sprintf(pid, "%d", pint);
	
	char directory[32] = "./forsytht.rooms."; // concatenating the dir name with the pid
	strcat(directory, pid);
	
	if (stat(directory, &st) == -1) { // checks if its ok to make the dir
		mkdir(directory, 0777);
	}

	// I am sorry for what you're about to see ahead. I wanted to split these into functions but I was having a lot of trouble, so I went with hard coding it. I put comments on the first of each copy.

       	char file1[64]; // creating a string to hold the file name
	strcpy(file1, directory); // the name of file with the directory name
	strcat(file1, "/roomfile1");	
	
       	char file2[64];
	strcpy(file2, directory);
       	strcat(file2, "/roomfile2");	

       	char file3[64];
	strcpy(file3, directory);
    	strcat(file3, "/roomfile3");	

       	char file4[64];
	strcpy(file4, directory);
    	strcat(file4, "/roomfile4");	
	
       	char file5[64];
	strcpy(file5, directory);
    	strcat(file5, "/roomfile5");	

       	char file6[64];
	strcpy(file6, directory);
    	strcat(file6, "/roomfile6");	

	char file7[64];
	strcpy(file7, directory);
    	strcat(file7, "/roomfile7");	
	
	// More repeated code that I was struggling creating as a function (105-142)

	int file_descriptor;
	ssize_t nread, nwritten;

	file_descriptor = open(file1, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); // creating a file for read and right, user access
	
	if(file_descriptor == -1){ // error checking
		printf("Error opening file: %s\n", file1);
		perror("In main()");
		exit(1);
	}
	
	char* str = "ROOM NAME: "; // creating the format for ROOM NAME
	char* temp = roomList[0].name;
	char holder[64];
	memset(holder, '\0', sizeof(holder)); // putting together the string with name of room by concatenation
	strcat(holder, str);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char)); // writing the room name to the file

	char connect[32];
	for(i = 1; i < (roomList[0].numConnections)+1; i++){	// this creates each connection lines and writes them to the file
		temp = roomList[0].roomConnections[i-1];
		sprintf(connect, "CONNECTION %d: ", i); //creating connection line
		memset(holder, '\0', sizeof(holder));
		strcat(holder, connect);
		strcat(holder, temp);
		strcat(holder, "\n");
		nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char)); // writing it to the file
	}

	char type[32];
	temp = roomList[0].type; // finally this creates the ROOM TYPE line
	sprintf(type, "ROOM TYPE: ");
	memset(holder, '\0', sizeof(holder));
	strcat(holder, type);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char)); // and writes it to the file
	
	close(file_descriptor); // closes the file
	
	// end of code which should be a function ***this continues for each room until line 357***

	file_descriptor = open(file2, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(file_descriptor == -1){
		printf("Error opening file: %s\n", file1);
		perror("In main()");
		exit(1);
	}
	
	temp = roomList[1].name;
	memset(holder, '\0', sizeof(holder));
	strcat(holder, str);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	for(i = 1; i < (roomList[1].numConnections)+1; i++){	
		temp = roomList[1].roomConnections[i-1];
		sprintf(connect, "CONNECTION %d: ", i);
		memset(holder, '\0', sizeof(holder));
		strcat(holder, connect);
		strcat(holder, temp);
		strcat(holder, "\n");
		nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	}

	temp = roomList[1].type;
	sprintf(type, "ROOM TYPE: ");
	memset(holder, '\0', sizeof(holder));
	strcat(holder, type);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	
	close(file_descriptor);
	file_descriptor = open(file3, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(file_descriptor == -1){
		printf("Error opening file: %s\n", file1);
		perror("In main()");
		exit(1);
	}
	
	temp = roomList[2].name;
	memset(holder, '\0', sizeof(holder));
	strcat(holder, str);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	for(i = 1; i < (roomList[2].numConnections)+1; i++){	
		temp = roomList[2].roomConnections[i-1];
		sprintf(connect, "CONNECTION %d: ", i);
		memset(holder, '\0', sizeof(holder));
		strcat(holder, connect);
		strcat(holder, temp);
		strcat(holder, "\n");
		nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	}

	temp = roomList[2].type;
	sprintf(type, "ROOM TYPE: ");
	memset(holder, '\0', sizeof(holder));
	strcat(holder, type);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	
	close(file_descriptor);
	file_descriptor = open(file4, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(file_descriptor == -1){
		printf("Error opening file: %s\n", file1);
		perror("In main()");
		exit(1);
	}
	
	temp = roomList[3].name;
	memset(holder, '\0', sizeof(holder));
	strcat(holder, str);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	for(i = 1; i < (roomList[3].numConnections)+1; i++){	
		temp = roomList[3].roomConnections[i-1];
		sprintf(connect, "CONNECTION %d: ", i);
		memset(holder, '\0', sizeof(holder));
		strcat(holder, connect);
		strcat(holder, temp);
		strcat(holder, "\n");
		nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	}

	temp = roomList[3].type;
	sprintf(type, "ROOM TYPE: ");
	memset(holder, '\0', sizeof(holder));
	strcat(holder, type);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	
	close(file_descriptor);
	file_descriptor = open(file5, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(file_descriptor == -1){
		printf("Error opening file: %s\n", file1);
		perror("In main()");
		exit(1);
	}
	
	temp = roomList[4].name;
	memset(holder, '\0', sizeof(holder));
	strcat(holder, str);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	for(i = 1; i < (roomList[4].numConnections)+1; i++){	
		temp = roomList[4].roomConnections[i-1];
		sprintf(connect, "CONNECTION %d: ", i);
		memset(holder, '\0', sizeof(holder));
		strcat(holder, connect);
		strcat(holder, temp);
		strcat(holder, "\n");
		nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	}

	temp = roomList[4].type;
	sprintf(type, "ROOM TYPE: ");
	memset(holder, '\0', sizeof(holder));
	strcat(holder, type);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	
	close(file_descriptor);
	file_descriptor = open(file6, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(file_descriptor == -1){
		printf("Error opening file: %s\n", file1);
		perror("In main()");
		exit(1);
	}
	
	temp = roomList[5].name;
	memset(holder, '\0', sizeof(holder));
	strcat(holder, str);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	for(i = 1; i < (roomList[5].numConnections)+1; i++){	
		temp = roomList[5].roomConnections[i-1];
		sprintf(connect, "CONNECTION %d: ", i);
		memset(holder, '\0', sizeof(holder));
		strcat(holder, connect);
		strcat(holder, temp);
		strcat(holder, "\n");
		nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	}

	temp = roomList[5].type;
	sprintf(type, "ROOM TYPE: ");
	memset(holder, '\0', sizeof(holder));
	strcat(holder, type);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	
	close(file_descriptor);
	file_descriptor = open(file7, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(file_descriptor == -1){
		printf("Error opening file: %s\n", file1);
		perror("In main()");
		exit(1);
	}
	
	temp = roomList[6].name;
	memset(holder, '\0', sizeof(holder));
	strcat(holder, str);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	for(i = 1; i < (roomList[6].numConnections)+1; i++){	
		temp = roomList[6].roomConnections[i-1];
		sprintf(connect, "CONNECTION %d: ", i);
		memset(holder, '\0', sizeof(holder));
		strcat(holder, connect);
		strcat(holder, temp);
		strcat(holder, "\n");
		nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	}

	temp = roomList[6].type;
	sprintf(type, "ROOM TYPE: ");
	memset(holder, '\0', sizeof(holder));
	strcat(holder, type);
	strcat(holder, temp);
	strcat(holder, "\n");
	
	nwritten = write(file_descriptor, holder, strlen(holder) * sizeof(char));
	
	close(file_descriptor);
	
	return 0;
}

// assigns random types for the rooms
void getType(struct Room arr[]){
	int i, j, randNum, end, start; // declaring variables
       	end = 0;
	start = 0;	
	for(i = 0; i < 7; i++){ // this loop goes through each room
		arr[i].type = malloc(16 * sizeof(char));
		memset(arr[i].type, '\0', 16);
		for(j = 0; j < i; j++){
			if(arr[j].type == "END_ROOM"){ // checks if there is already an END room, if so make note
				end = 1;
			}
			else if(arr[j].type == "START_ROOM"){ // checks if there is a start room, if so make note
				start = 1;
			}
		}
		if (end == 1 && start == 1){ // if there is a start and end room, make it a mid room
			arr[i].type = "MID_ROOM";
		}
		else if (end == 0 && start == 1){ // if theres already a start room, randomly assign end or mid room
			randNum = rand() % 2;
			if(randNum == 0){
				arr[i].type = "END_ROOM";
			}
			else{
				arr[i].type = "MID_ROOM";
			}	
		}
		else if (end == 1 && start == 0){ // if there is already an end room, randomly assign start or mid room
			randNum = rand() % 2;
			if(randNum == 0){
				arr[i].type = "START_ROOM";
			}
			else{
				arr[i].type = "MID_ROOM";
			}
		}
		else{ // otherwise, there are no start or end rooms, so randomly assign type
			randNum = rand() % 3;
			if(randNum == 0){
				arr[i].type = "START_ROOM";
			}
			else if(randNum == 1){
				arr[i].type = "END_ROOM";
			}
			else{
				arr[i].type = "MID_ROOM";
			}	
		}
		if (i == 6 && (end == 0 || start == 0)){ // this is to ensure a start and end room are assigned. If not, it will reset the loop and keep going.
			i = 0;
		}
	}
}

// assigns rooms based on randomly shuffled indexs
void getRooms(struct Room arr[], char* rooms[], int idx[]){ 
	int i;
	for(i = 0; i < 7; i++){
		arr[i].name = malloc (16 * sizeof(char)); //allocate space
		memset(arr[i].name, '\0', 16);
		arr[i].name = rooms[idx[i]];
	}	
}

// shuffles an array of ints to be used to assign rooms
void shuffleArray(int array[]){
	int i, j, temp;
	
	for(i = 0; i < 10; i++){
		j = rand() % 10;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
bool IsGraphFull(struct Room rooms[]){
	int i;
	for(i = 0; i < 7; i++){
		if(rooms[i].numConnections < 3)
			return false;
	}
	return true;
}

// Adds a random, valid outbound connection from a Room to another Room
void AddRandomConnection(struct Room rooms[]){
	struct Room* A;
	struct Room* B;

	while(true){ // keeps looping until it finds a valid room to create a connection
		A = GetRandomRoom(rooms);
    		if (CanAddConnectionFrom(A) == true)
      			break;
  	}

  	do{
		B = GetRandomRoom(rooms);
  	}
  	while(CanAddConnectionFrom(B) == false || IsSameRoom(A, B) == true || ConnectionAlreadyExists(A, B) == true); // keeps looping until it finds a valid room to connect with A

	ConnectRoom(A, B);  // connects a to b
 	ConnectRoom(B, A);  // connects b to a 
}

// returns a random room
struct Room* GetRandomRoom(struct Room rooms[]){
	struct Room* randRoom;
	int randNum = rand() % 7;
	randRoom = &rooms[randNum];

	return randRoom;
}

// checks if the rooms are the same by comparing name
bool IsSameRoom(struct Room* x, struct Room* y){
	if(x->name == y->name){
		return true;
	}
	return false;
}

// Returns true if a connection can be added from Room x (< 6 outbound connections), false otherwise
bool CanAddConnectionFrom(struct Room* x) {
	if(x->numConnections < 6)
		return true;
	return false;
}
// Returns true if a connection from Room x to Room y already exists, false otherwise
bool ConnectionAlreadyExists(struct Room* x, struct Room* y){
	int i;
	for(i = 0; i < x->numConnections; i++){
		if(x->roomConnections[i] == y->name){
			return true;
		}
	}
	return false;
}

// Connects Rooms x and y together, does not check if this connection is valid
void ConnectRoom(struct Room *x, struct Room *y){	
	int i = 0;

	while(x->roomConnections[i]){
		i++;
	}

	x->roomConnections[i] = y->name;
	x->numConnections++;
}
