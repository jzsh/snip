#include <stdio.h>
#include <stdarg.h>
#define INFO_LOG_STDERR (1<<0)
#define INFO_LOG_STDLOG (1<<1)
static int loglevel = 0;
void info(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	if((loglevel & INFO_LOG_STDERR) != 0) {
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, "\n");
	}
	va_end(ap);

	if((loglevel & INFO_LOG_STDLOG) != 0) {
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, "\n");
	}
	va_end(ap);

}
enum
{
	UCI_OK = 0,
	UCI_ERR_MEM,
	UCI_ERR_INVAL,
	UCI_ERR_NOTFOUND,
	UCI_ERR_IO,
	UCI_ERR_PARSE,
	UCI_ERR_DUPLICATE,
	UCI_ERR_UNKNOWN,
	UCI_ERR_LAST
};
/*
 * functions for debug and error handling, for internal use only
 */
#define UCI_DEBUG
#ifdef UCI_DEBUG
#define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
#else
#define DPRINTF(...)
#endif

/*
 * throw an uci exception and store the error number
 * in the context.
 */
#define UCI_THROW(ctx, err) do { 	\
	DPRINTF("Exception: %s in %s, %s:%d\n", #err, __func__, __FILE__, __LINE__); \
} while (0)
void main(void)
{
	loglevel |= INFO_LOG_STDLOG;
	info("test %d", 1);
	UCI_THROW(0, UCI_ERR_INVAL);

}
