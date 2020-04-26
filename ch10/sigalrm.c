/*
	sigint.c
	ctrl+c interrupt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void timer(int sig);

int main(int argc, char **argv)
{
	int state;

	struct sigaction act;
	act.sa_handler=timer;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;


	state = sigaction(SIGALRM, &act, 0);
	if(state != 0)
	{
		puts("sigaction() error ");
		exit(1);
	}

	alarm(5); // reserve alram after 5 seconds.
	while(1)
	{
		printf("holdposition\n");
		sleep(2);
	}
	return 0;
}

void timer(int sig)
{
	puts("it's the time!!\n");
	exit(0);
}
