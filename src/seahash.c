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
    ctx->a = 0x16f11fe89b0d677c;
    ctx->b = 0xb480a793d8e6c86c;
    ctx->c = 0x6fe2e5aaf078ebc9;
    ctx->d = 0x14f994a4c5259381;
    ctx->input_len = 0;
    ctx->buffer_size = 0;

    return;
}

void seahash_update(struct seahash_ctx *ctx, const unsigned char *input, unsigned len)
{
    ctx->input_len += len;

    if (ctx->buffer_size > 0)
    {
        // To be implemented
    }

    while (len >= SEAHASH_DIGEST_LENGTH)
    {
        uint64_t block = read_block(input, SEAHASH_DIGEST_LENGTH);
        update_state(ctx, block);

        input = input + SEAHASH_DIGEST_LENGTH;
        len -= SEAHASH_DIGEST_LENGTH;
    }

    if (len > 0)
    {
        ctx->buffer_size = len;
        memcpy(&ctx->buffer, input, len);
    }

    return;
}

void seahash_final(unsigned char digest[SEAHASH_DIGEST_LENGTH], struct seahash_ctx *ctx)
{
    uint64_t final = 0;

    if (ctx->buffer_size > 0)
    {
        struct seahash_ctx ctxcpy;
        (&ctxcpy)->a = ctx->a;
        (&ctxcpy)->b = ctx->b;
        (&ctxcpy)->c = ctx->c;
        (&ctxcpy)->d = ctx->d;

        uint64_t block = read_block(ctx->buffer, ctx->buffer_size);
        update_state(&ctxcpy, block);

        final = diffuse((&ctxcpy)->a ^ (&ctxcpy)->b ^ (&ctxcpy)->c ^ (&ctxcpy)->d ^ (uint64_t)ctx->input_len);

        digest[7] = (unsigned char)(final);
        digest[6] = (unsigned char)(final >> 8);
        digest[5] = (unsigned char)(final >> 16);
        digest[4] = (unsigned char)(final >> 24);
        digest[3] = (unsigned char)(final >> 32);
        digest[2] = (unsigned char)(final >> 40);
        digest[1] = (unsigned char)(final >> 48);
        digest[0] = (unsigned char)(final >> 56);

        return;
    }

    final = diffuse(ctx->a ^ ctx->b ^ ctx->c ^ ctx->d ^ (uint64_t)ctx->input_len);

    digest[7] = (unsigned char)(final);
    digest[6] = (unsigned char)(final >> 8);
    digest[5] = (unsigned char)(final >> 16);
    digest[4] = (unsigned char)(final >> 24);
    digest[3] = (unsigned char)(final >> 32);
    digest[2] = (unsigned char)(final >> 40);
    digest[1] = (unsigned char)(final >> 48);
    digest[0] = (unsigned char)(final >> 56);

    return;
}

void seahash(char *hash, const char *str, int len)
{
    struct seahash_ctx context;

    seahash_init(&context);
    for (int i = 0; i < len; i++)
    {
        seahash_update(&context, (const unsigned char *)str, 1);
    }
    seahash_final((unsigned char *)hash, &context);
    hash[19] = '\n';

    return;
}