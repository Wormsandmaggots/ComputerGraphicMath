//
// Created by 48782 on 06.10.2023.
//

#ifndef AMATEMATYKAGRAFIKI_MATRIX_H
#define AMATEMATYKAGRAFIKI_MATRIX_H

#include "Vector.h"

#define SIZE 16

class Matrix {
public:
    explicit Matrix(const float values[SIZE]);
    Matrix(const Matrix&);
    virtual ~Matrix() = default;

    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(const float&) const;
    Matrix operator*(const Matrix&) const;
    Matrix& operator=(const Matrix&);
    float operator[](int i) const;
    bool operator==(const Matrix&) const;

    std::string ToString() const;

    static Matrix Indentity();
    //inverse should work like an operator
    void Inverse(const Matrix&);
    void Inverse();
    void Transponse();
    void Translate(const Vector&);
    void SetScale(const Vector&);
    void SetScale(const float&);
    void RotX(const float&);
    void RotY(const float&);
    void RotZ(const float&);
    void Rotate(const float&, const Vector&);
    Vector RotateVecInY(Vector&, float angle) const;

private:
    float _data[SIZE] = {0};
};


#endif //AMATEMATYKAGRAFIKI_MATRIX_H
