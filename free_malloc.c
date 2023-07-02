#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct human {
	int age;
	char name[64];
};
typedef struct human human_t;
int main()
{
	char *test = NULL;
	free(test);
	printf("test\n");


	human_t *h = NULL;
	h = (human_t *)malloc(sizeof(human_t));
	h->age = 20;
	strcpy(h->name, "Tom");
	free(h); // free a user defined type

}
