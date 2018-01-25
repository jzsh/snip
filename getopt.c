#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int c;
	int i;
	int debug = 0;
	printf("optind:%d，opterr：%d\n",optind,opterr);
	printf("--------------------------\n");
	while((c = getopt(argc, argv, "l:b:d")) != -1) {
		switch(c) {
		case 'b':
			printf("backup %s\n", optarg);break;
		case 'l':
			printf("load %s\n", optarg);break;
		case 'd':
			printf("debug\n");debug++;break;
		defeult:
			printf("unknow parameter\n");
			exit(1);
		}
	}

	printf("----------------------------\n");
	printf("optind=%d,argv[%d]=%s\n",optind,optind,argv[optind]);

	argc -= optind;
	argv += optind;

	for(i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	return 0;
}
