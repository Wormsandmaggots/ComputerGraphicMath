//
// Created by 48782 on 05.10.2023.
//

#ifndef AMATEMATYKAGRAFIKI_VECTOR_H
#define AMATEMATYKAGRAFIKI_VECTOR_H

#include <valarray>
#include "string"
#include <stdexcept>

class Vector {
public:
    Vector();

    Vector(float, float, float = 0.);
    Vector(const Vector&);
    virtual ~Vector() = default;

    inline float x() const { return _x; };
    inline float y() const { return _y; };
    inline float z() const { return _z; };

    std::string ToString() const;

    float Len() const;
    Vector Normalize() const;
    float DotProduct(const Vector&) const;
    Vector CrossProduct(const Vector&) const;
    float AngleBetween(const Vector&) const;
    bool isClose(Vector&, float) const;

    Vector operator/(const float&) const;
    Vector operator*(const float&) const;
    Vector operator+(const Vector&) const;
    Vector operator-(const Vector&) const;
    Vector operator/(const Vector&) const;

    Vector operator-() const;


    Vector& operator=(const Vector&);

    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);
    Vector& operator*=(const float&);
    Vector& operator/=(const float&);

    bool operator==(const Vector&) const;

    // Static method to find component-wise minimum of two vectors
    static Vector Min(const Vector& a, const Vector& b) {
        Vector result;
        result._x = std::min(a._x, b._x);
        result._y = std::min(a._y, b._y);
        result._z = std::min(a._z, b._z);
        return result;
    }

    // Static method to find component-wise maximum of two vectors
    static Vector Max(const Vector& a, const Vector& b) {
        Vector result;
        result._x = std::max(a._x, b._x);
        result._y = std::max(a._y, b._y);
        result._z = std::max(a._z, b._z);
        return result;
    }

    Vector Normal()
    {
        const float len = this->Length();
        if (len == 0.0f) return {0, 0, 0};
        return *this / len;
    }

    float Length() const
    {
        return sqrt(
                this->x() * this->x() +
                this->y() * this->y() +
                this->z() * this->z());
    }

    void x(const float& x) { _x = x; };
    void y(const float& y) { _y = y; };
    void z(const float& z) { _z = z; };

    void norm() {
        const float len = this->Len();
        if (len != 0.0f) {
            *this = *this / len;  // Normalizuje bieżący wektor
        } else {
            throw std::logic_error("Math error: Cannot normalize a zero-length vector");
        }
    }

private:
    float _x, _y, _z;

    /*void x(const float& x) { _x = x; };
    void y(const float& y) { _y = y; };
    void z(const float& z) { _z = z; };*/

};


#endif //AMATEMATYKAGRAFIKI_VECTOR_H
