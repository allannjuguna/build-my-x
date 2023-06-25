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
#include <sys/wait.h>

/* Creating a simple fork */
int main() {
	printf("This is the main function of the program\n");

	int stat_loc;


	pid_t child_pid=fork();
	if (child_pid == 0){ /*Child process*/
		printf("Child :: Current PID %d and Child PID : %d\n", getpid(),child_pid);
		sleep(2);
	}else{ /*Parent process*/
		// We want to wait for the child process
		pid_t wait_result=waitpid(child_pid,&stat_loc,WUNTRACED);
		printf("Parent :: Current PID %d and Child PID : %d\n", getpid(),child_pid);

        if (WIFEXITED(stat_loc)) {
            // Child process exited normally
            int exit_status = WEXITSTATUS(stat_loc);
            printf("Child process %d terminated with exit status %d\n", wait_result, exit_status);
        } else if (WIFSIGNALED(stat_loc)) {
            // Child process terminated by a signal
            int signal_number = WTERMSIG(stat_loc);
            printf("Child process %d terminated by signal %d\n", wait_result, signal_number);
        }



	}

	return 0;
}



/*This is the main function of the program
Child :: Current PID 42491 and Child PID : 0
Parent :: Current PID 42490 and Child PID : 42491*/