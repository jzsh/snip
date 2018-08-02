
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 9999
#define BUFFER_SIZE 1024
int main()
{
        int sd;
        struct sockaddr_in addr;
        //int addr_len=sizeof(addr);
        char buffer[BUFFER_SIZE]="";
        char rbuffer[BUFFER_SIZE]="";

        if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
        {
                perror("socket error");
                return -1;
        }
        bzero(&addr,sizeof(addr));

        addr.sin_family=AF_INET;
        addr.sin_port=htons(PORT);
        addr.sin_addr.s_addr=htonl(INADDR_ANY);

        if(connect(sd,(struct sockaddr *)&addr,sizeof(addr))<0)
        {
                perror("connect error");
                return -1;
        }
        while(strcmp(buffer,"q")!=0)
        {
                scanf("%s",buffer);
                send(sd,buffer,strlen(buffer),0);
                recv(sd,rbuffer,BUFFER_SIZE,0);
                printf("message:%s\n",rbuffer);
        }
        return 0;
}


