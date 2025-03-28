#ifndef UTILS_H
#define UTILS_H
#include "Line.h"
#include "Plane.h"
#include "Segment.h"
#include "Sphere.h"
#include <cmath>
#include <vector>
#include <optional>

#include "Ray.h"
#include "Triangle.h"

float e = 0.0000001;

class Intersections {
public:

    static bool SphereRayIntersect(const Sphere &sphere, const Ray &ray)
    {
        const Vector rayMinusSphere = ray.start - sphere.c;
        const float rayMinusSphereLen = rayMinusSphere.Len();
        float b = (rayMinusSphere * 2).DotProduct(ray.dir);
        float c = rayMinusSphereLen * rayMinusSphereLen - sphere.r * sphere.r;
        float delta = b * b - 4 * c;

        return delta >= 0;
    }

    static std::vector<Vector> SphereRayIntersectPoints(Sphere &sphere, const Ray &ray) {
        std::vector<Vector> points;

        if(SphereRayIntersect(sphere, ray)) {
            const Vector rayMinusSphere = ray.start - sphere.c;
            const float rayMinusSphereLen = rayMinusSphere.Len();
            const float b = 2 * rayMinusSphere.DotProduct(ray.dir);
            const float c = rayMinusSphereLen * rayMinusSphereLen - sphere.r * sphere.r;
            float delta = b * b - 4 * c;

            const float t1 = (-b - sqrt(delta)) / 2;
            const float t2 = (-b + sqrt(delta)) / 2;

            points.push_back(ray.start + ray.dir * t1);

            if(delta > 0)
                points.push_back(ray.start + ray.dir * t2);
        }

        return points;
    }

    static Vector RayPlaneIntersect(Plane &plane, const Ray &ray) {
        float d = -plane.n.DotProduct(plane.p);
        float t = -(plane.n.DotProduct(ray.start) + d) / plane.n.DotProduct(ray.dir);
        return ray.start + ray.dir * t;
    }

    static bool RayTriangleIntersect2(const Ray& ray, const Triangle &triangle) {
        float d = triangle.normal.DotProduct(triangle.a);

    }

    static bool RayTriangleIntersect(const Ray& ray, const Triangle &triangle) {

        const float dot = triangle.normal.DotProduct(ray.dir);


        if(fabsf(dot) < e)
            return false;

        const float t = triangle.normal.DotProduct(triangle.a - ray.start) / dot;

        if(t < 0)
            return false;

        Vector ip = ray.start + ray.dir * t;

        Vector ap = ip - triangle.a;
        Vector bp = ip - triangle.b;
        Vector cp = ip - triangle.c;

        Vector v1 = triangle.ab.CrossProduct(ap);
        Vector v2 = triangle.ac.CrossProduct(bp);
        Vector v3 = triangle.cb.CrossProduct(cp);

        return v1.DotProduct(triangle.normal) >= 0 &&
            v2.DotProduct(triangle.normal) >= 0 &&
                v3.DotProduct(triangle.normal) >= 0;
    }


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
};
#endif