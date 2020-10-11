#ifndef LAB_01_GEOMETRY_OPERATIONS_H
#define LAB_01_GEOMETRY_OPERATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <math.h>

#include "point3D.h"
#include "tetrahedron.h"

#define EPS 1e-6

float* find_min_square(const Point3D* pnt1, const Point3D* pnt2,
                       const Point3D* pnt3, const Point3D* pnt4);

error calc_triangle_square(float* square, const Point3D* pnt1,
                           const Point3D* pnt2, const Point3D* pnt3);

error calc_len_line(float* mlt, const Point3D* pnt1, const Point3D* pnt2);

#ifdef __cplusplus
}
#endif

#endif
