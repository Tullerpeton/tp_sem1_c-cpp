#ifndef IZ_2_BIN_FILE_ROUTINES_H
#define IZ_2_BIN_FILE_ROUTINES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <inttypes.h>

#include "Errors/error_code.h"

error get_int_by_position(int* num, size_t index, FILE* stream);

#ifdef __cplusplus
}
#endif

#endif
