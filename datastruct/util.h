#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <malloc.h>
#include <sys/time.h>

void info(const char *fmt, ...);
void error(const char *fmt, ...);
void fail(const char *fmt, ...);
void timer_start(const char *event);
double timer_stop(const char *event);
