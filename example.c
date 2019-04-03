#include <stdio.h>

#include "src/seahash.h"

int main(int argc, char **argv) {
    unsigned char digest[SEAHASH_DIGEST_LENGTH];
    const char* string = "Hello World";
    
    struct seahash_ctx context;
    seahash_init(&context);
    seahash_update(&context, string, strlen(string));
    seahash_final(digest, &context);
}
