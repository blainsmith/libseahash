#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "seahash.h"

uint64_t read_block(const unsigned char *input, unsigned len)
{
    uint64_t block = 0;

    if (len == SEAHASH_DIGEST_LENGTH)
    {
        block = (uint64_t)input[0] |
                (uint64_t)input[1] << 8 |
                (uint64_t)input[2] << 16 |
                (uint64_t)input[3] << 24 |
                (uint64_t)input[4] << 32 |
                (uint64_t)input[5] << 40 |
                (uint64_t)input[6] << 48 |
                (uint64_t)input[7] << 56;

        return block;
    }

    while (len > 0)
    {
        len--;
        block <<= 8;
        block |= (uint64_t)input[len];
    }

    return block;
}

uint64_t diffuse(uint64_t in)
{
    in *= 0x6eed0e9da4d94a4f;
    uint64_t a = in >> 32;
    uint64_t b = in >> 60;
    in ^= a >> b;
    in *= 0x6eed0e9da4d94a4f;

    return in;
}

void update_state(struct seahash_ctx *ctx, uint64_t in)
{
    uint64_t a = ctx->a;
    a = diffuse(a ^ in);

    ctx->a = ctx->b;
    ctx->b = ctx->c;
    ctx->c = ctx->d;
    ctx->d = a;
}

void seahash_init(struct seahash_ctx *ctx)
{
    return;
}

void seahash_update(struct seahash_ctx *ctx, const unsigned char *input, unsigned len)
{
    return;
}

void seahash_final(unsigned char digest[SEAHASH_DIGEST_LENGTH], struct seahash_ctx *ctx)
{
    return;
}

void seahash(char *hash, const char *str, int len)
{
    return;
}