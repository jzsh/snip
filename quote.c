#include <stdio.h>
static void uci_print_value(FILE *f, const char *v)
{
	fprintf(f, "'");
	while (*v) {
		if (*v != '\'')
			fputc(*v, f);
		else
			fprintf(f, "'\\''");
		v++;
	}
	fprintf(f, "'");
}
int main(int argc, char **argv)
{
	char *a = NULL;
	char b;
	char *str = "\\\"abc'";
	printf("string: %s\n", str);
	uci_print_value(stderr, "a'b");
	printf("\n");

	printf("argc = %d\n", argc);
	a = argv[1];
	printf("argv[1] = %s\n", argv[1]);
	printf("argv[1] = %d\n", *(argv[1]+1));
}
