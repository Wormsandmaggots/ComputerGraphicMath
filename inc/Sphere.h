#ifndef SPHERE_H
#define SPHERE_H
#include "Vector.h"
#include <string>
#include <sstream>

class Sphere {
public:
    Vector c;  // Środek sfery
    float r;   // Promień sfery

    // Konstruktor domyślny
    Sphere() : r(0) {}

    // Konstruktor kopiujący
    Sphere(const Sphere& s) : c(s.c), r(s.r) {}

    // Konstruktor z wektorem środka i promieniem
    Sphere(const Vector& p, float r) : c(p), r(r) {}

    std::string ToString() const {
        std::stringstream ss;
        ss << "Sphere: Center = " << c.ToString() << ", Radius = " << r;
        return ss.str();
    }
};
#endif