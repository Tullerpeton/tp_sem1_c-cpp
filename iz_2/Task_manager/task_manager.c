#include "task_manager.h"

error task_manager(const task* new_task) {
    if (!new_task)
        return INCORRECT_DATA;

    error err = SUCCESS;

    // Calculate sum
    int64_t sum = 0;

    struct timeb start, end;
    int64_t time = 0;

    if (new_task->is_parallel) {
        ftime(&start);
        err = calculate_parallel_sum_array(&sum, new_task->size_array, new_task->input);
        ftime(&end);
    }
    else {
        ftime(&start);
        err = calculate_sequential_sum_array(&sum, new_task->size_array, new_task->input);
        ftime(&end);
    }
    time += (end.time - start.time + 0.) + (end.millitm - start.millitm + 0.) / 1000;

    // Print result sum
    printf("sum = %" PRIu64 "\n", sum);
    printf("time = %" PRIu64 "\n", time);

    return err;
}
