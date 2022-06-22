#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include "client_fun.h"
#include "config.h"

int main()
{
    SockClient my_client;
    my_client.param_init("192.168.116.129");
    my_client.client_connect();
    my_client.client_communicate();
}