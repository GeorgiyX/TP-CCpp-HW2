#include <limits>
#include "utils.h"

size_t TestConfig::testSeed;
size_t TestConfig::arraySize;
std::string TestConfig::sharedLibraryPath;
const size_t TestConfig::RANGE_1 = 0;
const size_t TestConfig::RANGE_2 = 1;
const size_t TestConfig::RANGE_3 = 10;
const size_t TestConfig::RANGE_4 = 3;
const size_t TestConfig::SMALL_ARRAY_SIZE = 2;
const int TestConfig::FD = 100;

int *(*PARALLEL_TESTS::create_array)(size_t count) = nullptr;
void (*PARALLEL_TESTS::free_array)(int *arr) = nullptr;
int (*PARALLEL_TESTS::set_values)(int *arr, size_t array_size, size_t seed, size_t step) = nullptr;
int (*PARALLEL_TESTS::get_check_sum)(int *arr, size_t array_size, int *check_sum) = nullptr;
int (*PARALLEL_TESTS::get_check_sum_private)(const int *arr, size_t array_size, int *check_sum) = nullptr;
void (*PARALLEL_TESTS::fork_work)(int *arr, size_t array_size, int pipe_fd[2]) = nullptr;
int (*PARALLEL_TESTS::io_all)(int fd, char *buf, size_t size, ssize_t (*io_function)(int, void *, size_t)) = nullptr;

void *PARALLEL_TESTS::library_handle = nullptr;
const int CHECK_SUM_MODULE = 1024;
const size_t IO_ALL_DECREMENT_STEP = 1;

void test_realisations::setVectorValuesInRange(std::vector<int> &data, size_t seed, size_t step) {
    size_t remainingElements = 0;
    srandom(seed);
    for (size_t i = 0; i < data.size(); i += step) {
        remainingElements = data.size() - i;
        memset(data.data() + i, random() % std::numeric_limits<int>::max(),
               remainingElements > step ? step : remainingElements);
    }
}

int test_realisations::getCheckSum(std::vector<int> &data) {
    int checkSum = 0;
    std::for_each(data.begin(), data.end(), [&checkSum](auto el) {
        checkSum = (checkSum + el) % CHECK_SUM_MODULE;
    });
    return checkSum;
}

ssize_t test_realisations::io_variant1(int, void *, size_t) {
    return -1;
}

ssize_t test_realisations::io_variant2(int, void *, size_t size) {
    return size > 0 ? IO_ALL_DECREMENT_STEP : 0;
}

long getL1LineSize() {
    long l1d_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (l1d_size == -1) {
        l1d_size = sizeof(void *);
    }
    return l1d_size;
}

void PARALLEL_TESTS::SetUpTestSuite() {
    library_handle = dlopen(TestConfig::sharedLibraryPath.c_str(), RTLD_LAZY);
    if (!library_handle) {
        throw std::runtime_error("Can't load shared library");
    }

    loadSymbol(create_array, "create_array");
    loadSymbol(free_array, "free_array");
    loadSymbol(set_values, "set_values");
    loadSymbol(get_check_sum, "get_check_sum");
    loadSymbol(get_check_sum_private, "get_check_sum_private");
    loadSymbol(fork_work, "fork_work");
    loadSymbol(io_all, "io_all");
}

void PARALLEL_TESTS::TearDownTestSuite() {
    if (dlclose(library_handle)) {
        throw std::runtime_error("Can't close library");
    }
}
