#ifndef _SEAHASH_H
#define _SEAHASH_H

#define SEAHASH_DIGEST_LENGTH 8

struct seahash_ctx {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    size_t input_len;
    size_t buffer_size;
    unsigned char buffer[SEAHASH_DIGEST_LENGTH];
} seahash_ctx;

void seahash_init(struct seahash_ctx *ctx);

void seahash_update(struct seahash_ctx *ctx, const unsigned char *buf, unsigned len);

void seahash_final(unsigned char digest[SEAHASH_DIGEST_LENGTH], struct seahash_ctx *ctx);

void seahash(char *hash, const char *str, int len);

#endif /* end _SEAHASH_H */
