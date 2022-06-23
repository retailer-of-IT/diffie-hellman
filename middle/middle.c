#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/dh.h>
#include <string.h>

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}
int generate(void)
{
    EVP_PKEY* params;//参数
    EVP_PKEY_CTX* kctx;
    EVP_PKEY *dhkey;
    /* 使用内置参数 */
    if(NULL == (params = EVP_PKEY_new())) handleErrors();
    if(1 != EVP_PKEY_assign(params, EVP_PKEY_DHX, DH_get_2048_256())) handleErrors();

    /* 为密钥生成创建上下文 */
    if(!(kctx = EVP_PKEY_CTX_new(params, NULL))) handleErrors();

    /* 生成新密钥 */
    if(1 != EVP_PKEY_keygen_init(kctx)) handleErrors();
    if(1 != EVP_PKEY_keygen(kctx, &dhkey)) handleErrors();

    /* 可选：如果你想检查你的私钥，这很有用*/
    BIO* fp = BIO_new_fp(stdout, BIO_NOCLOSE);
    EVP_PKEY_print_private(fp, dhkey, 0, NULL);
    return 0;
}
int main()
{
    generate();
    return 0;
}