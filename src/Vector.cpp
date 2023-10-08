//
// Created by 48782 on 05.10.2023.
//

#include <stdexcept>
#include <sstream>
#include "Vector.h"
#include "cmath"

Vector::Vector(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vector::Vector(const Vector & another) : _x(another._x), _y(another._y), _z(another._z) {}

float Vector::Len() const {
    return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
}

Vector Vector::Normalize() const {
    return (*this)/Len();
}

float Vector::DotProduct(const Vector & another) const {
    return _x * another._x + _y * another._y + _z * another._z;
}

//cross product daje wketor prostopadły do płaszczyzny
//czytaj, dwóch wektorów
Vector Vector::CrossProduct(const Vector & another) const {
    return       {_y * another._z - _z * another._y,
                  _z * another._x - _x * another._z,
                  _x * another._y - _y * another._x};
}

Vector Vector::operator/(const float & val) const {
    if (val == 0) throw std::invalid_argument("Cannot divide by zero");

    return {_x / val, _y / val, _z / val};
}

Vector Vector::operator*(const float & val) const {
    return {_x * val, _y * val, _z * val};
}

Vector Vector::operator+(const Vector & val) const {
    return {_x + val._x, _y + val._y, _z + val._z};
}

Vector Vector::operator-(const Vector & val) const {
    return {_x - val._x, _y - val._y, _z - val._z};
}

Vector& Vector::operator=(const Vector & val) {

    if(&val != this)
    {
        x(val._x);
        y(val._y);
        z(val._z);
    }

    return *this;
}

Vector& Vector::operator+=(const Vector & val) {
    x(_x + val._x);
    y(_y + val._y);
    z(_z + val._z);
    return *this;
}

Vector& Vector::operator-=(const Vector & val) {
    x(_x - val._x);
    y(_y - val._y);
    z(_z - val._z);
    return *this;
}

Vector &Vector::operator*=(const float & val) {
    x(_x * val);
    y(_y * val);
    z(_z * val);
    return *this;
}

Vector &Vector::operator/=(const float & val) {
    if (val == 0) throw std::invalid_argument("Cannot divide by zero");

    x(_x / val);
    y(_y / val);
    z(_z / val);
    return *this;
}

bool Vector::operator==(const Vector & another) const {

    return &another == this ||
           _x == another._x &&
           _y == another._y &&
           _z == another._z;
}

std::string Vector::ToString() const {
    std::stringstream ss;

    ss << "Vector: x = " << _x << ", y = " << _y << ", z = " << _z;
    return ss.str();
}

//iloczyn skalarny = a1*b1 + a2*b2 + a3*b3...
//iloczyn skalarny = długość(v1) * długość(v2) * cos(a)
//cos(a) = iloczyn skalarny / (długość(v1) * długość(v2))
//jesli iloczyn skalarny = 0 wektory prostopadłe
float Vector::AngleBetween(const Vector & another) const {
    float cosValue = DotProduct(another) / (Len() * another.Len());
    return (acos(cosValue) * 180) / M_PI;
}



