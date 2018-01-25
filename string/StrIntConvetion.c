#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PT printf("str(\"%s\") --> int(%d)\n", s, i);
int main()
{
	int i;
	char *s = NULL;

	s = "9";
	i = atoi(s);
	PT;
	s = "";
	i = atoi(s);
	PT;

	s = NULL;
// 	i = atoi(s); // segment fault
// 	PT;
	i = -1;
	i = strtoul(s, 0, 10);
// 	PT;
}
