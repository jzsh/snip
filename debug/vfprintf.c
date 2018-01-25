#include <stdarg.h>
#include <stdio.h>

void __nprintf(const char *fmt, ...)
{
	va_list ap;
	FILE *fp;
	if((fp = fopen("/tmp/log", "a")) == NULL)
		return;
	va_start(ap, fmt);
	vfprintf(fp, fmt, ap);
	fputs("\n", fp);
	fclose(fp);
	fp = NULL;
	va_end(ap);
}

int main(void)
{
	__nprintf("this is %d test", 9);
	return 0;
}
