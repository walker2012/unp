#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	//while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
	while ((pid = wait(&stat) > 0))
		printf("child %d terminated\n", pid);
	return;
}
