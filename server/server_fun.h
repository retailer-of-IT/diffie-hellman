#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#ifndef SERVER_FUN
#define SERVER_FUN
 
struct pthread_data{
    struct sockaddr_in client_addr;
    int sock_fd;
};

void *serveForClient(void * arg);

class SockServer
{
    public:
    int sock_fd;
    struct sockaddr_in mysock;
    struct pthread_data pdata;
    pthread_t pt;
    socklen_t sin_size;
    struct sockaddr_in client_addr;
    int new_fd;
    SockServer();
    void param_init();
    void server_init();
    void server_communicate();

};



#endif