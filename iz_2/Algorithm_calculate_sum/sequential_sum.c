#include "sequential_sum.h"

error calculate_sequential_sum_array(int64_t* res_sum, size_t size, char stream_name[MAX_LEN_FILE_NAME]) {
    if (!res_sum || !stream_name)
        return INCORRECT_DATA;

    if (!size) {
        *res_sum = 0;
        return SUCCESS;
    }

    FILE *stream = fopen(stream_name, "rd");
    if (!stream)
        return INCORRECT_DATA;

    error err = SUCCESS;
    *res_sum = 0;
    int buff_num = 0;

    for (size_t k = 0; (k < K) && (!err); k++) {
        for (size_t i = 0; (i < I) && (k + 10 * i < size) && (!err); i++) {
            err = get_int_by_position(&buff_num, k + 10 * i, stream);

            if (!err)
                err = add_num(res_sum, buff_num);
        }
    }

    fclose(stream);
    return err;
}
