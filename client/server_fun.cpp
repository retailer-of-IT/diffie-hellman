#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include "server_fun.h"
#include "config.h"

void *serveForClient(void *arg)
{
    struct pthread_data *pdata = (struct pthread_data*)arg;
    int new_fd = pdata->sock_fd;
    char recvbuf[max_buff];
    char sendbuf[max_buff] = "recv successfully.\n";
    while(true)
    {
        recv(new_fd, recvbuf, sizeof(recvbuf), 0);
        fputs(recvbuf,stdout);
        strcpy(sendbuf, recvbuf);
        if(strcmp(recvbuf,"exit\n") == 0){
            send(new_fd, "connection close.\n", sizeof("connection close.\n"), 0);
            break;
        }
        send(new_fd, sendbuf, sizeof(sendbuf), 0);
        memset(recvbuf,0,sizeof(recvbuf));
    }
    pthread_exit(0);
}

SockServer::SockServer()
{

}
void SockServer::param_init()
{
    sin_size = sizeof(struct sockaddr_in);
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if (sock_fd < 0)
    {
        perror("Socket error\n");
        exit(1);
    }
    memset(&mysock, 0, sizeof(mysock));
    mysock.sin_family = AF_INET;
    mysock.sin_port = htons(Port);
    mysock.sin_addr.s_addr = INADDR_ANY; //TODO1
}

void SockServer::server_init()
{
    if((bind(sock_fd,(struct sockaddr *)&mysock,sizeof(struct sockaddr))) != 0)
    {
        perror("bind error\n");
        exit(2);
    }
    if(listen(sock_fd,5) != 0)
    {
        perror("listen error\n");
        exit(3);
    }
    printf("listening...\n");
}

void SockServer::server_communicate()
{
     while(true)
     {
        //accpet
        new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
        printf("accept\n");
        pdata.client_addr = client_addr;
        pdata.sock_fd = new_fd;
        pthread_create(&pt, NULL, serveForClient, (void *)&pdata);
    }
    close(new_fd);
    close(sock_fd);
}