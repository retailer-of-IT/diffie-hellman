#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<errno.h>
#ifndef CLIENT_FUN
#define CLIENT_FUN
class SockClient
{
    public:
    int sock_fd;
    char buf[1024], sendbuf[1024], recvbuf[1024];
    struct sockaddr_in server_addr;
    SockClient();
    void param_init(char* ip);
    void client_connect();
    void client_communicate();
};

#endif
