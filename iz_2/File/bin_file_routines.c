#include "bin_file_routines.h"

error get_int_by_position(int* num, size_t index, FILE* stream) {
    if (!num || !stream)
        return INCORRECT_DATA;

    if (fseek(stream, index * sizeof(int), SEEK_SET))
        return FUNCTION_ERROR;

    if (fread(num, sizeof(int), 1, stream) != 1)
        return INPUT_ERROR;

    return SUCCESS;
}
