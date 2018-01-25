#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SZ 512
#define SERV_IP "127.0.0.1"
#define SERV_PORT 7777

void test_function(void);

int do_something(int client_sock)
{
	char *filename = "recv.dat";
	FILE *fp = fopen(filename, "wb");
	if(fp == NULL) {
		printf("Can not open file\n");
	}
	int nCount;
	char buffer[BUF_SZ];
	while((nCount = read(client_sock, buffer, BUF_SZ)) > 0) {
		fwrite(buffer, 1, nCount, fp);
	}
	puts("File transfer success!");
	fclose(fp);
}
int main(int argc, char **argv)
{
	if(argc > 1) {
		if(!strcmp(argv[1], "test")) {
			test_function();
			return 0;
		} else if(!strcmp(argv[1], "data")) {
			printf("get data from server\n");
		}
	}
	//创建套接字
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	//向服务器（特定的IP和端口）发起请求
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));        //每个字节都用0填充
	serv_addr.sin_family = AF_INET;                  //使用IPv4地址
	serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);  //具体的IP地址
	serv_addr.sin_port = htons(SERV_PORT);	         //端口
	while(1) {
		if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == 0) {
			printf("Connect to server\n");
			break;
		}
		printf("Failed to connect\n");
		close(sock);
		sleep(1);
		sock = socket(AF_INET, SOCK_STREAM, 0);
	}
	do_something(sock);

	//关闭套接字
	close(sock);

	return 0;
}


int hostname(char *name)
{
	char   *ptr, **pptr;
	struct hostent *hptr;
	char   str[32];
	ptr = name;

	if((hptr = gethostbyname(ptr)) == NULL)
	{
		printf(" gethostbyname error for host:%s\n", ptr);
		return 0;
	}

	printf("official hostname:%s\n",hptr->h_name);
	for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		printf(" alias:%s\n",*pptr);

	switch(hptr->h_addrtype)
	{
		case AF_INET:
		case AF_INET6:
			pptr=hptr->h_addr_list;
			for(; *pptr!=NULL; pptr++)
				printf(" address:%s\n",
					   inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
			printf(" first address: %s\n",
					   inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str)));
		break;
		default:
			printf("unknown address type\n");
		break;
	}

	return 0;
}
void test_function(void) {
	printf("test hostname function\n");
	hostname("www.baidu.com");
}

