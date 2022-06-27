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
#include"diffiehellman_work.h"

DiffieHellmanInfo::DiffieHellmanInfo()
{
    P = BN_new();
    g = BN_new();
    private_key = BN_new();
    public_key = BN_new();
    Key = BN_new();
    int w = 5;
    BN_add_word(g,w);
    
}

void DiffieHellmanInfo::get_p(int bits)
{
    BN_generate_prime_ex(P,bits,0,NULL,NULL,NULL);
}


void DiffieHellmanInfo::get_private_key()
{
    BN_rand_range(private_key,P);
}

void DiffieHellmanInfo::get_public_key()
{
    BN_CTX* ctx = BN_CTX_new();
    BN_mod_exp(public_key,g,private_key,P,ctx);
    BN_CTX_free(ctx);
}

void DiffieHellmanInfo::get_Key(BIGNUM *server_public_key)
{
    BN_CTX* ctx = BN_CTX_new();
    BN_mod_exp(Key,server_public_key,private_key,P,ctx);
    BN_CTX_free(ctx);
}