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
#include <openssl/bn.h>
#include "client_fun.h"
#include "config.h"
#include"diffiehellman_work.h"

SockClient::SockClient()
{

}

void SockClient::param_init(char* ip)
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
    printf("init success\n");
}

void SockClient::client_connect()
{
    int tmp = connect(sock_fd, (struct sockaddr *)(&server_addr),sizeof(struct sockaddr));//连接服务端socket
    if(tmp == -1)
    {
        printf("%s\n",strerror(errno));
        exit(2);
    }
    printf("connect success\n");
}

void SockClient::client_communicate()
{
    diffie_hellman_client();
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

void SockClient::diffie_hellman_client()
{
    client_key_info.get_p(512);
    char *P  = NULL;
    P = BN_bn2dec(client_key_info.P);
    strcpy(sendbuf,P);
    send(sock_fd,sendbuf,strlen(sendbuf),0);
    memset(sendbuf, 0, sizeof(sendbuf));
    client_key_info.get_private_key();
    client_key_info.get_public_key();
    char *client_public_key = NULL;
    client_public_key = BN_bn2dec(client_key_info.public_key);
    strcpy(sendbuf,client_public_key);
    send(sock_fd,sendbuf,strlen(sendbuf),0);
    memset(sendbuf, 0, sizeof(sendbuf));
    recv(sock_fd,recvbuf,strlen(recvbuf),0);
    printf("%s",recvbuf);
    BIGNUM *server_public_key = BN_new();
    BN_dec2bn(&server_public_key,recvbuf); //TODO2
    client_key_info.get_Key(server_public_key);
    char *Key = NULL;
    Key = BN_bn2dec(client_key_info.Key);
    printf("%s",Key);
    OPENSSL_free(Key);
    OPENSSL_free(P);
    OPENSSL_free(client_public_key);
}
