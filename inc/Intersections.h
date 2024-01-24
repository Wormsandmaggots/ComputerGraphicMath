#ifndef UTILS_H
#define UTILS_H
#include "Line.h"
#include "Plane.h"
#include "Segment.h"
#include "Sphere.h"
#include <cmath>
#include <vector>
#include <optional>
#include <algorithm>


class Intersections {
public:
    // Oblicza punkt przecięcia dwóch prostych
    static Vector LineIntersect(const Line& line1, const Line& line2) {
        Vector cross = line1.v.CrossProduct(line2.v);
        float t = line2.p.DotProduct(cross) - line1.p.DotProduct(cross) / cross.DotProduct(cross);
        return line1.p + line1.v * t;
    }

    // Oblicza kąt między dwoma prostymi
    /*static float LineAngle(const Line& line1, const Line& line2) {
        Vector dir1 = line1.v.Normalize();
        Vector dir2 = line2.v.Normalize();
        float dot = dir1.DotProduct(dir2);
        return acos(dot) * 180 / M_PI;  // Konwersja z radianów na stopnie
    }*/
    // Oblicza kąt między dwoma prostymi
    static float LineAngle(const Line& line1, const Line& line2) {
        Vector dir1 = line1.p.Normalize();
        Vector dir2 = line2.p.Normalize();
        return dir1.AngleBetween(dir2); // Wywołanie metody AngleBetween na wektorach kierunkowych
    }


    // Znajduje punkt przecięcia prostej z płaszczyzną
    static Vector LinePlaneIntersect(const Line& line, const Plane& plane) {
        float d = -plane.n.DotProduct(plane.p); // Użycie minusa dla d
        float t = -(plane.n.DotProduct(line.p) + d) / plane.n.DotProduct(line.v); // Używając wektora kierunkowego linii w mianowniku
        return line.p + line.v * t; // Obliczenie punktu przecięcia
    }


    // Oblicza kąt między prostą a płaszczyzną
    static float LinePlaneAngle(const Line& line, const Plane& plane) {
        Vector lineDir = line.p.Normalize();
        Vector planeNormal = plane.n.Normalize();
        float dot = lineDir.DotProduct(planeNormal);
        return asin(std::abs(dot)) * 180 / M_PI; // Użycie asin zamiast acos
    }

    static Line PlaneIntersect(const Plane& plane1, const Plane& plane2) {

        Line result;
        result.v = plane1.n.CrossProduct(plane2.n); // Wektor kierunkowy linii przecięcia
        float length = result.v.Len();

        // Sprawdzenie, czy płaszczyzny nie są równoległe
        //if(length == 0) return Line(); // Zwróć pustą linię, jeśli płaszczyzny są równoległe lub pokrywające się

        // Obliczanie punktu na linii przecięcia
        result.p = (result.v.CrossProduct(plane2.n) * plane1.d +
                    plane1.n.CrossProduct(result.v) * plane2.d) / length;
        return result;
    }

    static float PlaneAngle(const Plane& plane1, const Plane& plane2)
    {
        return plane1.n.AngleBetween(plane2.n);
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

    static bool IsRayIntersectAABBUnitBox(Line line)
    {
        Vector boxMin(-1, -1, -1);
        Vector boxMax(1, 1, 1);

        // Perform element-wise division using DivideElementWise
        Vector tMin = (boxMin - line.p) / line.v;
        Vector tMax = (boxMax - line.p) / line.v;

        // Continue using the Vector::Min and Vector::Max static methods
        Vector t1 = Vector::Min(tMin, tMax);
        Vector t2 = Vector::Max(tMin, tMax);

        // Extract the minimum and maximum values of t
        //double tNear = std::max({t1.x(), t1.y(), t1.z()});
        //double tFar = std::min({t2.x(), t2.y(), t2.z()});
        double tNear = std::max(std::max(t1.x(),t1.y()), t1.z());
        double tFar = std::min(std::min(t2.x(),t2.y()), t2.z());
        // Check if the ray intersects the AABB unit box
        return tFar > tNear;
    }

    static bool IsPointOnAABBEdge(const Vector& point, const Vector& center, float a, float b, float c) {
        float tolerance = 0.95f;  // Ustaw dowolną tolerancję, aby uwzględnić pewien margines błędu

        bool onEdgeX = (std::abs(point.x() - center.x()) >= a - tolerance) &&
                       (std::abs(point.y() - center.y()) <= b + tolerance) &&
                       (std::abs(point.z() - center.z()) <= c + tolerance);

        bool onEdgeY = (std::abs(point.x() - center.x()) <= a + tolerance) &&
                       (std::abs(point.y() - center.y()) >= b - tolerance) &&
                       (std::abs(point.z() - center.z()) <= c + tolerance);

        bool onEdgeZ = (std::abs(point.x() - center.x()) <= a + tolerance) &&
                       (std::abs(point.y() - center.y()) <= b + tolerance) &&
                       (std::abs(point.z() - center.z()) >= c - tolerance);

        return onEdgeX || onEdgeY || onEdgeZ;
    }

};
#endif