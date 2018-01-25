#include <stdio.h>
#include <stdarg.h>
void printf1(char *fmt, ...)
{
	FILE *fp = stderr;
	va_list ap;
	va_start(ap, fmt);
	vfprintf(fp, fmt, ap);
	fputs("\n", fp);
	va_end(ap);
}
