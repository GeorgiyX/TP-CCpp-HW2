#include <gtest/gtest.h>
#include "utils.h"
extern "C" {
#include "check_sum.h"
}

TEST(COMMON, CREATE_ARRAY) {
    errno = 0;
    auto *arr = create_array(TestConfig::arraySize);
    free(arr);
    ASSERT_TRUE(!arr == (errno == ENOMEM));
}

TEST(COMMON, FREE_ARRAY) {
    auto *arr = create_array(TestConfig::arraySize);
    if (!arr) {
        throw std::runtime_error("no memory");
    }
    free_array(arr);
    SUCCEED();
}

