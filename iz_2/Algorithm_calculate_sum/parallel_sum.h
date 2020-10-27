#ifndef IZ_2_PARALLEL_SUM_H
#define IZ_2_PARALLEL_SUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "Errors/error_code.h"
#include "Config/configuration.h"
#include "File/bin_file_routines.h"
#include "my_math.h"

typedef struct thread_args {
    FILE *stream;
    int64_t sum;
    size_t step;
    size_t size;
    size_t index;
    int buff_num;
} thread_args;

error calculate_parallel_sum_array(int64_t *res_sum, size_t size, char stream_name[MAX_LEN_FILE_NAME]);

error init_threads(thread_args *args, size_t threads_count, size_t size, char stream_name[MAX_LEN_FILE_NAME]);
error run_threads(pthread_t *threads, thread_args *args, size_t threads_count);
error wait_threads(const pthread_t *threads, size_t threads_count);
error get_result_sum_threads(int64_t *res_sum, thread_args *args, size_t threads_count);

int get_number_CPU();

void *calculate_partial_sum(void *void_args);

#ifdef __cplusplus
}
#endif

#endif
