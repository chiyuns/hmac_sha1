#ifndef __SHA256_H__
#define __SHA256_H__

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define KEY_IOPAD_SIZE    64
#define SHA1_DIGEST_SIZE  20
#define MASTER_KEY_SIZE   32

typedef struct {
    uint8_t buf[64];   //512bit chunks
    uint32_t state[5];   //256bit hash value
    uint32_t buf_len;   //bytes in buf
    uint32_t bit_len[2];    //total length in bits
} sha1_ctx_t;

void sha1Init(sha1_ctx_t *ctx);
void sha1Update(sha1_ctx_t *ctx, uint8_t *message, uint32_t len);
void sha1_finish(sha1_ctx_t *ctx, uint8_t *hash);


#endif
