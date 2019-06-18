#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "unity/unity.h"

#include "../src/seahash.h"

void test_seahash_verbose_one(void) {
    struct seahash_ctx context;
    seahash_init(&context);

    TEST_ASSERT_NOT_NULL(&context);
    TEST_ASSERT_EQUAL_UINT64((&context)->a, 0x16f11fe89b0d677c);
    TEST_ASSERT_EQUAL_UINT64((&context)->b, 0xb480a793d8e6c86c);
    TEST_ASSERT_EQUAL_UINT64((&context)->c, 0x6fe2e5aaf078ebc9);
    TEST_ASSERT_EQUAL_UINT64((&context)->d, 0x14f994a4c5259381);
    TEST_ASSERT_EQUAL_INT((&context)->input_len, 0);

    seahash_update(&context, (const unsigned char *)"update all the things", 21);

    TEST_ASSERT_EQUAL_UINT16((&context)->a, 0xf078ebc9);
    TEST_ASSERT_EQUAL_UINT16((&context)->b, 0xc5259381);
    TEST_ASSERT_EQUAL_UINT16((&context)->c, 0xed069414);
    TEST_ASSERT_EQUAL_UINT16((&context)->d, 0x6dd23f5a);
    TEST_ASSERT_EQUAL_INT((&context)->input_len, 21);

    unsigned char expected[SEAHASH_DIGEST_LENGTH+1] = {0x79, 0xb2, 0x6b, 0x5a, 0x61, 0x6e, 0x2d, 0x4a};
    unsigned char digest[SEAHASH_DIGEST_LENGTH+1];
    seahash_final(digest, &context);

    for (uint8_t i = 0; i < SEAHASH_DIGEST_LENGTH; i++) {
        TEST_ASSERT_EQUAL_INT(expected[i], digest[i]);
    }
}

void test_seahash_verbose_many(void) {
    struct seahash_ctx context;
    seahash_init(&context);

    TEST_ASSERT_NOT_NULL(&context);
    TEST_ASSERT_EQUAL_UINT64((&context)->a, 0x16f11fe89b0d677c);
    TEST_ASSERT_EQUAL_UINT64((&context)->b, 0xb480a793d8e6c86c);
    TEST_ASSERT_EQUAL_UINT64((&context)->c, 0x6fe2e5aaf078ebc9);
    TEST_ASSERT_EQUAL_UINT64((&context)->d, 0x14f994a4c5259381);
    TEST_ASSERT_EQUAL_INT((&context)->input_len, 0);

    seahash_update(&context, (const unsigned char *)"update", 6);

    TEST_ASSERT_EQUAL_UINT16((&context)->a, 0x9b0d677c);
    TEST_ASSERT_EQUAL_UINT16((&context)->b, 0xd8e6c86c);
    TEST_ASSERT_EQUAL_UINT16((&context)->c, 0xf078ebc9);
    TEST_ASSERT_EQUAL_UINT16((&context)->d, 0xc5259381);
    TEST_ASSERT_EQUAL_INT((&context)->input_len, 6);

    seahash_update(&context, (const unsigned char *)" all the things", 15);

    TEST_ASSERT_EQUAL_UINT16((&context)->a, 0xf078ebc9);
    TEST_ASSERT_EQUAL_UINT16((&context)->b, 0xc5259381);
    TEST_ASSERT_EQUAL_UINT16((&context)->c, 0xed069414);
    TEST_ASSERT_EQUAL_UINT16((&context)->d, 0x6dd23f5a);
    TEST_ASSERT_EQUAL_INT((&context)->input_len, 21);

    unsigned char expected[SEAHASH_DIGEST_LENGTH+1] = {0x79, 0xb2, 0x6b, 0x5a, 0x61, 0x6e, 0x2d, 0x4a};
    unsigned char digest[SEAHASH_DIGEST_LENGTH+1];
    seahash_final(digest, &context);

    for (uint8_t i = 0; i < SEAHASH_DIGEST_LENGTH; i++) {
        TEST_ASSERT_EQUAL_INT(expected[i], digest[i]);
    }
}

void test_seahash_terse(void) {
    unsigned char expected[SEAHASH_DIGEST_LENGTH+1] = {0x79, 0xb2, 0x6b, 0x5a, 0x61, 0x6e, 0x2d, 0x4a};
    unsigned char digest[SEAHASH_DIGEST_LENGTH+1];
    seahash(digest, (const unsigned char *)"update all the things", 21);

    for (uint8_t i = 0; i < SEAHASH_DIGEST_LENGTH; i++) {
        TEST_ASSERT_EQUAL_INT(expected[i], digest[i]);
    }
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_seahash_verbose_one);
    RUN_TEST(test_seahash_verbose_many);
    RUN_TEST(test_seahash_terse);

    return UNITY_END();
}
