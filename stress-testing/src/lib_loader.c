#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include "lib_loader.h"

int *(*create_array)(size_t count) = NULL;
void (*free_array)(int *arr) = NULL;
int (*set_values)(int *arr, size_t array_size, size_t seed, size_t step) = NULL;
int (*get_check_sum)(int *arr, size_t array_size, int *check_sum) = NULL;
void *library_handle = NULL;


int load_dynamic_symbols(const char *lib_path) {
    if (!lib_path) {
        return EXIT_FAILURE;
    }
    library_handle = dlopen(lib_path, RTLD_LAZY);
    if (!library_handle) {
        return EXIT_FAILURE;
    }

    dlerror();  // call dlerror to clear any old error conditions
    *(void **) (&create_array) = dlsym(library_handle, "create_array");
    *(void **) (&free_array) = dlsym(library_handle, "free_array");
    *(void **) (&set_values) = dlsym(library_handle, "set_values");
    *(void **) (&get_check_sum) = dlsym(library_handle, "get_check_sum");
    char *error_msg = dlerror();
    if (error_msg) {
        printf("Error while loading dynamic library_handle functions: %s\n", error_msg);
        return EXIT_FAILURE;
    }
    return 0;
}

int unload_dynamic_symbols() {
    if (dlclose(library_handle)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
