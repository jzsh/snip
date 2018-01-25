#include <stdio.h>
#include <string.h>

#define STRCMP(_str1, _str2) \
	(if(!_str1) return -1; \
	strcmp(_str1, _str2);)
#define LINE_SZ 128
int main() {
	int a;
	FILE *fp = NULL;
	char *str = "avc(avd_webfilter)";
	char line[LINE_SZ];
	a = atoi("123.4");
	printf("a=%d\n", a);

	fp = fopen("log", "r");
	fgets(&line[0], LINE_SZ, fp);
	printf("line: %s", line);
// 	a = atoi(str);
// 	printf("a=%d\n", a);

	printf("%s\n", strchr(str, '('));

	return 0;
}
