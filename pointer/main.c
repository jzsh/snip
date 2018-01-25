#include <stdio.h>
#include <malloc.h>

void section_iter(int op, char *rtn) {
	if(op == 1) {
		rtn = "123";
	}
 	else
 		rtn = "World";
	return;
}
int main(void) {
	char *string = "Hello";
	char *ptr = string;
	char *rtn = NULL;
// 	printf("%s\n", ptr);
// 	free(ptr);

	section_iter(0, NULL);
	section_iter(0, rtn);
	printf("%s\n", rtn);
	return 0;


}

