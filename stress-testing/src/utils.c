#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include "utils.h"

#ifdef DYNAMIC
# include "lib_loader.h"
# define ARG_CNT 4
const char *few_arg_msg = "Please specify test seed, array size and path"
                          " to .so library like: %s <seed> <array size> <path/to/lib.so>";
#else
# include "check_sum.h"
# define ARG_CNT 3
const char *few_arg_msg = "Please specify test seed and array size like: %s <seed> <array size>";
#endif

const double MICRO = 1e-6;

int read_params(int argc, const char **argv, size_t *seed, size_t *arr_size, const char **lib_path) {
    if (!argv || !seed || !arr_size || !lib_path) { return EXIT_FAILURE; }

    if (argc < ARG_CNT) {
        printf(few_arg_msg, argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    *seed = strtoul(argv[1], NULL, 10);
    *arr_size = strtoul(argv[2], NULL, 10);
    if (errno) {
        printf("wrong params..");
        return EXIT_FAILURE;
    }

#ifdef DYNAMIC
    *lib_path = argv[3];
#else
    *lib_path = NULL;
#endif
    return EXIT_SUCCESS;
}

int get_elapsed_time(const struct timeval *start, const struct timeval *end, double *result) {
    if (!start || !end || !result) {
        return EXIT_FAILURE;
    }

    __time_t sec  = end->tv_sec - start->tv_sec;
    __suseconds_t usec = end->tv_usec - start->tv_usec;
    *result = sec + usec * MICRO;

    return EXIT_SUCCESS;
}

int test_work(int *array, size_t array_size, int *check_sum, double *elapsed) {
    if (!array || !check_sum || !elapsed) {
        return EXIT_FAILURE;
    }

#ifdef DYNAMIC
    if (!get_check_sum) {
        return EXIT_FAILURE;
    }
#endif

    struct timeval start, end;

    if (gettimeofday(&start, 0)) {
        return EXIT_FAILURE;
    }
    if (get_check_sum(array, array_size, check_sum)) {
        return EXIT_FAILURE;
    }
    if (gettimeofday(&end, 0)) {
        return EXIT_FAILURE;
    }
    if (get_elapsed_time(&start, &end, elapsed)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
