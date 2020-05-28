/*
   pipe1.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 30

int main(int agrc, char **argv)
{
	int fd[2];
	char buffer[BUFSIZE];
	pid_t pid;
	int state;

	state = pipe(fd);
	if(state == -1)
	{
		puts("pipe error()\n");
		exit(1);
	}
	
	pid = fork();

	if(pid == -1)
	{
		puts("fork error()\n");
		exit(1);
	}
	else if(pid == 0)
	{
		write(fd[1], "Good\n", 6);				// send message parent to child
	}
	else{
		read(fd[0], buffer, BUFSIZE);			// receive meessage child from parent
		puts(buffer);
	}

	return 0;
}
