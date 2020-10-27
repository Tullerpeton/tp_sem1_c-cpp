#ifndef IZ_2_TASK_MANAGER_H
#define IZ_2_TASK_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/timeb.h>

#include "Errors/error_code.h"
#include "Config/configuration.h"
#include "Algorithm_calculate_sum/sequential_sum.h"
#include "Algorithm_calculate_sum/parallel_sum.h"

typedef struct task {
    char input[MAX_LEN_FILE_NAME];
    size_t size_array;
    int is_parallel;
} task;

error task_manager(const task* new_task);

#ifdef __cplusplus
}
#endif

#endif
