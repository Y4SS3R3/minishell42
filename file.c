#include <stdio.h>
#include <unistd.h>
# include <sys/wait.h>

int main()
{
	int pid = fork();
	int status = 0;
	if (pid)
	{
		wait(&status);
		printf("Status of momo [%d]\n", status);
	}
	printf("Hi, im a process, my pid is [%d] my parent pid is [%d]\n", getpid(), getppid());
	printf("PID [%d]\n", pid);
}
