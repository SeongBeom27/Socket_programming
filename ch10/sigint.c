/*
	sigint.c
	ctrl+c interrupt
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// signal function
// void (*signal(int signum, void (*func)(int)))(int);

void handler(int sig);
int main(int argc, char **argv)
{
	int state;
	int num = 0;

	signal(SIGINT, handler);
	while(1)
	{
		printf("%d : holdposition \n", ++num);
		sleep(2);
		if(num > 5) break;
	}
	return 0;
}

void handler(int sig)
{
	signal(SIGINT, handler);
	printf("Transfered signal is %d \n", sig);
}
