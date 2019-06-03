#include <string.h>
#include "llist.h"
#include "unity.h"

/**
 * Test malloc_s a void * and free_s it.
 *
 * Tests Items:
 *   1) malloc_s one void * ptr to out, should return CC_OK;
 *   2) the ptr should be push into gc->buff[];
 *   3) count of alloc_ed should be 1;
 *   4) free_s out, should return CC_OK;
 *   5) alloc_ed should be 0;
 *   6) gc->buff[0] shoule be all-AA
 */
void test_malloc_s( void ) {
    void *out;
    TEST_ASSERT_EQUAL( CC_OK, malloc_s(sizeof(void *), &out));
    TEST_ASSERT_EQUAL_UINT64(1, gc->count);
    TEST_ASSERT_EQUAL_PTR(out, gc->buff[0]);
    TEST_ASSERT_EQUAL( CC_OK, free_s(out));
    TEST_ASSERT_EQUAL_UINT64(0, gc->count);
    TEST_ASSERT_EQUAL_HEX64(0xAAAAAAAAAAAAAAAA, gc->buff[0]);
}

void test_malloc_s_multi( void ) {
    char *out[100];
    char *str = "Hello World";
    for ( size_t i = 0; i < 100; i++)
        TEST_ASSERT_EQUAL( CC_OK, malloc_s(sizeof(char *), &out[i]));
    TEST_ASSERT_EQUAL_HEX64(100, gc->count);
    TEST_ASSERT_EQUAL_PTR(out[99], gc->buff[99]);
    TEST_ASSERT_EQUAL( CC_OK, free_s(out[99]));
    TEST_ASSERT_EQUAL_UINT64(99, gc->count);
    TEST_ASSERT_EQUAL_HEX64(0xAAAAAAAAAAAAAAAA, gc->buff[99]);
    strcpy(out[10], str);
    TEST_ASSERT_EQUAL_STRING("Hello World", gc->buff[10]);
    free_all();
}

int main( void )
{
    UNITY_BEGIN();
    RUN_TEST(test_malloc_s);
    RUN_TEST(test_malloc_s_multi);
    return UNITY_END();
}
