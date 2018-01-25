#include <stdio.h>
#include <unistd.h>

void main(void)
{
	int i;
	int j;
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 5; j++ ) {
			if(j == 2) {
				sleep(2);
				goto if_loop;
			}
			printf("current=%d, %d\n", i, j);
		}
		if_loop:
			continue;
	}
}
