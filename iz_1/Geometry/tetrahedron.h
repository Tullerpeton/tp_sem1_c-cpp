#ifndef LAB_01_TETRAHEDRON_H
#define LAB_01_TETRAHEDRON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "point3D.h"

#define NUM_TETRAHEDRON_VERTICES 4

typedef struct Tetrahedron {
    Point3D vertices[NUM_TETRAHEDRON_VERTICES];
} Tetrahedron;

error input_tetrahedron(Tetrahedron* tetr);
error copy_tetrahedron(Tetrahedron* receiver, const Tetrahedron* source);

#ifdef __cplusplus
}
#endif

#endif
