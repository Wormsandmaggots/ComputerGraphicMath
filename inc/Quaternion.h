//
// Created by 48782 on 08.10.2023.
//

#ifndef AMATEMATYKAGRAFIKI_QUATERNION_H
#define AMATEMATYKAGRAFIKI_QUATERNION_H
#include "Vector.h"

class Quaternion {
public:
    Quaternion(const Vector &vec, float real);
    Quaternion(float, float, float, float);
    virtual ~Quaternion() = default;

    Quaternion operator*(const Quaternion&) const;
    Quaternion operator+(const Quaternion&) const;
    Quaternion operator-(const Quaternion&) const;
    Quaternion operator/(const Quaternion&) const;
    Quaternion& operator=(const Quaternion&);
    bool operator==(const Quaternion&) const;

    std::string ToString() const;

    void Rotate(float angle, const Vector&);

private:
    Vector _vec;
    float _real;
};


#endif //AMATEMATYKAGRAFIKI_QUATERNION_H
