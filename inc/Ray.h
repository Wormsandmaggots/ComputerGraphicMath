//
// Created by Radek on 24.03.2025.
//

#ifndef RAY_H
#define RAY_H
#include "Vector.h"

class Ray {
public:
    Vector dir;
    Vector start;

    Ray(const Vector& origin, const Vector& direction);

    static Ray StartToEnd(const Vector& s, const Vector& e) {
        return Ray(s, e - s);
    }
};


#endif //RAY_H
