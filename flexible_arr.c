#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

struct data {
	int a;
	char b;
	char c[];
};

int main()
{
	struct data *d;
	int i, max;

	d = malloc(sizeof(struct data));
	printf("size of : %d\n", sizeof(struct data));
	d->a = 10;
	d->b = 'h';
	printf("%p, %d\n", &d->a, d->a);
	printf("%p, %c\n", &d->b, d->b);
	for(i = 0, max = 0; max < MAX; i = i + 1024, max++) {
		d->c[i] = 'g';
		printf("%d: %p, %c\n", max, &d->c[i], d->c[i]);
	}
}
