#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>
#include <stdexcept>
#include <sstream>

class Vector4 {
public:
    Vector4() : _x(0), _y(0), _z(0), _w(0) {}
    Vector4(float x, float y, float z, float w = 0.0f) : _x(x), _y(y), _z(z), _w(w) {}
    Vector4(const Vector4& v) : _x(v._x), _y(v._y), _z(v._z), _w(v._w) {}

    std::string ToString() const {
        std::stringstream ss;
        ss << "[" << _x << ", " << _y << ", " << _z << ", " << _w << "]";
        return ss.str();
    }

    Vector4& operator=(const Vector4& v) = default;

    Vector4 operator+(const Vector4& v) const {
        return {_x + v._x, _y + v._y, _z + v._z, _w + v._w};
    }

    Vector4 operator-(const Vector4& v) const {
        return {_x - v._x, _y - v._y, _z - v._z, _w - v._w};
    }

    void operator+=(const Vector4& v) {
        _x += v._x;
        _y += v._y;
        _z += v._z;
        _w += v._w;
    }

    void operator-=(const Vector4& v) {
        _x -= v._x;
        _y -= v._y;
        _z -= v._z;
        _w -= v._w;
    }

    Vector4 operator*(float f) const {
        return {_x * f, _y * f, _z * f, _w * f};
    }

    Vector4 operator/(float f) const {
        if (f != 0.0f) {
            f = 1 / f;
            return {_x * f, _y * f, _z * f, _w * f};
        }
        throw std::logic_error("Math error: Cannot divide by zero\n");
    }

    void operator*=(float f) {
        _x *= f;
        _y *= f;
        _z *= f;
        _w *= f;
    }

    void operator/=(float f) {
        if (f != 0.0f) {
            f = 1 / f;
            _x *= f;
            _y *= f;
            _z *= f;
            _w *= f;
        } else {
            throw std::logic_error("Math error: Cannot divide by zero\n");
        }
    }

    float Length() const {
        return sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
    }

    void Normalize() {
        float len = Length();
        if (len != 0) {
            *this /= len;
        } else {
            throw std::logic_error("Math error: Cannot normalize a zero-length vector\n");
        }
    }

private:
    float _x, _y, _z, _w;
};

#endif // VECTOR4_H
