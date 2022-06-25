#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <openssl/bn.h>
#include "config.h"

#ifndef DIFFIEHELLMAN_WORK
#define DIFFIEHELLMAN_WORK

class DiffieHellmanInfo
{
    public:
    BIGNUM *P;
    BIGNUM *g;
    BIGNUM *private_key;
    BIGNUM *public_key;
    BIGNUM *Key;
    DiffieHellmanInfo();
    void get_p(int bits);
    void get_private_key();
    void get_public_key();
    void get_Key(BIGNUM *server_public_key);
};

#endif
