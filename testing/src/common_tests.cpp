#include <gtest/gtest.h>
#include <cstring>
#include "utils.h"
extern "C" {
#include "check_sum.h"
#include "check_sum_private.h"
}

const size_t RANGE_1 = 0;
const size_t RANGE_2 = 1;
const size_t RANGE_3 = 10;
const size_t RANGE_4 = 3;

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

TEST(COMMON, SET_VALUES) {
    std::vector<int> arr_test(TestConfig::arraySize, 0);
    std::vector<int> arr_lib(TestConfig::arraySize, 0);

    ASSERT_EQ(set_values(nullptr, arr_lib.size(), RANGE_1, TestConfig::testSeed), ERROR_CODE);
    ASSERT_EQ(set_values(arr_lib.data(), 0, RANGE_1, TestConfig::testSeed), SUCCESS_CODE);
    ASSERT_EQ(set_values(arr_lib.data(), arr_lib.size(), RANGE_1, TestConfig::testSeed), SUCCESS_CODE);

    test_realisations::setVectorValuesInRange(arr_test, RANGE_2, TestConfig::testSeed);
    ASSERT_EQ(set_values(arr_lib.data(), arr_lib.size(), RANGE_2, TestConfig::testSeed), SUCCESS_CODE);
    ASSERT_EQ(std::memcmp(arr_test.data(), arr_lib.data(), TestConfig::arraySize), 0);

    test_realisations::setVectorValuesInRange(arr_test, RANGE_3, TestConfig::testSeed);
    ASSERT_EQ(set_values(arr_lib.data(), arr_lib.size(), RANGE_3, TestConfig::testSeed), SUCCESS_CODE);
    ASSERT_EQ(std::memcmp(arr_test.data(), arr_lib.data(), TestConfig::arraySize), 0);
}

TEST(COMMON, GET_CHECK_SUM_PRIVATE) {
    std::vector<int> arr(TestConfig::arraySize, 0);
    ASSERT_EQ(set_values(arr.data(), arr.size(), RANGE_4, TestConfig::testSeed), SUCCESS_CODE);

    int checkSumLib = 0;
    int checkSumTest = test_realisations::getCheckSum(arr);;
    ASSERT_EQ(get_check_sum_private(arr.data(), arr.size(), nullptr), ERROR_CODE);
    ASSERT_EQ(get_check_sum_private(arr.data(), arr.size(), &checkSumLib), SUCCESS_CODE);
    ASSERT_EQ(checkSumLib, checkSumTest);
}

