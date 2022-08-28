#include "CppUTest/TestHarness.h"
#undef _L

TEST_GROUP(TEST_ONE){};

TEST(TEST_ONE, TEST_ONE) {
    LONGS_EQUAL(1, 1)
}
