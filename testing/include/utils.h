#ifndef TP_HW1_UTILS_H
#define TP_HW1_UTILS_H

#include <gtest/gtest.h>
#include <dlfcn.h>

struct TestConfig {
    static size_t testSeed;
    static size_t arraySize;
    static std::string sharedLibraryPath;
    static const size_t RANGE_1;
    static const size_t RANGE_2;
    static const size_t RANGE_3;
    static const size_t RANGE_4;
    static const size_t SMALL_ARRAY_SIZE;
    static const int FD;
};

namespace test_realisations {
    void setVectorValuesInRange(std::vector<int> &data, size_t seed, size_t step);
    int getCheckSum(std::vector<int> &data);
    ssize_t io_variant1(int fd, void *buf, size_t size);
    ssize_t io_variant2(int fd, void *buf, size_t size);
}

long getL1LineSize();

class PARALLEL_TESTS : public testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    static int *(*create_array)(size_t count);
    static void (*free_array)(int *arr);
    static int (*set_values)(int *arr, size_t array_size, size_t seed, size_t step);
    static int (*get_check_sum)(int *arr, size_t array_size, int *check_sum);
    static int (*get_check_sum_private)(const int *arr, size_t array_size, int *check_sum);
    static void (*fork_work)(int *arr, size_t array_size, int pipe_fd[2]);
    static int (*io_all)(int fd, char *buf, size_t size, ssize_t (*io_function)(int, void *, size_t));

private:
    template <class T>
    static void loadSymbol(T &fooPtr, const char *fooName) {
        *(void **) (&fooPtr) = dlsym(library_handle, fooName);
        auto error = dlerror();
        if (error) {
            throw std::runtime_error(error);
        }
    }
    static void *library_handle;
};

#endif //TP_HW1_UTILS_H
