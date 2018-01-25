#include <stdio.h>
struct module {
	signed   char ma : 2;
	unsigned char mb : 2;
	unsigned char mc : 1;
	signed   char md : 1;
};

int main()
{
	struct module m = {
		.ma = 1,
		.mb = 3,
		.mc = 1,
		.md = 1,
	};
	printf("size  of m = %d\n", sizeof(m));
	printf("m = {ma = %d, mb = %d, mc = %d, md = %d}\n", m.ma, m.mb, m.mc, m.md);
}
