#ifndef LAB_01_POINT3D_H
#define LAB_01_POINT3D_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "Errors/error_code.h"

typedef struct Point3D {
    float x;
    float y;
    float z;
} Point3D;

error input_point3D(Point3D* pnt);
int are_equal(const Point3D* pnt1, const Point3D* pnt2);

#ifdef __cplusplus
}
#endif

#endif
