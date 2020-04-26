/*
	wait.c
*/
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid, child;

	int data = 10;
	int state;

	pid = fork();
	if(pid < 0)
	{
		printf("fork fault process id : , %d \n", pid);
	}
 	
	printf("fork success process id : %d \n", pid);
	
	if(pid ==0) data += 10;	// if child process
	else{					// if parent process
		data -= 10;
		child = wait(&state);
		printf("child process id = %d \n", child);
		// printing out child return return value when that's exit by using WEXITSTATUS
		printf("return value : %d \n", WEXITSTATUS(state));
		sleep(20);
	}

	printf("data :  %d \n", data);
	return 0;
}
