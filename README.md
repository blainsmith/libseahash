# [WIP] libseahash

libseahash is a C library that implements SeaHash, a non-cryptographic hash function created by [http://ticki.github.io](http://ticki.github.io). This is a port of the Go library [here](https://github.com/blainsmith/seahash).

## Use

I used the same conventions as the other C hashing libraries such as SHA1 and MD5 so the functions should be familiar.

## Example

```c
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
```

Source is available in `example.c`.