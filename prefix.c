#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*
	inet_pton()
	inet_ntop()
	inet_aton()
	inet_ntoa()
*/

int main()
{

	const char *network = "255.255.254.0";
	uint32_t n;
	struct in_addr net;
	inet_aton(network, &net);
	printf("%d\n", net.s_addr);
	inet_pton(AF_INET, network, &n);
	int i = 0;
	n=htonl(net.s_addr);
	printf("n = %u\n", n);
	while (n > 0) {
			n = n << 1;
			i++;
	}

	printf("network = %s, suffix = %d\n", network, i);
}
