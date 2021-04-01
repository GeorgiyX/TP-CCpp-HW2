#ifndef TP_HW1_UTILS_H
#define TP_HW1_UTILS_H

#include <gtest/gtest.h>

struct TestConfig {
    static size_t testSeed;
    static size_t arraySize;
};

namespace test_realisations {
    void setVectorValuesInRange(std::vector<int> &data, size_t step, size_t seed);
    int getCheckSum(std::vector<int> &data);
}

#endif //TP_HW1_UTILS_H
