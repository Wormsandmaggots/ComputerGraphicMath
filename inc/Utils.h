#ifndef UTILS_H
#define UTILS_H
#include "Line.h"
#include "Plane.h"
#include "Segment.h"
#include "Sphere.h"
#include <cmath>
#include <vector>
#include <optional>


class Utils {
public:
    // Oblicza punkt przecięcia dwóch prostych
    static Vector LineIntersect(const Line& line1, const Line& line2) {
        Vector cross = line1.v.CrossProduct(line2.v);
        float t = line2.p.DotProduct(cross) - line1.p.DotProduct(cross) / cross.DotProduct(cross);
        return line1.p + line1.v * t;
    }

    // Oblicza kąt między dwoma prostymi
    static float LineAngle(const Line& line1, const Line& line2) {
        Vector dir1 = line1.v.Normalize();
        Vector dir2 = line2.v.Normalize();
        float dot = dir1.DotProduct(dir2);
        return acos(dot) * 180 / M_PI;  // Konwersja z radianów na stopnie
    }

    // Znajduje punkt przecięcia prostej z płaszczyzną
    static Vector LinePlaneIntersect(const Line& line, const Plane& plane) {
        float d = plane.n.DotProduct(plane.p);
        float t = -(plane.n.DotProduct(line.p) + d) / plane.n.DotProduct(line.v);
        return line.p + line.v * t;
    }
    // Oblicza kąt między prostą a płaszczyzną
    static float LinePlaneAngle(const Line& line, const Plane& plane) {
        Vector lineDir = line.v.Normalize();
        Vector planeNormal = plane.n.Normalize();
        float dot = lineDir.DotProduct(planeNormal);
        return acos(std::abs(dot)) * 180 / M_PI; // Konwersja z radianów na stopnie
    }

    // Znajduje linię przecięcia dwóch płaszczyzn
    static Line PlaneIntersect(const Plane& plane1, const Plane& plane2) {
        Vector lineDir = plane1.n.CrossProduct(plane2.n);
        float d1 = -plane1.n.DotProduct(plane1.p);
        float d2 = -plane2.n.DotProduct(plane2.p);
        Vector linePoint = (lineDir.CrossProduct(plane2.n) * d1 + plane1.n.CrossProduct(lineDir) * d2) / pow(lineDir.Len(), 2);
        return Line(linePoint, lineDir);
    }

    // Oblicza kąt między dwoma płaszczyznami
    static float PlaneAngle(const Plane& plane1, const Plane& plane2) {
        Vector n1 = plane1.n.Normalize();
        Vector n2 = plane2.n.Normalize();
        float dot = n1.DotProduct(n2);
        return acos(std::abs(dot)) * 180 / M_PI; // Konwersja z radianów na stopnie
    }
    // Znalezienie punktu przecięcia dwóch odcinków
    static std::optional<Vector> SegmentIntersect(const Segment& seg1, const Segment& seg2) {
        Vector dir1 = seg1.e - seg1.s;
        Vector dir2 = seg2.e - seg2.s;
        Vector h = seg2.s - seg1.s;

        float cross1 = dir1.CrossProduct(h).Len();
        float cross2 = dir1.CrossProduct(dir2).Len();

        if (cross2 != 0) {
            float t = cross1 / cross2;
            if (t >= 0 && t <= 1) {
                return seg2.s + dir2 * t;
            }
        }
        return std::nullopt; // Brak przecięcia
    }

    // Znalezienie punktów przecięcia prostej ze sferą
    static std::vector<Vector> LineSphereIntersect(const Line& line, const Sphere& sphere) {
        std::vector<Vector> points;
        Vector oc = line.p - sphere.c;

        float a = line.v.DotProduct(line.v);
        float b = 2.0f * oc.DotProduct(line.v);
        float c = oc.DotProduct(oc) - sphere.r * sphere.r;

        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return points; // Brak przecięć
        }

        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);

        points.push_back(line.p + line.v * t1);
        if (discriminant != 0) {
            points.push_back(line.p + line.v * t2);
        }

        return points;
    }
};
#endif