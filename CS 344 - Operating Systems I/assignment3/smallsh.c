/****************************************************************************************
********************************* Assignment 3 ******************************************
*** Author: Tim Forsyth								      ***
*** Date: 11/15/2017								      ***
*** Description: This is a basic shell that contains 3 built-in commands: cd, status, ***
*** 		and exit. It also allows for input and output files as well as        ***
***		background processes. SIGTSTP (CTRL+Z) is redirected as a toggle for  ***
***		allowing background processes to be created.			      ***
*****************************************************************************************
****************************************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

// Function declarations
void sh_loop(void);
char* sh_read_input();
char** sh_get_args(char*);
int sh_execute(char**, int*, pid_t*);
int sh_cd(char**, int*);
int sh_exit(char**);
int sh_status(int*);
int sh_execute_command(char**, int*, pid_t*);
void catchSIGINT(int signo);
void catchSIGTSTP(int signo);
void set_sig_handlers();
void check_for_bg_pid(int*);

// Global background mode variable
int background_mode = 0;
// Global signal variable
struct sigaction SIGINT_action = {0};

int main(){
	// Set up signals
	set_sig_handlers();
	// Run command loop
	sh_loop();

	return EXIT_SUCCESS;
}

/*****************************************************************
** Function: set_sig_handlers 
** Description: This initializes and sets signal handler for the
**		SIGTSTP signal as well as sets the SIGINT to be
**		ignored.
*****************************************************************/
void set_sig_handlers(){
	// Init SIGTSTP struct
	struct sigaction SIGTSTP_action = {0};

	SIGINT_action.sa_handler = SIG_IGN;

	SIGTSTP_action.sa_handler = catchSIGTSTP; 		// Catch it with the handler
	sigfillset(&SIGTSTP_action.sa_mask);
	SIGTSTP_action.sa_flags = SA_RESTART;			// Restart

	sigaction(SIGINT, &SIGINT_action, NULL);		// Initialize the sigs
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);
}

/*****************************************************************
** Function: catchSIGTSTP
** Description: The handler function for signal SIGTSTP. It checks
**		if background mode is off or on and then toggles it
*****************************************************************/
void catchSIGTSTP(int signo){
	char *message;
	// If background mode is off, turn it on
	if(background_mode == 1){
		background_mode = 0;
		message = "\nExiting foreground-only mode\n: ";
		write(STDOUT_FILENO, message, 32);
		fflush(stdout);
	}
	// If background mode is on, turn it off
	else if(background_mode == 0){
		background_mode = 1;
		message = "\nEntering foreground-only mode (& is now ignored)\n: ";
		write(STDOUT_FILENO, message, 52);
		fflush(stdout);
	}
}

/*****************************************************************
** Function: sh_loop
** Description: The loop that allows the user to keep inputting 
**		commands to the shell.
*****************************************************************/
void sh_loop(void){
	char **args;	
	char *input;
	pid_t *bg_pids = malloc(32 * sizeof(pid_t));
	int exit_status = 0, status, idx, i;
	// Infinite loop to gather input
	do{	
		fflush(stdout);
		printf(": ");
		fflush(stdout);
		// Read inputs
		input = sh_read_input();
		args = sh_get_args(input);
		// Execute command
		status = sh_execute(args, &exit_status, bg_pids);
		// Check for any bg processes
		check_for_bg_pid(bg_pids);

		// Reset the input string/args
		memset(input, 0, sizeof(input));
		memset(args, 0, sizeof(args));
	} while(status);
	// Free when done
	free(args);
	free(input);
	free(bg_pids);
}

/*****************************************************************
** Function: check_for_bg_pid
** Description: Checks if there are any background processes 
**		running and then checks if they are finished if
**		there are. If they are finished, it reaps the
**		child and prints a message saying how it finished
*****************************************************************/
void check_for_bg_pid(int *bg_pids){
	pid_t childPID;
	int i = 0, j, status;
	// Go into the loop when there is at least one bg process
	while(bg_pids[i] != 0){
		childPID = waitpid(bg_pids[i], &status, WNOHANG); 	// Check each process status
		if(childPID){ 						// If there is even a child
			if(WIFSIGNALED(status) != 0){			// If term by signal, print so
				printf("background pid %d is done: terminated by signal %d\n", bg_pids[i], WTERMSIG(status));	
				fflush(stdout);
			}
			else if(WIFEXITED(status != 0)){		// If exit normally, print so
				printf("background pid %d is done: exit value %d\n", bg_pids[i], WEXITSTATUS(status));
				fflush(stdout);
			}
			j = i;
			while(bg_pids[j] != 0){				// Remove the reaped process from the array of pids
				bg_pids[j] = bg_pids[j+1];
				j++;
			}
		}
		i++;
	}
}

/*****************************************************************
** Function: sh_read_input
** Description: Reads the input from the with getline() and puts 
**		returns the string containing it.
*****************************************************************/
char* sh_read_input(){
	char *input = NULL;
	ssize_t bufsize = 0;
	getline(&input, &bufsize, stdin);
	return input;
}

/*****************************************************************
** Function: sh_get_args
** Description: Gets an array containing the arguments input by 
**		user. It uses strtok() to separate the arguments
**		by using spaces and new lines as the delimiters.
*****************************************************************/
char** sh_get_args(char* buffer){
	// Init variables
	int bufsize = 64, idx = 0;
	char **args = malloc(bufsize * sizeof(char*));
	char *token;

	// Tokenize input
	token = strtok(buffer, " \n");
	while(token != NULL){ 			// While there are still args
		args[idx] = token;		// Store them into an array
		idx++;

		if(idx >= bufsize){
			bufsize += 64;
			args = realloc(args, bufsize * sizeof(char*));
			if(!args){
				fprintf(stderr, "Allocation error\n");
				fflush(stdout);
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \n");
	}
	
	args[idx] = NULL;			// Store the last idx as NULL
	idx = 0;
	while(args[idx] != NULL){
		printf("Arg %d: %s\n", idx, args[idx]);
		idx++;
	}

	// This deals with $$ input and replaces it with the PID. I probably could have put this in it's own function
	char *pch;
	int i;
	pid_t pid = getpid();
	char str_pid[32];
	sprintf(str_pid, "%d", pid);
	for(i = 0; i < idx; i++){
		pch = strstr(args[i], "$$");
		if(pch){
			strncpy(pch, str_pid, strlen(str_pid));
		}
	}
	return args;
}

/*****************************************************************
** Function: sh_execute
** Description: Looks at the first argument of the user input
**		(the command) and calls the corresponding function
**		accordingly. If it is not built in, it creates a 
**		fork() and uses execvp() to run the process.
*****************************************************************/
int sh_execute(char *args[], int *exit_status, pid_t *bg_pids){
	// Checks if empty command or if comment
	int i;
	if(args[0] == NULL){				// Do nothing when no input
		return 1;	
	}
	else if(args[0][0] == '#'){ 			// Do nothing when a comment
		return 1;
	}
	else if(strcmp(args[0], "cd") == 0){		// cd command
		return(sh_cd(args, exit_status));
	}
	else if(strcmp(args[0], "exit") == 0){		// exit command
		return(sh_exit(args));
	}
	else if(strcmp(args[0], "status") == 0){	// status command
		return(sh_status(exit_status));
	}
	else{						// any other command
		return(sh_execute_command(args, exit_status, bg_pids));	
	}
}

/*****************************************************************
** Function: sh_cd 
** Description: This is the cd command, it checks for no argument 
** 		or a tilde (~) after the cd to go to the HOME 
**		directory or it will just go to whatever directory
**		is directly after cd, ignoring any other arguments
*****************************************************************/
int sh_cd(char *args[], int *exit_status){
	int direr = -5;

	// Check for no argument for cd command or "~"
	if (args[1] == NULL || strcmp(args[1], "~") == 0){
		direr = chdir(getenv("HOME"));
		*exit_status = 0;
	}
	// Otherwise, just use the next argument after "cd"
	else{ 
		direr = chdir(args[1]);
		*exit_status = 0;
	}
	// If the directory does not exist, print err.
	if (direr == -1){
		printf("cd: %s: No such file or directory\n", args[1]);
		fflush(stdout);	
		*exit_status = 1;
	}
	return 1;
}

/*****************************************************************
** Function: sh_exit
** Description: A simply exit of the program. Using return 0 just 
** tells the loop to leave the loop and allow the program to end.
*****************************************************************/
int sh_exit(char *args[]){
	return 0;
}

/*****************************************************************
** Function: sh_status
** Description: This function just prints out the exit value or
**		signal of the last terminated process.
*****************************************************************/
int sh_status(int *status){
	int exitStatus, termSignal;
	// Check if exited
	if(WIFEXITED(*status) != 0){
		exitStatus = WEXITSTATUS(*status);
		printf("exit value %d\n", exitStatus);
		fflush(stdout);	
	}
	// Check if terminated	
	if(WIFSIGNALED(*status) != 0){
		termSignal = WTERMSIG(*status);
		printf("terminated by signal %d\n", termSignal);
		fflush(stdout);
	}
	return 1;
}

/*****************************************************************
** Function: sh_execute_command 
** Description: This function is way to big, and I appologize for 
** 		that. It does multiple things that should be split
** 		up into several functions such as checking for 
**		input or output files, checking for background
**		process key (&), setting the files for input or
**		output, setting the process to be a background
**		process and actually executing the process.
**		Normally I would split these all up into their own
**		functions, but I just want to get the assignment
**		turned in asap at this point.
*****************************************************************/
int sh_execute_command(char *args[], int *exit_status, pid_t *bg_pids){
	int exitStatus, termSignal, status, i = 0, j, inputFile, outputFile, result;
	pid_t pid, wpid;
	
	pid = fork();
	// Child process goes here
	if(pid == 0){
		// I set the handler to be default as I want foreground process to be killed on SIGINT
		// I'm basically assuming foreground
		SIGINT_action.sa_handler = SIG_DFL;
		sigaction(SIGINT, &SIGINT_action, NULL);
		i = 0;
		// This just counts how many args there are
		while(args[i] != NULL){
			i++;
		}
		i = i-1;
		// Here checks if its a background process
		if(strcmp(args[i], "&") == 0){
			// If it is, I set it back to ignoring the SIGINT signal
			SIGINT_action.sa_handler = SIG_IGN;
			sigaction(SIGINT, &SIGINT_action, NULL);
			
			args[i] = NULL;
			// Automatically set the input and output streams to /dev/null for background
			// If a file is specified, this will be overwritten later on in this function
			inputFile = open("/dev/null", O_RDONLY);
			if(inputFile == -1){
				perror("/dev/null");
				fflush(stdout);
				*exit_status = 1;
				exit(1);
			}
			result = dup2(inputFile, 0);
			// Error checking
			if(result == -1){
				perror("source dup2()");
				fflush(stdout);
				*exit_status = 1;
				close(inputFile);
				exit(1);
			}
			// Setting output to /dev/null
			outputFile = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(outputFile == -1){
				perror("/dev/null");
				fflush(stdout);
				*exit_status = 1;
				exit(1);
			}
			result = dup2(outputFile, 1);
			// Err checking
			if(result == -1){
				perror("source dup2()");
				fflush(stdout);
				*exit_status = 1;
				close(outputFile);
				exit(1);
			}
		}
		i = 0;
		while(args[i] != NULL){
			// Check for an input file
			if(strcmp(args[i], "<") == 0 && args[i+1] != NULL){
				// If so, redirect it
				inputFile = open(args[i+1], O_RDONLY);
				if(inputFile == -1){
					printf("cannot open %s for input\n", args[i+1]);
					fflush(stdout);
					*exit_status = 1;
					exit(1);
				}
				result = dup2(inputFile, 0);
				// Error checking
				if(result == -1){
					perror("source dup2()");
					*exit_status = 1;
					close(inputFile);
					exit(1);
				}
				j = i;
				// Remove the file args
				while(args[j] != NULL){
					args[j] = args[j+2];
					j++;
				}
				i--;
			}
			// Check for an output file
			if(strcmp(args[i], ">") == 0 && args[i+1] != NULL){
				// If so, redirect it
				outputFile = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(outputFile == -1){
					printf("cannot open %s for output\n", args[i+1]);
					fflush(stdout);
					*exit_status = 1;
					exit(1);
				}
				result = dup2(outputFile, 1);
				// Err checking
				if(result == -1){
					perror("source dup2()");
					fflush(stdout);
					*exit_status = 1;
					close(outputFile);
					exit(1);
				}
				j = i;
				// Removing file args
				while(args[j] != NULL){
					args[j] = args[j+2];
					j++;
				}
				i--;
			}
			i++;
		}
		// Actually executing command
		if(execvp(args[0], args) == -1){
			// If it returns anything, it didn't work
			printf("%s: command not found\n", args[0]);
			fflush(stdout);
		}
		exit(EXIT_FAILURE);
	}
	// Some error forking
	else if(pid < 0){
		perror("fork");
		fflush(stdout);
	}
	// Parent process goes here
	else{
		i = 0;
		while(args[i] != NULL){
			i++;
		}
		i = i-1;
		// Checks for background mode
		if(strcmp(args[i], "&") == 0 && background_mode == 0){
			// If so, it prints the pid of the bg process
			printf("background pid is %d\n", pid);
			fflush(stdout);
			j = 0;
			// Also adds said pid to an array of bg pids
			while(bg_pids[j] != 0){
				j++;
			}
			bg_pids[j] = pid;
		}
		// Otherwise, it is a foreground process, so the parent waits as normal
		else{
			do{
				wpid = waitpid(pid, &status, 0);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status)); // This prevents it from being interrupted by some signal, 
									    // it will keep waiting until the child has been exited
		}
	}
	if(WIFEXITED(status) != 0){
	}
	// This checks if it was terminated by signal 2 (CTRL+C), if so, print it out
	else if(WIFSIGNALED(status) != 0){
		termSignal = WTERMSIG(status);
		if(termSignal == 2){
			printf("terminated by signal %d\n", termSignal);
			fflush(stdout);
		}
	}

	*exit_status = status;
	return 1;
}
