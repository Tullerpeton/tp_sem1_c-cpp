#ifndef LAB_01_ERROR_CODE_H
#define LAB_01_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum error {
    SUCCESS,
    INCORRECT_DATA,
    INPUT_ERROR,
    CALCULATE_ERROR,
    MEMORY_ERROR,
} error;

#ifdef __cplusplus
}
#endif

#endif
