/*
*  @author: zerofrost🦊
*  @date: 2023-6-25
*  @compilation: gcc file.c -o file
*  @description: Creating a simple unix shell
*/

/*
* Forks will help prevent crashing of the shell in case of an error 
* They will also allow independent commands to have their own process blocks (isolation) thus helping in fault torelance
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// #define SHELLNAME "$"
#define HOSTNAME "unixsh"
#define USERNAME "shell"
#define DELIMETER " "
#define BUFFER 100


void sigint_handler(){
	fprintf(stderr, "\nExit invoked. Closing the shell\n");
	exit(EXIT_SUCCESS);
}

int main(int argc,char **argv){
	char prompt[BUFFER];
	ssize_t stat_loc;
	char* SHELLNAME="$";
	pid_t child_fork=0;
	char *command[10];
	signal(SIGINT,sigint_handler);

	uid_t uid=getuid();
	if (uid == 0){
		SHELLNAME="#";
	}

while (1){
	/* Accepting the user input */
	printf("\n%s@%s %s ",USERNAME,HOSTNAME,SHELLNAME);
	fgets(prompt,BUFFER,stdin);

	/* Cleaning the user input */
	strncpy(prompt,strtok(prompt,"\n"),BUFFER);

	if (strstr(prompt,"exit") != NULL){
		sigint_handler();
	}

	/*Splitting the input string into an array*/
	int index=0;
	char *parsed = strtok(prompt, DELIMETER);
	while (parsed != NULL) {
	    command[index] = parsed;
	    index++;
	    parsed = strtok(NULL, DELIMETER);
	}
	command[index] = NULL;

	if (strcmp(command[0],"cd") == 0){
		if(chdir(command[1]) < 0){
			fprintf(stderr, "An error occurred while changing directory\n");
		}
		continue;
	}

	child_fork=fork();
	if (child_fork == 0){
		// This is the child process
	    ssize_t retcode=execvp(command[0],command);	
	    if (retcode < 0){
	    	fprintf(stderr, "An error occurred while running command '%s'\n", prompt);
	    	exit(EXIT_FAILURE);
	    }
		// printf("Child process spawned with pid of %d. Return of exec is %d\n",getpid(),retcode);
	}else{ 
		// This is the parent process
		// printf("Main process is running with pid of %d and with a child with pid %d\n",getpid(), child_fork );
		waitpid(child_fork,&stat_loc,0);
	}

}
	return 0;
}

