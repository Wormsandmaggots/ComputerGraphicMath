//
// Created by 48782 on 08.10.2023.
//

#include <stdexcept>
#include "Quaternion.h"
#include <cmath>
#include <sstream>

Quaternion::Quaternion(const Vector &vec, float real) : _vec(vec), _real(real) {}

Quaternion::Quaternion(float i, float j, float k, float r) : _vec(Vector(i,j,k)), _real(r) {}

Quaternion Quaternion::operator*(const Quaternion & another) const {
    float r = _real * another._real - _vec.DotProduct(another._vec);
    Vector vec = another._vec * _real + _vec * another._real + _vec.CrossProduct(another._vec);
    return {vec, r};
}

Quaternion Quaternion::operator+(const Quaternion & another) const {
    return {_vec + another._vec, _real + another._real};
}

Quaternion Quaternion::operator-(const Quaternion & another) const {
    return {_vec - another._vec, _real - another._real};
}

Quaternion Quaternion::operator/(const Quaternion & another) const {
    float div = another._real * another._real + another._vec.DotProduct(another._vec);

    if(div == 0)
        throw std::invalid_argument("Cannot divide by zero");

    float r = _real * another._real + _vec.DotProduct(another._vec);
    Vector vec = (another._vec * -_real + _vec * another._real - _vec.CrossProduct(another._vec)) / div;

    return {vec, r};
}

Quaternion& Quaternion::operator=(const Quaternion & another) {
    if(&another == this)
        return *this;

    _vec = another._vec;
    _real = another._real;

    return *this;
}

bool Quaternion::operator==(const Quaternion & another) const {
    if(&another == this)
        return true;

    return _vec == another._vec && _real == another._real;
}

//to powinno być mnożenie dwóch quaternionów chyba
//void Quaternion::Rotate(float angle) {
//    float qDiv = ((_vec.x() + _vec.y() + _vec.z()) /
//            sqrt(_vec.x() * _vec.x() + _vec.y() * _vec.y() + _vec.z() * _vec.z())) *
//            sin(angle/2.);
//
//    float q = (float)cos(angle / 2.) + qDiv;
//    float qMinusOne = (float)cos(angle / 2.) - qDiv;
//
//    _vec *= q;
//    _vec *= qMinusOne;
//}

//wydaje się działać
//sprawdzone na chłopski rozum rysując układ współrzędnych
void Quaternion::Rotate(float angle, const Vector & axis)
{
    Quaternion q = Quaternion(Vector(axis.Normalize() * sin(M_PI * angle / 180 / 2)), cos(M_PI * angle / 180 / 2));

    Quaternion qMinusOne = Quaternion(Vector((axis.Normalize() * sin(M_PI * angle / 180 / 2)) * -1), cos(M_PI * angle / 180 / 2));

    *this = q * *this * qMinusOne;
}

std::string Quaternion::ToString() const {
    std::stringstream ss;

    ss << _vec.ToString() << " " << "Real: " << _real;

    return ss.str();
}

