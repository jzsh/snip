#include <stdio.h>
#include <malloc.h>

void read_sub2(int *spoint[]) {
	int *ptr = NULL;
	ptr = (int *) malloc(sizeof(int)*3);
	*ptr = 99;
	*(ptr+1)=87;
	*(ptr+2)=22;
	*spoint=ptr;
}

int main(void)
{

	int i = 0;
	int *spoint;
	read_sub2(&spoint);
	for(i = 0; i<3; i++) {
		printf("%d\n", spoint[i]);
	}



	printf("\n------------------------------\n");
	int a[5] = {2,4,6,8,10};
	printf("size of array a: %d\n", sizeof(a));
	printf("a: %p\n", a);
	printf("a+1: %p\n", a+1);
	printf("&a: %p\n", &a);
	printf("&a+1: %p\n", &a+1);
	int *p = &a[0];
	printf("a = {");
	for(i=0;i<5;i++) {
		printf("%d, ", a[i]);
	}
	printf("}\n");
	printf("p[0] = %d\n", p[0]);
	printf("p[4] = %d\n", p[4]);
	printf("p[5] = %d\n", p[5]);
	printf("*p = %d\n", *p);
	printf("*p+1 = %d\n", *p+1);
	printf("*(p+1) = %d\n", *(p+1));
	printf("*(p+4) = %d\n", *(p+4));
	printf("*(p+5) = %d\n", *(p+5));

	return 0;
}
