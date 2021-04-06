#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "utils.h"

#ifdef DYNAMIC
# define ARG_CNT 3
# define lib_path
const char *few_arg_msg = "Please specify test seed and array size like: %s <seed> <array size>";
#else
# define ARG_CNT 4
const char *few_arg_msg = "Please specify test seed, array size and path"
                          " to .so library like: %s <seed> <array size> <path/to/lib.so>";
#endif


int read_params(int argc, const char **argv, size_t *seed, size_t *arr_size, const char **lib_path) {
    if (!argv || !seed || !arr_size || !lib_path) {
        return EXIT_FAILURE;
    }
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
#endif
    return EXIT_SUCCESS;
}
