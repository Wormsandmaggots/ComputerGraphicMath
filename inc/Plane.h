#ifndef PLANE_H
#define PLANE_H

#include "Vector.h"
#include <string>
#include <sstream>

class Plane {
public:
    Vector n;  // Wektor normalny płaszczyzny
    Vector p;  // Punkt na płaszczyźnie
    float d;   // Wartość d w równaniu ogólnym płaszczyzny (ax + by + cz + d = 0)

    // Konstruktor domyślny
    Plane() {}

    // Konstruktor kopiujący
    Plane(const Plane& plane) : n(plane.n), p(plane.p), d(plane.d) {}

    // Konstruktor z parametrami równania ogólnego
    Plane(float a, float b, float c, float d) : n(Vector(a, b, c)), d(d) {
        // Obliczenie punktu na płaszczyźnie
        // Uwzględniamy specjalne przypadki, aby uniknąć dzielenia przez zero
        if (c != 0) {
            p = Vector(0, 0, -d / c);
        } else if (b != 0) {
            p = Vector(0, -d / b, 0);
        } else if (a != 0) {
            p = Vector(-d / a, 0, 0);
        }
    }

    // Metoda ToString dla reprezentacji tekstowej płaszczyzny
    std::string ToString() const {
        std::stringstream ss;
        ss << "Plane: n = " << n.ToString() << ", p = " << p.ToString() << ", d = " << d;
        return ss.str();
    }
};

#endif