#include <time.h>
#include <stdio.h>

int main() {

	time_t now;
	time_t timep;
	struct tm *tm_now;
	time(&now);
	tm_now = localtime(&now) ;

	printf("now datetime: %d-%d-%d %d:%d:%d\n",
	tm_now->tm_year+1900, tm_now->tm_mon+1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);

	printf("time() : %d \n", (int)now);
	timep = mktime(tm_now);
	printf("time()->localtime()->mktime():%d\n", (int)timep);
}
