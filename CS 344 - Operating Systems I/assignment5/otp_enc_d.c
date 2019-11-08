#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues
void encrypt_text(char *text, char *key, char *encrypted_text);

int main(int argc, char *argv[])
{
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead, charsWritten, i, end_of_text = 1;
	int num_forks = 0;
	socklen_t sizeOfClientInfo;
	char buffer[1024];
	struct sockaddr_in serverAddress, clientAddress;
	int childExitMethod;
	pid_t pid;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

		// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
	while(1){
		// Accept a connection, blocking if one is not available until one connects
		char *plaintext = malloc(sizeof(char));
		char *key = malloc(sizeof(char));
		sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
		if (establishedConnectionFD < 0) error("ERROR on accept");
	
		//fork here
		//check num forks
		if(num_forks < 5){
			waitpid(pid, &childExitMethod, WNOHANG); // don't wait if num is less than 5
		}
		else{
			waitpid(pid, &childExitMethod, 0); // wait if num is more than 5
		}
	
		pid = fork();
		if(pid == 0){
			// Get the message from the client and display it
			memset(buffer, '\0', sizeof(buffer));
			charsRead = recv(establishedConnectionFD, buffer, sizeof(buffer)-1, 0); // Read the client's message from the socket
			if (charsRead < 0) error("ERROR reading from socket");
			if(strcmp(buffer, "enc") == 0){
				charsWritten = send(establishedConnectionFD, "accept+", 7, 0); // Send success back
				if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
			}
			else{
				charsWritten = send(establishedConnectionFD, "reject+", 7, 0); // Send rejection back
				if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
				num_forks--;
				exit(2);
			}
			// get client's plaintext message
			while(end_of_text != 0){
				memset(buffer, '\0', sizeof(buffer));
				charsRead = recv(establishedConnectionFD, buffer, sizeof(buffer)-1, 0); // Read the client's message from the socket
				plaintext = (char*)realloc(plaintext, sizeof(char)*(strlen(buffer) + strlen(plaintext) + 1));
				strcat(plaintext, buffer);
				for(i = 0; i < strlen(buffer); i++){
					if(buffer[i] == '+'){
						end_of_text = 0;
						break;
					}
				}	
			}	
			plaintext[strcspn(plaintext, "+")] = '\0'; // Remove the trailing + that is added
	
			// let the client know the server is ready	
			charsWritten = send(establishedConnectionFD, "I am the server, and I got your message, ready for key+", 55, 0); // Send success back
			if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
			
			//get the client's key message
			end_of_text = 1;
			while(end_of_text != 0){
				memset(buffer, '\0', sizeof(buffer));
				charsRead = recv(establishedConnectionFD, buffer, sizeof(buffer)-1, 0); // Read the client's message from the socket
				key = (char*)realloc(key, sizeof(char)*(strlen(buffer) + strlen(key) + 1));
				strcat(key, buffer);
				for(i = 0; i < strlen(buffer); i++){
					if(buffer[i] == '+'){
						end_of_text = 0;
						break;
					}
				}	
			}	
			key[strcspn(key, "+")] = '\0'; // Remove the trailing + that is added
		
			char *encrypted_text = malloc(sizeof(char)*strlen(plaintext));
			memset(encrypted_text, '\0', sizeof(encrypted_text));
			//encrypt the text
			encrypt_text(plaintext, key, encrypted_text);
			
			free(key); //free key
			free(plaintext); //free plaintext
		
			encrypted_text = (char*)realloc(encrypted_text, sizeof(char)*(strlen(encrypted_text) + 1));
			strcat(encrypted_text, "+"); //add a hanging + to encrypted text
			charsWritten = send(establishedConnectionFD, encrypted_text, strlen(encrypted_text), 0); // Send ciphertext back
			if (charsWritten < 0) error("CLIENT: ERROR writing to socket"); //err
			if (charsWritten < strlen(encrypted_text)) printf("CLIENT: WARNING: Not all data written to socket oh no!\n");
			memset(buffer, '\0', sizeof(buffer));
	
			free(encrypted_text);	//free ciphertext
			close(establishedConnectionFD); // Close the existing socket which is connected to the client
			num_forks--;	//dec num forks counter
			exit(0); //exit success
		}
		else if(pid < 0){
			fprintf(stderr, "fork error\n"); //fork err
		}
		else{
			num_forks++; //inc num forks counter
		}
	}
	
	close(listenSocketFD); // Close the listening socket
	return 0; 
}

void encrypt_text(char *text, char *key, char *encrypted_text){
	int i, encrypted_char, text_val, key_val;
	char *characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

	for(i = 0; i < strlen(text); i++){
		if(text[i] == ' '){ // need this since the ascii value of space is not 91
			text_val = 26;
		}
		else{
			text_val = text[i] - 65; // can just use the ascii values - 65 to get their index in the characters array
		}
		if(key[i] == ' '){
			key_val = 26; // need since ascii value of space is no 91
		}
		else{
			key_val = key[i] - 65; // can just use the ascii values - 65 to get their index in the chars array
		}
		encrypted_char = text_val + key_val;
		// when total is > 28, need to minus 27
		while(encrypted_char > 28){
			encrypted_char -= 27;
		}
		encrypted_char %= 27;
		encrypted_text[i] = characters[encrypted_char]; // place the new encrypted char in the text
	}
	encrypted_text[i] = '\0'; //add a null terminator
}
