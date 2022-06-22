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

int main()
{
    SockServer my_server;
    my_server.param_init();
    my_server.server_init();
    my_server.server_communicate();
    return 0;
}