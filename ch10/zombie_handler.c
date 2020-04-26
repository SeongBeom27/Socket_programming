/*
   zombie_handler by using signal
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void z_handler(int sig);

int main(int argc, char **argv)
{
	pid_t pid;
	int state, i;

	struct sigaction act;
	act.sa_handler= z_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	state = sigaction(SIGCHLD, &act, 0);		// signal handler registeration
	if(state != 0)
	{
		puts("sigaction() error ");
		exit(1);
	}

	pid = fork();
	if(pid == 0)
	{
		// getpid() return process that is excuting now
		printf("child process generation : %d \n", getpid());
		exit(3);
	}
	else{
		// parent process have to exit later than child process to prevent zombie process generation
		sleep(3);
	}

	return 0;
}

void z_handler(int sig)
{
	pid_t pid;
	int rtn;
	// waitpid func. gets return value of child process. also Concern situation exited several child process while processing repeatibly in while
	while((pid = waitpid(-1, &rtn, WNOHANG)) > 0 ){
		printf("Die Zombie process ID : %d\n", pid);
		printf("return data : %d \n\n", WEXITSTATUS(rtn));
	}

}
