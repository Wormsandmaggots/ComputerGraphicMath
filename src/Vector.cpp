//
// Created by 48782 on 05.10.2023.
//

#include <stdexcept>
#include <sstream>
#include "Vector.h"
#include "cmath"

Vector::Vector(float x, float y, float z) {
    _x = x;
    _y = y;
    _z = z;
}

Vector::Vector(Vector & another) {
    x(another.x());
    y(another.y());
    z(another.z());
}

float Vector::Len() const {
    return sqrt(pow(x(), 2) + pow(y(), 2) + pow(z(), 2));
}

Vector Vector::Normalize() const {
    return (*this)/Len();
}

float Vector::DotProduct(const Vector & another) const {
    return x() * another.x() + y() * another.y() + z() * another.z();
}

//cross product daje wketor prostopadły do płaszczyzny
//czytaj, dwóch wektorów
Vector Vector::CrossProduct(const Vector & another) const {
    return       {y() * another.z() - z() * another.y(),
                  z() * another.x() - x() * another.z(),
                  x() * another.y() - y() * another.x()};
}

Vector Vector::operator/(const float & val) const {
    if (val == 0) throw std::invalid_argument("Cannot divide by zero");

    return {x() / val, y() / val, z() / val};
}

Vector Vector::operator*(const float & val) const {
    return {x() * val, y() * val, z() * val};
}

Vector Vector::operator+(const Vector & val) const {
    return {x() + val.x(), y() + val.y(), z() + val.z()};
}

Vector Vector::operator-(const Vector & val) const {
    return {x() - val.x(), y() - val.y(), z() - val.z()};
}

Vector& Vector::operator=(const Vector & val) {

    if(&val != this)
    {
        x(val.x());
        y(val.y());
        z(val.z());
    }

    return *this;
}

Vector& Vector::operator+=(const Vector & val) {
    x(x() + val.x());
    y(y() + val.y());
    z(z() + val.z());
    return *this;
}

Vector& Vector::operator-=(const Vector & val) {
    x(x() - val.x());
    y(y() - val.y());
    z(z() - val.z());
    return *this;
}

Vector &Vector::operator*=(const float & val) {
    x(x() * val);
    y(y() * val);
    z(z() * val);
    return *this;
}

Vector &Vector::operator/=(const float & val) {
    if (val == 0) throw std::invalid_argument("Cannot divide by zero");

    x(x() / val);
    y(y() / val);
    z(z() / val);
    return *this;
}

bool Vector::operator==(const Vector & another) const {

    return &another == this ||
           x() == another.x() &&
           y() == another.y() &&
           z() == another.z();
}

std::string Vector::ToString() const {
    std::stringstream ss;

    ss << "Vector: x = " << x() << ", y = " << y() << ", z = " << z();
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



