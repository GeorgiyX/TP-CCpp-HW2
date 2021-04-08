#include <gtest/gtest.h>
#include <cstring>
#include "utils.h"

TEST_F(PARALLEL_TESTS, CREATE_ARRAY) {
    auto *arr = create_array(TestConfig::arraySize);
    if (!arr) {
        throw std::runtime_error("no memory");
    }
    free_array(arr);
    auto memPtr = reinterpret_cast<uintptr_t>(arr);
    ASSERT_EQ(memPtr % getL1LineSize(), 0);
}

TEST_F(PARALLEL_TESTS, FREE_ARRAY) {
    auto *arr = create_array(TestConfig::arraySize);
    if (!arr) {
        throw std::runtime_error("no memory");
    }
    free_array(arr);
    SUCCEED();
}

TEST_F(PARALLEL_TESTS, SET_VALUES) {
    std::vector<int> arr_test(TestConfig::arraySize, 0);
    std::vector<int> arr_lib(TestConfig::arraySize, 0);

    ASSERT_EQ(set_values(nullptr, arr_lib.size(), TestConfig::RANGE_1, TestConfig::testSeed), EXIT_FAILURE);
    ASSERT_EQ(set_values(arr_lib.data(), 0, TestConfig::RANGE_1, TestConfig::testSeed), EXIT_SUCCESS);
    ASSERT_EQ(set_values(arr_lib.data(), arr_lib.size(), TestConfig::RANGE_1, TestConfig::testSeed), EXIT_SUCCESS);

    test_realisations::setVectorValuesInRange(arr_test, TestConfig::RANGE_2, TestConfig::testSeed);
    ASSERT_EQ(set_values(arr_lib.data(), arr_lib.size(), TestConfig::RANGE_2, TestConfig::testSeed), EXIT_SUCCESS);
    ASSERT_EQ(std::memcmp(arr_test.data(), arr_lib.data(), TestConfig::arraySize), 0);

    test_realisations::setVectorValuesInRange(arr_test, TestConfig::RANGE_3, TestConfig::testSeed);
    ASSERT_EQ(set_values(arr_lib.data(), arr_lib.size(), TestConfig::RANGE_3, TestConfig::testSeed), EXIT_SUCCESS);
    ASSERT_EQ(std::memcmp(arr_test.data(), arr_lib.data(), TestConfig::arraySize), 0);
}

TEST_F(PARALLEL_TESTS, GET_CHECK_SUM_PRIVATE) {
    std::vector<int> arr(TestConfig::arraySize, 0);
    ASSERT_EQ(set_values(arr.data(), arr.size(), TestConfig::RANGE_4, TestConfig::testSeed), EXIT_SUCCESS);

    int checkSumLib = 0;
    int checkSumTest = test_realisations::getCheckSum(arr);
    ASSERT_EQ(get_check_sum_private(arr.data(), arr.size(), nullptr), EXIT_FAILURE);
    ASSERT_EQ(get_check_sum_private(arr.data(), arr.size(), &checkSumLib), EXIT_SUCCESS);
    ASSERT_EQ(checkSumLib, checkSumTest);
}

TEST_F(PARALLEL_TESTS, GET_CHECK_SUM_1) {
    std::vector<int> arr(TestConfig::arraySize, 0);
    ASSERT_EQ(set_values(arr.data(), arr.size(), TestConfig::testSeed, TestConfig::RANGE_4), EXIT_SUCCESS);

    int checkSumLib = 0;
    int checkSumTest = test_realisations::getCheckSum(arr);
    ASSERT_EQ(get_check_sum(arr.data(), arr.size(), nullptr), EXIT_FAILURE);
    ASSERT_EQ(get_check_sum(arr.data(), arr.size(), &checkSumLib), EXIT_SUCCESS);
    ASSERT_EQ(checkSumLib, checkSumTest);
}

TEST_F(PARALLEL_TESTS, GET_CHECK_SUM_2) {
    std::vector<int> arr(TestConfig::SMALL_ARRAY_SIZE, 0);
    ASSERT_EQ(set_values(arr.data(), arr.size(), TestConfig::testSeed, TestConfig::RANGE_4), EXIT_SUCCESS);

    int checkSumLib = 0;
    int checkSumTest = test_realisations::getCheckSum(arr);
    ASSERT_EQ(get_check_sum(arr.data(), arr.size(), nullptr), EXIT_FAILURE);
    ASSERT_EQ(get_check_sum(arr.data(), arr.size(), &checkSumLib), EXIT_SUCCESS);
    ASSERT_EQ(checkSumLib, checkSumTest);
}

TEST_F(PARALLEL_TESTS, IO_ALL) {
    std::vector<char> buf(10, 0);
    ASSERT_EQ(io_all(TestConfig::FD, buf.data(), buf.size(), test_realisations::io_variant1), EXIT_FAILURE);
    ASSERT_EQ(io_all(TestConfig::FD, buf.data(), buf.size(), test_realisations::io_variant2), EXIT_SUCCESS);
}
