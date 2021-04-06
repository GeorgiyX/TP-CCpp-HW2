#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifdef DYNAMIC
# include "lib_loader.h"
#else
# include "check_sum.h"
#endif

int main(int argc, const char **argv) {
    size_t seed = 0, array_size = 0;
    const char *library_path = NULL;
    if (read_params(argc, argv, &seed, &array_size, &library_path)) {
        return EXIT_FAILURE;
    }
#ifdef DYNAMIC
    if (load_dynamic_symbols(library_path)) {
        return EXIT_FAILURE;
    }
#endif



#ifdef DYNAMIC
    if (unload_dynamic_symbols()) {
        return EXIT_FAILURE;
    }
#endif
    return EXIT_SUCCESS;
}
