#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "seahash.h"

void seahash_init(struct seahash_ctx *ctx)
{
    return;
}

void seahash_update(struct seahash_ctx *ctx, unsigned char const *buf, unsigned len)
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
