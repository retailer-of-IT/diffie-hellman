#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<errno.h>
#include <openssl/bn.h>
#include"config.h"
#include"diffiehellman_work.h"
#ifndef CLIENT_FUN
#define CLIENT_FUN
class SockClient
{
    public:
    int sock_fd;
    char buf[max_buff], sendbuf[max_buff], recvbuf[max_buff];
    struct sockaddr_in server_addr;
    DiffieHellmanInfo client_key_info;
    SockClient();
    void param_init(char* ip);
    void client_connect();
    void client_communicate();
    void diffie_hellman_client();
};

#endif
