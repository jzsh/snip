#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void func()
{
	printf("hello\n");
}

int main()
{
	signal(SIGALRM, func);
	while(1)
	{
		sleep(2);
		kill(getpid(), SIGALRM);
	}
	return 0;
}
