/*
	fork.c
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int data = 10;

	pid = fork();			// child process generation
	if(pid == -1)
	{
		printf("fork fault, process id : %d \n", pid);
	}
	printf("fork success, process id : %d \n", pid);

	if(pid == 0)		/* if child process */
		data += 10;
	else
		data -= 10;		/* if parent process */

	printf("data : %d \n", data);

	return 0;
}
