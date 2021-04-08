#include <sys/sysinfo.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>
#include "check_sum_private.h"
#include "check_sum.h"

#define read_all(fd, buf, size) io_all(fd, buf, size, read)
#define write_all(fd, buf, size) io_all(fd, buf, size, (ssize_t (*)(int, void *, size_t)) write)
#define unlikely(expr) __builtin_expect(!!(expr), 0)

#define PIPE_PAIR_SIZE 2
extern const int CHECK_SUM_MODULE;
const size_t WRITE_INDEX = 1;
const size_t READ_INDEX = 0;


int io_all(int fd, char *buf, size_t size, ssize_t (*io_function)(int, void *, size_t)) {
    if (!fd || !buf || !size || size >= PIPE_BUF) {
        return EXIT_FAILURE;
    }
    long ret = 1;
    while (size && ret > 0) {
        ret = io_function(fd, buf, size);
        size -= ret;
        buf += ret;
    }
    return ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS;
}

void fork_work(int *arr, size_t array_size, int pipe_fd[2]) {
    close(pipe_fd[READ_INDEX]);
    int check_sum = 0;
    int exit_code = EXIT_FAILURE;

    do {
        if (unlikely(get_check_sum_private(arr, array_size, &check_sum))) { break; }
        if (unlikely(write_all(pipe_fd[WRITE_INDEX], (char *) &check_sum, sizeof(check_sum)))) { break; }
        exit_code = EXIT_SUCCESS;
    } while (0);

    close(pipe_fd[WRITE_INDEX]);
    exit(exit_code);
}

int get_check_sum(int *arr, size_t array_size, int *check_sum) {
    if (unlikely(!arr || !check_sum)) { return EXIT_FAILURE; }

    size_t proc_count = get_nprocs();
    size_t range_to_sum = array_size / proc_count;
    if (range_to_sum == 0) {
        /* Too few elements in the array for parallel work */
        return get_check_sum_private(arr, array_size, check_sum);
    }

    size_t num_of_forks = 0;
    int pipe_fd[PIPE_PAIR_SIZE];
    int exit_code = EXIT_FAILURE;
    pid_t pid = 0;

    if (unlikely(pipe(pipe_fd) == -1)) {
        return EXIT_FAILURE;
    }

    while (num_of_forks < (proc_count - 1)) {
        pid = fork();
        if (unlikely(pid == -1)) {
            break;
        } else if (pid == 0) {
            fork_work(arr + num_of_forks * range_to_sum, range_to_sum, pipe_fd);
        } else {
            ++num_of_forks;
        }
    }

    do {
        if (unlikely(pid == -1)) { break; }

        if (unlikely(get_check_sum_private(arr + num_of_forks * range_to_sum,
                                           (array_size - num_of_forks * range_to_sum), check_sum))) { break; }

        int *check_sums = create_array(num_of_forks * sizeof(int));
        if (unlikely(!check_sums)) { break; }
        if (unlikely(read_all(pipe_fd[READ_INDEX], (char *) check_sums, num_of_forks * sizeof(int)))) {
            free(check_sums);
            break;
        }
        for (size_t i = 0; i < num_of_forks; ++i) {
            *check_sum = (*check_sum + check_sums[i]) % CHECK_SUM_MODULE;
        }
        free(check_sums);

        exit_code = EXIT_SUCCESS;
    } while (0);

    close(pipe_fd[READ_INDEX]);
    close(pipe_fd[WRITE_INDEX]);
    int wait_status = 0;
    while (num_of_forks) {
        if ((wait(&wait_status) == -1) || (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == EXIT_FAILURE)) {
            exit_code = EXIT_FAILURE;
        }
        --num_of_forks;
    }
    return exit_code;
}
