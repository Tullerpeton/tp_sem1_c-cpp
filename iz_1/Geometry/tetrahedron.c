#include "tetrahedron.h"

error input_tetrahedron(Tetrahedron* tetr) {
    if (!tetr)
        return INCORRECT_DATA;

    error err = SUCCESS;
    printf("Input 4 points(x y z)\n");

    Tetrahedron buf_tetr;
    for (size_t i = 0; i < NUM_TETRAHEDRON_VERTICES && !err; i++)
        err = input_point3D(&(buf_tetr.vertices[i]));

    if (err)
        return err;

    err = copy_tetrahedron(tetr, &buf_tetr);
    return err;
}


error copy_tetrahedron(Tetrahedron* receiver, const Tetrahedron* source) {
    if (!receiver || !source)
        return INCORRECT_DATA;

    for (size_t i = 0; i < NUM_TETRAHEDRON_VERTICES; i++)
        receiver->vertices[i] = source->vertices[i];

    return SUCCESS;
}

