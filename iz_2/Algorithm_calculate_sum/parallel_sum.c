#include "parallel_sum.h"

error calculate_parallel_sum_array(int64_t* res_sum, size_t size, char stream_name[MAX_LEN_FILE_NAME]) {
    if (!res_sum || !stream_name)
        return INCORRECT_DATA;

    if (!size) {
        *res_sum = 0;
        return SUCCESS;
    }

    error err = SUCCESS;

    // [K + 10 * I] sums
    size_t threads_count = K;

    // Init arguments for threads
    thread_args args[threads_count];
    err = init_threads(args, threads_count, size, stream_name);
    if (err)
        return err;

    // Run and wait threads
    pthread_t threads[threads_count];
    int num_CPU = get_number_CPU();
    size_t active_threads, i = 0;
    while ((i < threads_count) && (!err)) {
        active_threads = (threads_count - i >=  num_CPU) ? num_CPU : threads_count - i;
        err = run_threads(threads + i, args + i, active_threads);
        if (!err) {
            err = wait_threads(threads + i, active_threads);
            i += active_threads;
        }
    }
    if (err)
        return err;

    // Calculate result sum
    err = get_result_sum_threads(res_sum, args, threads_count);

    return err;
}


error init_threads(thread_args* args, size_t threads_count,
                   size_t size, char stream_name[MAX_LEN_FILE_NAME]) {
    if (!args || !stream_name || (threads_count < 1) || (size < 1))
        return INCORRECT_DATA;

    for (size_t i = 0; i < threads_count; i++) {
        FILE *stream = fopen(stream_name, "rd");
        if (!stream)
            return INCORRECT_DATA;

        args[i].stream = stream;
        args[i].sum = 0;
        args[i].step = threads_count;
        args[i].size = size;
        args[i].index = i;
        args[i].buff_num = 0;
    }

    return SUCCESS;
}

error run_threads(pthread_t* threads, thread_args* args, size_t threads_count) {
    if (!threads || !args || (threads_count < 1))
        return INCORRECT_DATA;

    int err_flag = 0;
    for (size_t i = 0; (i < threads_count) && (!err_flag); i++)
        err_flag = pthread_create(threads + i, NULL, calculate_partial_sum, args + i);

    if (err_flag)
        return RUN_THREADS_ERROR;

    return SUCCESS;
}

error wait_threads(const pthread_t* threads, size_t threads_count) {
    if (!threads || (threads_count < 1))
        return INCORRECT_DATA;

    int err_flag = 0;
    for (size_t i = 0; (i < threads_count) && (!err_flag); i++)
        err_flag = pthread_join(threads[i], NULL);

    if (err_flag)
        return JOIN_THREADS_ERROR;

    return SUCCESS;
}

error get_result_sum_threads(int64_t* res_sum, thread_args* args, size_t threads_count) {
    if (!res_sum || !args || (threads_count < 1))
        return INCORRECT_DATA;

    for (size_t i = 0; i < threads_count; i++) {
        *res_sum += args[i].sum;
        fclose(args[i].stream);
    }

    return SUCCESS;
}


int get_number_CPU() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}


void* calculate_partial_sum(void *void_args) {
    error err = SUCCESS;

    if (!void_args) {
        err = INCORRECT_DATA;
        pthread_exit(&err);
    }

    thread_args *args = (thread_args*) void_args;

    args->sum = 0;
    while ((args->index < I) && (args->index < args->size) && (!err)) {
        err = get_int_by_position(&(args->buff_num), args->index, args->stream);

        if (!err)
            err = add_num(&(args->sum), args->buff_num);

        args->index += args->step;
    }

    pthread_exit(&err);
}
