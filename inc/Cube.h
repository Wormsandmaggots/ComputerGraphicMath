//
// Created by jakub on 24.01.2024.
//

#ifndef AMATEMATYKAGRAFIKI_CUBE_H
#define AMATEMATYKAGRAFIKI_CUBE_H
#include <vector>
#include "Plane.h"  // Make sure this path is correct
#include "Vector.h"

class Cube {
public:
    std::vector<Plane> planes;
    double size = 1;  // Length of the edge

    Cube(int size)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                float sign = k % 2 == 0 ? 1.0f : -1.0f;
                Plane plane;

                // Zamiast używać tablicy vec, inicjujemy bezpośrednio wektory
                if (i == 0) {
                    plane.p = Vector(sign * size, 0, 0);  // X axis
                    plane.n = Vector(sign, 0, 0);
                } else if (i == 1) {
                    plane.p = Vector(0, sign * size, 0);  // Y axis
                    plane.n = Vector(0, sign, 0);
                } else if (i == 2) {
                    plane.p = Vector(0, 0, sign * size);  // Z axis
                    plane.n = Vector(0, 0, sign);
                }

                planes.push_back(plane);
            }
        }
    }

};
#endif //AMATEMATYKAGRAFIKI_CUBE_H
