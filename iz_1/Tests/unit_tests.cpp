#include <fstream>
#include "gtest/gtest.h"
#include "../Geometry/point3D.h"
#include "../Geometry/tetrahedron.h"
#include "../Geometry/geometry_operations.h"


// Тестирование модуля point3D
TEST(Point3D, input_point) {
    // Нулевой указатель
    EXPECT_EQ(input_point3D(NULL), INCORRECT_DATA);
}

TEST(Point3D, are_equal) {
    // Точки не равны
    Point3D pnt1 = {1, 3, 2};
    Point3D pnt2 = {3, 3, 2};
    EXPECT_EQ(are_equal(&pnt1, &pnt2), false);

    // Точки равны
    Point3D pnt3 = {3, 3, 2};
    Point3D pnt4 = {3, 3, 2};
    EXPECT_EQ(are_equal(&pnt3, &pnt4), true);

    // Одна из точек - NULL
    EXPECT_EQ(are_equal(&pnt4, NULL), false);
}



// Тестирование модуля tetrahedron
TEST(Tetrahedron, input_tetrahedron) {
    // Нулевой указатель
    EXPECT_EQ(input_tetrahedron(NULL), INCORRECT_DATA);
}

TEST(Tetrahedron, copy_tetrahedron) {
    // Тетраедр скопирован корректно
    Tetrahedron tetr1 = {Point3D{1, 2, 3},
                         Point3D{2, 1, 3},
                         Point3D{1, 3, 3},
                         Point3D{1, 1, 3}};

    Tetrahedron tetr2 = {Point3D{0, 0, 0},
                         Point3D{0, 0, 0},
                         Point3D{0, 0, 0},
                         Point3D{0, 0, 0}};


    EXPECT_EQ(copy_tetrahedron(&tetr1, &tetr2), SUCCESS);
    EXPECT_EQ(((are_equal(&tetr1.vertices[0], &tetr2.vertices[0])) *
                    are_equal(&tetr1.vertices[1], &tetr2.vertices[1]) *
                    are_equal(&tetr1.vertices[2], &tetr2.vertices[2]) *
                    are_equal(&tetr1.vertices[3], &tetr2.vertices[3])), true);

    // Один из тетраэдров - NULL
    EXPECT_EQ(copy_tetrahedron(NULL, &tetr2), INCORRECT_DATA);
}



// Тестирование модуля geometry_operation
TEST(geometry_operations, calc_len_line) {
    // Отрезок ненулевой длины
    Point3D pnt1 = {3, 0, 1};
    Point3D pnt2 = {0, 4, 1};
    float mlt = 0;
    EXPECT_EQ(calc_len_line(&mlt, &pnt1, &pnt2), SUCCESS);
    EXPECT_EQ(abs(mlt - 5) < EPS, true);

    // Отрезок нулевой длины
    Point3D pnt3 = {0, 2, 3};
    Point3D pnt4 = {0, 2, 3};
    float mlt_null = 1;
    EXPECT_EQ(calc_len_line(&mlt_null, &pnt3, &pnt4), SUCCESS);
    EXPECT_EQ(abs(mlt_null) < EPS, true);

    // Один из концов отрезка - NULL
    EXPECT_EQ(calc_len_line(&mlt, &pnt1, NULL), INCORRECT_DATA);

    // Переменная mlt - NULL
    EXPECT_EQ(calc_len_line(NULL, &pnt1, &pnt2), INCORRECT_DATA);
}

TEST(geometry_operations, calc_triangle_square) {
    // Треугольник ненулевой площади
    Point3D pnt1 = {3, 0, 2};
    Point3D pnt2 = {0, 0, 2};
    Point3D pnt3 = {0, 4, 2};
    float square = 0;
    EXPECT_EQ(calc_triangle_square(&square, &pnt1, &pnt2, &pnt3), SUCCESS);
    EXPECT_EQ(abs(square - 6) < EPS, true);

    // Треугольник нулевой площади (вырожден в точку)
    Point3D pnt4 = {1, 1, 1};
    Point3D pnt5 = {1, 1, 1};
    Point3D pnt6 = {1, 1, 1};
    float square_null = 1;
    EXPECT_EQ(calc_triangle_square(&square_null, &pnt4, &pnt5, &pnt6), SUCCESS);
    EXPECT_EQ(square_null < EPS, true);

    // Треугольник нулевой площади (вырожден в прямую)
    square_null = 1;
    EXPECT_EQ(calc_triangle_square(&square_null, &pnt1, &pnt5, &pnt6), SUCCESS);
    EXPECT_EQ(square_null < EPS, true);

    // Одна из вершин треугольника - NULL
    EXPECT_EQ(calc_triangle_square(&square, NULL, &pnt5, &pnt6), INCORRECT_DATA);

    // Переменная square - NULL
    EXPECT_EQ(calc_triangle_square(NULL, &pnt1, &pnt5, &pnt6), INCORRECT_DATA);
}

TEST(geometry_operations, find_min_square) {
    // Тетраедр вырожден в точку
    Point3D pnt1 = {0, 0, 0};
    Point3D pnt2 = {0, 0, 0};
    Point3D pnt3 = {0, 0, 0};
    Point3D pnt4 = {0, 0, 0};
    float *min_square = NULL;
    min_square = find_min_square(&pnt1, &pnt2, &pnt3, &pnt4);
    EXPECT_EQ(abs(*min_square) < EPS, true);
    free(min_square);

    // Тетраедр вырожден в отрезок
    Point3D pnt5 = {2, 0, 0};
    min_square = find_min_square(&pnt5, &pnt1, &pnt2, &pnt3);
    EXPECT_EQ(abs(*min_square) < EPS, true);
    free(min_square);

    // Тетраедр вырожден в треугольник
    Point3D pnt6 = {0, -2, 0};
    Point3D pnt7 = {0, -2, 0};
    Point3D pnt8 = {-1, -1, 0};
    Point3D pnt9 = {1, 1, 0};
    min_square = find_min_square(&pnt6, &pnt7, &pnt8, &pnt9);
    EXPECT_EQ(abs(*min_square) < EPS, true);
    free(min_square);

    // Ненулевая минимальная площадь грани тетраэдра
    Point3D pnt10 = {0, 0, 0};
    Point3D pnt11 = {4, 0, 0};
    Point3D pnt12 = {0, 4, 0};
    Point3D pnt13 = {0, 0, 3};

    min_square = find_min_square(&pnt10, &pnt11, &pnt12, &pnt13);
    EXPECT_EQ(abs(*min_square - 6) < EPS, true);
    free(min_square);

    // Одна и точек тетраэдра - NULL
    min_square = find_min_square(NULL, &pnt11, &pnt12, &pnt13);
    EXPECT_EQ(min_square == NULL, true);
}



