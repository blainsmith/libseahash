# [WIP] libseahash

libseahash is a C library that implements SeaHash, a non-cryptographic hash function created by [http://ticki.github.io](http://ticki.github.io). This is a port of the Go library [here](https://github.com/blainsmith/seahash).

## Use

I used the same conventions as the other C hashing libraries such as SHA1 and MD5 so the functions should be familiar.

## Example

```c
#include <stdio.h>

#include "src/seahash.h"

int main(int argc, char **argv) {
    // This is the verbose method of
    // computing a hash by initializing
    // a context first and then updating
    // and finalizing it for the results.
    unsigned char digest[SEAHASH_DIGEST_LENGTH+1];
    const char *string = "to be or not to be";

    struct seahash_ctx context;
    seahash_init(&context);
    seahash_update(&context, (const unsigned char *)string, strlen(string));
    seahash_final(digest, &context);

    for (uint8_t i = 0; i < SEAHASH_DIGEST_LENGTH; i++) {
        printf("0x%02x ", digest[i]);
    }
    // Prints "0x1b 0x99 0x3a 0x82 0x6f 0x4a 0xe5 0x75"

    // This is a convenience function
    // for perorming the same hashing
    // above, but with a lot less steps.
    unsigned char hash[SEAHASH_DIGEST_LENGTH+1];
    const char *str = "to be or not to be";
    seahash(hash, (const unsigned char *)str, strlen(str));

    for (uint8_t i = 0; i < SEAHASH_DIGEST_LENGTH; i++) {
        printf("0x%02x ", hash[i]);
    }
    // Prints "0x1b 0x99 0x3a 0x82 0x6f 0x4a 0xe5 0x75"
}
```

Source is available in `example.c`.