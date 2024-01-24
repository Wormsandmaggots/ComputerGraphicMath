//
// Created by jakub on 24.01.2024.
//

#ifndef AMATEMATYKAGRAFIKI_RTX_H
#define AMATEMATYKAGRAFIKI_RTX_H

#include <iostream>
#include "Line.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Intersections.h"
#include "Vector.h"
#include "Cube.h"


class RTX {
public:
    RTX() {
        for (int i = 0; i < 60; i++) {
            for (int k = 0; k < 60; k++) {
                screen[i][k] = false;
            }
        }
    }

    void Draw() {
        for (int i = 0; i < 60; i++)
        {
            for (int k = 0; k < 60; k++)
            {
                if (screen[i][k])
                    std::cout << "#";
                else
                    std::cout << ".";
            }
            std::cout << "\n";
        }
    }

    void RayCast(const Vector &cameraPosition, const Vector &cameraDirection) {
        float pixelSize = 4.0f / 60.0f;
        float screenDistance = 1.0f;

        Vector screenPosition = cameraPosition + cameraDirection * screenDistance;

        Vector worldUp{ 0, 0, 1 };

        Vector screenLeft = ((screenPosition - cameraPosition) * -1).CrossProduct(worldUp);
        //screenLeft.Normalize();
        screenLeft.norm();
        Vector screenDown = screenPosition.CrossProduct(screenLeft);
        //screenDown.Normalize();
        screenDown.norm();

        for (int i = 0; i < 60; i++)
        {
            for (int k = 0; k < 60; k++)
            {
                // Oblicz pozycję pixela na ekranie
                Vector pixelLocation = screenPosition
                                       + screenLeft * ((k - 30) * pixelSize)
                                       + screenDown * ((i - 30) * pixelSize);

                Line line = Line::StartToEnd(cameraPosition, pixelLocation);
                screen[i][k] = Intersections::IsRayIntersectAABBUnitBox(line);
            }
        }

    }

private:
    bool screen[60][60] = {{false}};
};
#endif //AMATEMATYKAGRAFIKI_RTX_H
