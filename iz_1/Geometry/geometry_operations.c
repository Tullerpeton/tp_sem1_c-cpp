#include "geometry_operations.h"

float* find_min_square(const Point3D* pnt1, const Point3D* pnt2,
                       const Point3D* pnt3, const Point3D* pnt4) {
    if (!pnt1 || !pnt2 || !pnt3 || !pnt4)
        return NULL;

    error err = SUCCESS;
    const Point3D* pnt[NUM_TETRAHEDRON_VERTICES] = {pnt1, pnt2, pnt3, pnt4};

    float min_square = 0;
    calc_triangle_square(&min_square, pnt1, pnt2, pnt3);

    float cur_square = min_square;
    for (size_t i = 1; (i < NUM_TETRAHEDRON_VERTICES) && (min_square > EPS) && (!err); i++) {

        err = calc_triangle_square(&cur_square, pnt[i], pnt[(i + 1) % 4], pnt[(i + 2) % 4]);
        min_square = (min_square > cur_square + EPS) ? cur_square : min_square;
    }

    if (err)
        return NULL;

    float* res = (float*) malloc(sizeof(float));
    if (!res)
        return MEMORY_ERROR;

    *res = min_square;
    return res;
}

error calc_triangle_square(float* square, const Point3D* pnt1,
                           const Point3D* pnt2, const Point3D* pnt3) {
    if (!square || !pnt1 || !pnt2 || !pnt3)
        return INCORRECT_DATA;

    error err = SUCCESS;
    if (are_equal(pnt1, pnt2) && are_equal(pnt2, pnt3)) {
        *square = 0;
        return err;
    }

    float line1, line2, line3;
    err = calc_len_line(&line1, pnt1, pnt2);
    if (err)
        return err;

    err = calc_len_line(&line2, pnt2, pnt3);
    if (err)
        return err;

    err = calc_len_line(&line3, pnt3, pnt1);
    if (err)
        return err;

    float half_perimeter = (line1 + line2 + line3) / 2;
    *square = sqrtf((half_perimeter * (half_perimeter - line1) *
                    (half_perimeter - line2) * (half_perimeter - line3)));

    return err;

}

error calc_len_line(float* mlt, const Point3D* pnt1, const Point3D* pnt2) {
    if (!mlt || !pnt1 || !pnt2)
        return INCORRECT_DATA;

    *mlt = sqrtf((pnt2->x - pnt1->x) * (pnt2->x - pnt1->x) +
                (pnt2->y - pnt1->y) * (pnt2->y - pnt1->y) +
                (pnt2->z - pnt1->z) * (pnt2->z - pnt1->z));

    return SUCCESS;
}

