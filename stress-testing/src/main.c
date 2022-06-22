#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

#ifdef DYNAMIC
# include "lib_loader.h"
#else
# include "check_sum.h"
#endif

const size_t SET_VAL_STEP = 10;
const size_t REPETITION_CNT = 20;

int main(int argc, const char **argv) {
    int exit_code = EXIT_FAILURE;
    size_t seed = 0, array_size = 0;
    const char *library_path = NULL;

    if (read_params(argc, argv, &seed, &array_size, &library_path)) {
        return exit_code;
    }
#ifdef DYNAMIC
    if (load_dynamic_symbols(library_path)) {
        return exit_code;
    }
#endif

    do {
        int *array = create_array(array_size * sizeof(int));
        if (!array) { break; }
        if (set_values(array, array_size, seed, SET_VAL_STEP)) {
            free_array(array);
            break;
        }

        int check_sum = 0;
        _Bool error_in_cycle = false;
        double elapsed = 0, cycle_elapsed = 0;

        for (size_t i = 0; i < REPETITION_CNT; ++i) {
            if (test_work(array, array_size, &check_sum, &cycle_elapsed)) {
                error_in_cycle = true;
                break;
            }
            elapsed += cycle_elapsed;
        }
        elapsed = elapsed / REPETITION_CNT;

        free_array(array);
        if (error_in_cycle) {
            break;
        }

        printf("%f\n%d\n", elapsed, check_sum);
        exit_code = EXIT_SUCCESS;
    } while (0);

#ifdef DYNAMIC
    if (unload_dynamic_symbols()) {
        return EXIT_FAILURE;
    }
#endif
    return exit_code;
}
