#include "task_manager.h"

error task_manager() {
    error err = SUCCESS;

    Tetrahedron tetr;
    err = input_tetrahedron(&tetr);
    if (err)
        return err;

    float* square = find_min_square(&(tetr.vertices[0]), &(tetr.vertices[1]),
                                    &(tetr.vertices[2]), &(tetr.vertices[3]));
    if (!square) {
        err = CALCULATE_ERROR;
        return err;
    }

    printf("Min square = %.2g", *square);
    free(square);

    return err;
}
