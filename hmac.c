#include "sha1.h"
#include <stdio.h>


void hmac_sha1(uint8_t *data, unsigned long length, uint8_t *key, unsigned int keylen, uint8_t *mac_value)
{
    uint8_t ikey[KEY_IOPAD_SIZE], okey[KEY_IOPAD_SIZE];
    uint8_t hash[SHA1_DIGEST_SIZE];
    sha1_ctx_t ctx;
    int i;

    if(keylen <= KEY_IOPAD_SIZE)
    {
        memset(ikey, 0, KEY_IOPAD_SIZE);
        memset(okey, 0, KEY_IOPAD_SIZE);
        memcpy(ikey, key, keylen);
        memcpy(okey, key, keylen);
    }
    else
    {
        sha1Init(&ctx);
        sha1Update(&ctx, key, keylen);
        sha1_finish(&ctx, ikey);
        memcpy(okey, ikey, KEY_IOPAD_SIZE);
    }

    for(i = 0; i < KEY_IOPAD_SIZE; i++)
    {
        ikey[i] = ikey[i] ^ 0x36;
        okey[i] = okey[i] ^ 0x5c;
    }

    sha1Init(&ctx);
    sha1Update(&ctx, ikey, KEY_IOPAD_SIZE);
    sha1Update(&ctx, data, length);
    sha1_finish(&ctx, hash);

    sha1Init(&ctx);
    sha1Update(&ctx, okey, KEY_IOPAD_SIZE);
    sha1Update(&ctx, hash, SHA1_DIGEST_SIZE);
    sha1_finish(&ctx, mac_value);
}
