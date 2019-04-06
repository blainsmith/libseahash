#include <stdio.h>
#include <string.h>

#include "unity/unity.h"

#include "../src/seahash.h"

int main(int argc, char **argv) {
    UNITY_BEGIN();

    unsigned char digest[SEAHASH_DIGEST_LENGTH];
    const char *string = "to be or not to be";

    struct seahash_ctx context;
    seahash_init(&context);
    seahash_update(&context, (const unsigned char *)string, strlen(string));
    seahash_final(digest, &context);

    for (uint8_t i = 0; i < SEAHASH_DIGEST_LENGTH; i++) {
        printf("%x", digest[i]);
    }

    char result[20];
    const char *str = "to be or not to be";
    seahash(result, str, strlen(str));

    for (uint8_t i = 0; i < SEAHASH_DIGEST_LENGTH; i++) {
        printf("%x", result[i]);
    }

    return UNITY_END();
}
