#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void show_all_env()
{
	char **p = environ;
	while(*p) {
	fprintf(stderr, "%s\n", *p);
		p++;
	}
}
int main()
{
	show_all_env();
	printf("HOME=%s\n", getenv("HOME"));
	putenv("HOME=/root");
	printf("HOME=%s\n", getenv("HOME"));
	return 0;
}
