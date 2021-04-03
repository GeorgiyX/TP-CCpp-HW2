#include <sys/sysinfo.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>
#include "check_sum_private.h"
#include "check_sum.h"

#define PIPE_PAIR_SIZE 2
const size_t WRITE_INDEX = 1;
const size_t READ_INDEX = 0;

int fork_task(int *arr, size_t array_size) {
    exit(0);
}

int write_all(int fd, const char *buf, size_t size) {
    if (!fd || !buf || !size || size >= PIPE_BUF) {
        return EXIT_FAILURE;
    }
    int ret = 0;
    while (size && ret > 0) {
        ret = write(fd, buf, size);
        size -= ret;
        buf += ret;
    }
    return ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS;
}

int read_all(int fd, char *buf, size_t size) {
    if (!fd || !buf || !size) {
        return EXIT_FAILURE;
    }
    int ret = 1;
    while (size && ret > 0) {
        ret = read(fd, buf, size);
        size -=ret;
        buf +=ret;
    }
    return ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS;
}

#define read_all(fd, buf, size) io_all(fd, buf, size, read)
#define write_all(fd, buf, size) io_all(fd, buf, size, (ssize_t (*)(int, void *, size_t)) write)

int io_all(int fd, char *buf, size_t size, ssize_t (*io_function) (int, void *, size_t)) {
    if (!fd || !buf || !size || size >= PIPE_BUF) {
        return EXIT_FAILURE;
    }
    int ret = 1;
    while (size && ret > 0) {
        ret = io_function(fd, buf, size);
        size -= ret;
        buf += ret;
    }
    return ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS;
}

int get_check_sum(int *arr, size_t array_size, int *check_sum) {
    if (!arr || !check_sum) { return EXIT_FAILURE; }

    size_t proc_count = get_nprocs();
    size_t range_to_sum = array_size / proc_count;
    if (range_to_sum == 0) {
        /* Too few elements in the array for parallel work */
        return get_check_sum_private(arr, array_size, check_sum);
    }

    size_t num_of_forks = 0;
    int pipe_fd[PIPE_PAIR_SIZE];
    pid_t pid = 0;
    int exit_status = 0;

    if (pipe(pipe_fd) == -1) {
        return EXIT_FAILURE;
    }

    while (num_of_forks < (proc_count - 1)) {
        pid = fork();
        if (pid == -1) {
            break;
        } else if (pid == 0) {
            close(pipe_fd[READ_INDEX]);
            int check_sum_fork = 0;
            int return_code = get_check_sum_private(arr + num_of_forks * range_to_sum, range_to_sum, &check_sum_fork);
            if (write_all(pipe_fd[WRITE_INDEX], (char *) &check_sum_fork, sizeof(check_sum_fork)) == -1) {
                close(pipe_fd[WRITE_INDEX]);
                exit(EXIT_FAILURE);
            }
            close(pipe_fd[WRITE_INDEX]);
            exit(return_code);
        }
        ++num_of_forks;
    }

    if (pid == -1) {
        while (num_of_forks) {
            wait(NULL);
            --num_of_forks;
        }
        return EXIT_FAILURE;
    }


    if (get_check_sum_private(arr + num_of_forks * range_to_sum,
                              (array_size - proc_count * range_to_sum), check_sum) == EXIT_FAILURE) {
        /* same as below */
    }

    int another_ret_code = 0;
    int check_sum_from_process = 0;
    while ((another_ret_code = read(pipe_fd[READ_INDEX], &check_sum_from_process, sizeof check_sum_from_process)) > 0) {

    }


    int wait_status = 0;
    while (num_of_forks) {
        wait(&wait_status);
        if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
        }
        --num_of_forks;
    }


    return get_check_sum_private(arr, array_size, check_sum);
}
