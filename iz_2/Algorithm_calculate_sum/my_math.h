#ifndef IZ_2_MY_MATH_H
#define IZ_2_MY_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <inttypes.h>

#include "Errors/error_code.h"
#include "Config/configuration.h"

error add_num(int64_t* sum, int num);

#ifdef __cplusplus
}
#endif

#endif
