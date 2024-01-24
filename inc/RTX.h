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
                screen[i][k] = '.';
            }
        }
    }

    void Draw() {
        for (int i = 0; i < 60; i++)
        {
            for (int k = 0; k < 60; k++)
            {
                std::cout << screen[i][k];
            }
            std::cout << "\n";
        }
    }

    void RayCast(const Vector &cameraPosition, const Vector &cameraDirection) {
        float pixelSize = 0.5f / 60.0f;
        float screenDistance = 1.0f;

        Vector screenPosition = cameraPosition + cameraDirection * screenDistance;

        Vector worldUp{ 0, 1, 0 };

        Vector check(0.0, 1.0, 0.0);

        if (cameraDirection.isClose(check, 0.1))
        {
            worldUp = Vector(0.0, 0.0, 1.0);
        }

        Vector diff = screenPosition - cameraPosition;
        diff *= -1;
        Vector screenLeft = diff.CrossProduct(worldUp).Normalize();

        Vector screenDown = screenPosition.CrossProduct(screenLeft).Normalize();

        for (int i = 0; i < 60; i++)
        {
            for (int k = 0; k < 60; k++)
            {
                Vector pixelLocation = screenPosition + (screenLeft * ((k - 30) * pixelSize));
                pixelLocation = pixelLocation + (screenDown * ((i - 30) * pixelSize));

                Line line = Line::StartToEnd(cameraPosition, pixelLocation);
                if(Intersections::IsRayIntersectAABBUnitBox(line))
                {
                    screen[i][k] = '0';  // Symbol for inside the box
                }
                else
                {
                    screen[i][k] = '.';
                }
            }
        }

    }

private:
    char screen[60][60] = {{'.'}};
};
#endif //AMATEMATYKAGRAFIKI_RTX_H
