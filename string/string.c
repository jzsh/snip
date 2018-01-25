#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[10] = "Hello";
	char *str2 = "world";
	char *str0 = NULL;
	printf("len = %d\n", strlen(str0));

// 	strcpy(str, NULL);
// 
// 	printf("%s\n", str);
	return 0;
}
