#include <limits>
#include "utils.h"

size_t TestConfig::testSeed;
size_t TestConfig::arraySize;
const int CHECK_SUM_MODULE = 1024;

void test_realisations::setVectorValuesInRange(std::vector<int> &data, size_t step, size_t seed) {
    srandom(seed);
    size_t remaining_elements = 0;

    for (size_t i = 0; i < data.size(); i += step) {
        remaining_elements = data.size() - i;
        memset(data.data() + i, random() % std::numeric_limits<int>::max(), remaining_elements > step ? step : remaining_elements);
    }
}

int test_realisations::getCheckSum(std::vector<int> &data) {
    int checkSum = 0;
    std::for_each(data.begin(), data.end(), [&checkSum](auto el){
        checkSum = (checkSum + el) % CHECK_SUM_MODULE;
    });
    return checkSum;
}

long getL1LineSize() {
    long l1d_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (l1d_size == -1) {
        l1d_size = sizeof (void*);
    }
    return  l1d_size;
}
