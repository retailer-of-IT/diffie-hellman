#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<errno.h>
#include <arpa/inet.h>
#include "client_fun.h"
#include "config.h"

SockClient::SockClient()
{

}

void SockClient::param_init(const char* ip)
{
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);//初始化socket
    if(sock_fd == -1)
    {
        printf("%s\n",strerror(errno));
        exit(1);
    }
    bzero(&server_addr, sizeof(server_addr));//编辑服务端地址信息
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(Port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
}

void SockClient::client_connect()
{
    int tmp = connect(sock_fd, (struct sockaddr *)(&server_addr),sizeof(struct sockaddr));//连接服务端socket
    if(tmp == -1)
    {
        printf("%s\n",strerror(errno));
        exit(2);
    }
}

void SockClient::client_communicate()
{
    while(true){
        fgets(sendbuf, sizeof(sendbuf), stdin);
        send(sock_fd, sendbuf, strlen(sendbuf), 0);
        if(strcmp(sendbuf, "exit\n") == 0)
            break;
        recv(sock_fd, recvbuf, sizeof(recvbuf), 0);
        fputs(recvbuf, stdout);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    close(sock_fd);
    return;
}
