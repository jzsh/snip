#include "util.h"

void info(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

void error(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

void fail(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);

	exit(1);
}

struct TimeInfo {
	double startTime;
	char event[256];
	struct TimeInfo *next;
}; 

struct TimeInfo *head = NULL;

double currtime()
{
	struct timeval t;  
	gettimeofday(&t, NULL);  
	long timeuse = 1000000 * t.tv_sec + t.tv_usec;  
	return timeuse/1000000.0;
}

void timer_start(const char *event)
{
	struct TimeInfo *info = NULL;
	info = malloc(sizeof(struct TimeInfo));
	info->startTime = currtime();
	strncpy(info->event, event, 256);
	info->next = head;
	head = info;
}

double timer_stop(const char *event)
{
	struct TimeInfo *p = head, *next, *prev = head;
	double interval = 0;
	while(p != NULL)
	{
		next = p->next;
		if(!strcmp(p->event, event))
		{
			interval = currtime() - p->startTime;
			if(p == head)
				head = p->next;
			else
				prev->next = p->next;
			free(p);
			break;
		}
		prev = p;
		p = next;
	}
	return interval;
}



