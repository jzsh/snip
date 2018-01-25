#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	if((pid = fork()) == 0) {
		printf("child[%d]\n", getpid());
		exit(0);
	}
	// wait();
	printf("parent[%d]\n", getpid());
	sleep(10);
	return 0;
}
