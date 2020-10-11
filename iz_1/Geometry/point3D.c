#include "point3D.h"

error input_point3D(Point3D* pnt) {
    if (!pnt)
        return INCORRECT_DATA;

    printf("Input point = ");
    float x, y, z;
    if (scanf("%f %f %f", &x, &y, &z) != 3)
        return INPUT_ERROR;

    pnt->x = x;
    pnt->y = y;
    pnt->z = z;

    return SUCCESS;
}

int are_equal(const Point3D* pnt1, const Point3D* pnt2) {
    if (!pnt1 || !pnt2)
        return 0;

    return ((pnt1->x == pnt2->x) && (pnt1->y == pnt2->y) && (pnt1->z == pnt2->z)) ? 1 : 0;
}

