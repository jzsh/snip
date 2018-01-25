#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
	int i = 0;
	char *str="hello";
	if(strcmp(NULL, str) == 0) {
		printf("equal\n");
	}
	assert(i);
	return 0;
}
