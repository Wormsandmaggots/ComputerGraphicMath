//
// Created by 48782 on 05.10.2023.
//

#ifndef AMATEMATYKAGRAFIKI_VECTOR_H
#define AMATEMATYKAGRAFIKI_VECTOR_H

class Vector {
public:
    Vector(float, float, float = 0.);
    Vector(Vector&);
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

    Vector operator/(const float&) const;
    Vector operator*(const float&) const;
    Vector operator+(const Vector&) const;
    Vector operator-(const Vector&) const;

    Vector& operator=(const Vector&);

    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);
    Vector& operator*=(const float&);
    Vector& operator/=(const float&);

    bool operator==(const Vector&) const;

private:
    float _x, _y, _z;

    void x(const float& x) { _x = x; };
    void y(const float& y) { _y = y; };
    void z(const float& z) { _z = z; };
};


#endif //AMATEMATYKAGRAFIKI_VECTOR_H
