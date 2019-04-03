#ifndef _SEAHASH_H
#define _SEAHASH_H

#define SEAHASH_DIGEST_LENGTH 8

struct seahash_ctx {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    int8_t input_size;
    int8_t buffer_size;
    unsigned char in[SEAHASH_DIGEST_LENGTH];
} seahash_ctx;

void seahash_init(struct seahash_ctx *ctx);

void seahash_update(struct seahash_ctx *ctx, unsigned char const *buf, unsigned len);

void seahash_final(unsigned char digest[SEAHASH_DIGEST_LENGTH], struct seahash_ctx *ctx);

void seahash(char *hash, const char *str, int len);

#endif /* end _SEAHASH_H */
