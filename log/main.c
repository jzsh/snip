// https://www.gnu.org/software/libc/manual/html_node/openlog.html

#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>

void main(void)
{
	openlog ("mylibrary", 0, 0);
	

	int n = 0;	
	unsigned char mes[64];
	while(1) {
		syslog(LOG_INFO, "[%d] This is a test message", n);
		n++;
		sleep(2);
		closelog ();
	}
	
}
