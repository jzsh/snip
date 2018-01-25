#include <stdio.h>

char *test(int a) {
	char *str = "123";
	if(a == 1)
		return str;
	else {
		printf("it is null\n");
		return NULL;
	}
	
}
int main(void)
{
	printf("%s\n", test(1));
	test(0);
	printf("%s", test(0));
	test((int)NULL);
	return 0;
}
