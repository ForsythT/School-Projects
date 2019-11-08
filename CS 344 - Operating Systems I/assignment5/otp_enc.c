#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>

void check_characters(char*);
void check_lengths(char*, char*, char*[]);

void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues

int main(int argc, char *argv[])
{
	int i, fp, socketFD, portNumber, charsWritten, charsRead, end_of_text;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char *plaintext = malloc(sizeof(char));
	char *key = malloc(sizeof(char));
	char *response = malloc(sizeof(char));
	char buffer[1024];
	ssize_t nread;
    
	if (argc < 4) { fprintf(stderr,"USAGE: %s plaintext key port\n", argv[0]); exit(0); } // Check usage & args
	
	// Read the plaintext from the given plaintext file
	fp = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR); // open the plaintext file
	if(fp == -1){
		printf("Opening file failed\n"); // error checking
		exit(1);
	}	
	
	memset(buffer, '\0', sizeof(buffer));
	while(read(fp, buffer, sizeof(buffer)-1) != 0){
		plaintext = (char*)realloc(plaintext, sizeof(char)*(strlen(buffer) + strlen(plaintext) + 1));
		strcat(plaintext, buffer);
		memset(buffer, '\0', sizeof(buffer));
	}

	plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the trailing \n
	close(fp);

	check_characters(plaintext);

	// Read the key from the given key file
	fp = open(argv[2], O_RDWR, S_IRUSR | S_IWUSR); // open the key file
	if(fp == -1){
		printf("Opening file failed\n"); // error checking
	}	
	
	memset(buffer, '\0', sizeof(buffer));
	while(read(fp, buffer, sizeof(buffer)-1) != 0){
		key = (char*)realloc(key, sizeof(char)*(strlen(buffer) + strlen(key)) + 1);
		strcat(key, buffer);
		memset(buffer, '\0', sizeof(buffer));
	}
	
	key[strcspn(key, "\n")] = '\0'; // Remove the trailing \n
	close(fp);
	
	check_characters(key);

	check_lengths(plaintext, key, argv);

	plaintext = (char*)realloc(plaintext, sizeof(char)*(strlen(plaintext) + 1));
	strcat(plaintext, "+");
	key = (char*)realloc(key, sizeof(char)*(strlen(key) + 2));
	strcat(key, "+");

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");


	charsWritten = send(socketFD, "enc", 3, 0); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < strlen(buffer)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
	
	end_of_text = 1;
	while(end_of_text != 0){
		memset(buffer, '\0', sizeof(buffer));
		charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read the client's message from the socket
		if (charsRead < 0) error("CLIENT: ERROR reading from socket");
		response = (char*)realloc(response, sizeof(char)*(strlen(buffer) + strlen(response)));
		strcat(response, buffer);
		for(i = 0; i < strlen(buffer); i++){
			if(buffer[i] == '+'){
				end_of_text = 0;
				break;
			}
		}	
	}	
	response[strcspn(response, "+")] = '\0'; // Remove the trailing + that is added

	if(strcmp(response, "reject") == 0){
		fprintf(stderr, "otp_enc error: cannot connect to otp_dec_d on port %s\n", argv[3]);
		exit(2);
	}
	// Send message to server
	charsWritten = send(socketFD, plaintext, strlen(plaintext), 0); // Write to the server
	
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < strlen(plaintext)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Get return message from server
	end_of_text = 1;
	memset(response, '\0', sizeof(response));
	while(end_of_text != 0){
		memset(buffer, '\0', sizeof(buffer));
		charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read the client's message from the socket
		if (charsRead < 0) error("CLIENT: ERROR reading from socket");
		response = (char*)realloc(response, sizeof(char)*(strlen(buffer) + strlen(response)));
		strcat(response, buffer);
		for(i = 0; i < strlen(buffer); i++){
			if(buffer[i] == '+'){
				end_of_text = 0;
				break;
			}
		}	
	}	
	response[strcspn(response, "+")] = '\0'; // Remove the trailing + that is added
	
	// Send message to server
	charsWritten = send(socketFD, key, strlen(key), 0); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < strlen(key)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Get return message from server
	memset(response, '\0', sizeof(response));
	end_of_text = 1;
	while(end_of_text != 0){
		memset(buffer, '\0', sizeof(buffer));
		charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read the client's message from the socket
		if (charsRead < 0) error("CLIENT: ERROR reading from socket");
		response = (char*)realloc(response, sizeof(char)*(strlen(buffer) + strlen(response)));
		strcat(response, buffer);
		for(i = 0; i < strlen(buffer); i++){
			if(buffer[i] == '+'){
				end_of_text = 0;
				break;
			}
		}	
	}	
	response[strcspn(response, "+")] = '\0'; // Remove the trailing + that is added
	response = (char*)realloc(response, sizeof(char)*(strlen(response) + 1));
	strcat(response, "\n");
	printf("%s", response);

	close(socketFD); // Close the socket
	
	free(plaintext);
	free(key);
	free(response);
	return 0;
}

void check_characters(char* text){
	char *characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	int i, j, good;
	for(i = 0; i < strlen(text); i++){
		good = 1;
		for(j = 0; j < 27; j++){
			if(text[i] == characters[j]){
				good = 0;
			}
		}
		if(good == 1){
			fprintf(stderr,"otp_enc error: input contains bad characters\n"); 
			exit(1);	
		}
	}
}

void check_lengths(char* plaintext, char* key, char* argv[]){
	if(strlen(plaintext) > strlen(key)){
		fprintf(stderr, "otp_enc error: key '%s' is too short\n", argv[2]);
		exit(1);
	}
}
