#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#ifndef CONFIG
#define CONFIG

const int Port = 8888;
const char server_ip[] = "127.0.0.1";
const int max_buff = 1024;
// pthread_mutex_t g_mutext;

#endif