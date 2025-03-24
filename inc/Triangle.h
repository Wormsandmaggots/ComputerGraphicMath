//
// Created by Radek on 24.03.2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vector.h"

class Triangle
{
public:
    Vector a, b, c;
    Vector ab, ac, cb;
    Vector normal;

    Triangle(Vector A, Vector B, Vector C) : a(A), b(B), c(C) {
        ab = B - A;
        ac = C - A;
        cb = B - C;
        normal = ab.CrossProduct(ac);
    };
};

#endif //TRIANGLE_H
