#include <stdio.h>
#include <signal.h>

static void sig_usr(int);

int main()
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		printf("cannot catch SIGUER1\n");
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		printf("cannot catch SIGUSR2");
	for(;;)
		pause();
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
		printf("recrived SIGUSR1\n");
	else if(signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("received other signal: %d\n", signo);
}
