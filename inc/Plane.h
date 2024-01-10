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

   Plane(float a, float b, float c, float d)
   {
       this->n = {a, b, c};
       //this->n.Normalize();

       if (c != 0) {
           this->p = {0, 0, -d / c};
       } else if (b != 0) {
           this->p = {0, -d / b, 0};
       }
   }

};

#endif