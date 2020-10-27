#include "my_math.h"

error add_num(int64_t* sum, int num) {
    if (INT64_MAX - num < *sum)
        return OVERFLOW_ERROR;
    else
        *sum += num;

    return SUCCESS;
}

