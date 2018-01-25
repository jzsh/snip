#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define RBUF_SZ 512
#define BUF_SZ 512
#define SERV_PORT 7777
#define SERV_IP "127.0.0.1"

int do_something(int client_sock)
{
	/* file to send */
	char *filename = "send.dat";
	FILE *fp = fopen(filename, "rb");
	char buffer[BUF_SZ];
	int nCount;
	if(fp == NULL) {
		return -1;
	}
	while((nCount = fread(buffer, 1, BUF_SZ, fp)) > 0)
	{
		write(client_sock, buffer, nCount);
	}
	fclose(fp);
	/* when done, send FIN */
	shutdown(client_sock, 1);
	/* block */
	read(client_sock, buffer, BUF_SZ);
}

int main(int argc, char **argv)
{
	int on = 1;
	int bufDepth;
	int bufLen;
	struct sockaddr_in serv_addr;

	/* create a socket */
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	/* allows to bind on the same local address even if the socket is
	 * in TIME_WAIT state */
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	/* buffer length */
	getsockopt(serv_sock, SOL_SOCKET, SO_SNDBUF, (int *)&bufDepth, &bufLen);
	printf("Socket buffer length:%d\n", bufDepth);

	//将套接字和IP、端口绑定
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family      = AF_INET;               /* 使用IPv4地址 */
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);     /* Any incoming interface */
	serv_addr.sin_port        = htons(SERV_PORT);      /* 端口 */

	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("Bind failed\n");
		return -1;
	}
	//进入监听状态，等待用户发起请求
	listen(serv_sock, 20);
	printf("Listen done\n");

	int client_sock;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int recvLen;
	char recvBuf[RBUF_SZ];
	while(1) {
		//接收客户端请求
		client_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		printf("Accept!\n");

		/* do something */
		do_something(client_sock);

		close(client_sock);
	}

	//关闭套接字
	close(serv_sock);

	return 0;
}


void print_sa_data(struct sockaddr_in serv_addr)
{
	struct sockaddr *p = NULL;
	int n = 0;
	p = (struct sockaddr *)&serv_addr;
	printf("s_addr = %d\n", serv_addr.sin_addr.s_addr);
	printf("sin_port = %d\n", ntohs(serv_addr.sin_port));

	for(n = 0; n < 14; n++)
		fprintf(stderr, "sa_data[%d] = %X\n", n, (unsigned char)(p->sa_data[n]));
}
