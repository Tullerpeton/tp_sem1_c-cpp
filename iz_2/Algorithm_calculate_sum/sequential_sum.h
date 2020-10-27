#ifndef IZ_2_SEQUENTIAL_SUM_H
#define IZ_2_SEQUENTIAL_SUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <inttypes.h>

#include "File/bin_file_routines.h"
#include "Config/configuration.h"
#include "Errors/error_code.h"
#include "my_math.h"

error calculate_sequential_sum_array(int64_t* res_sum, size_t size, char stream_name[MAX_LEN_FILE_NAME]);

#ifdef __cplusplus
}
#endif

#endif
