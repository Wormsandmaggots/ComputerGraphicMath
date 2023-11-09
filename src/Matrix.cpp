//
// Created by 48782 on 06.10.2023.
//

#include "Matrix.h"
#include <cstring>
#include <sstream>
#include <cmath>

float Calculate3x3Det(float arr[9]);
float* GetMatrix3x3From4x4(const Matrix & another, int i, int j);

Matrix::Matrix(const float values[SIZE]) {
    memcpy(_data, values, SIZE * sizeof(float));
}

Matrix::Matrix(const Matrix & cpy) {
    memcpy(_data, cpy._data, SIZE * sizeof(float));
}

Matrix Matrix::operator+(const Matrix & another) const {
    float newTab[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        newTab[i] = _data[i] + another[i];
    }

    return Matrix(newTab);
}

Matrix Matrix::operator-(const Matrix & another) const {
    float newTab[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        newTab[i] = _data[i] - another[i];
    }

    return Matrix(newTab);
}

Matrix Matrix::operator*(const float & val) const {
    float newTab[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        newTab[i] = _data[i] * val;
    }

    return Matrix(newTab);
}

Matrix Matrix::operator*(const Matrix & another) const {
    float newTab[SIZE] = {0};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                newTab[i * 4 + j] += _data[i * 4 + k] * another[k * 4 + j];
            }
        }
    }

    return Matrix{newTab};
}

Matrix Matrix::Indentity() {
    float newTab[16] = {1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,0,0,1};

    return Matrix(newTab);
}

void Matrix::Transponse() {
    float temp;

    for(int i = 0; i < 4; i++)
    {
        for(int j = i; j < 4; j++)
        {
            if(i == j) continue;

            temp = _data[i * 4 + j];
            _data[i * 4 + j] = _data[j * 4 + i];
            _data[j * 4 + i] = temp;
        }
    }
}

std::string Matrix::ToString() const {
    std::stringstream ss;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            ss << _data[i * 4 + j] << " ";
        }

        ss << std::endl;
    }

    return ss.str();
}

bool Matrix::operator==(const Matrix & another) const {

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(_data[i * 4 + j] != another[i * 4 + j])
                return false;
        }
    }

    return true;
}

float Matrix::operator[](int i) const {

    if(i < 0 || i > 15)
        throw std::invalid_argument("Index out of bounds, must be between 0 and 15 included");

    return _data[i];
}

void Matrix::Translate(const Vector & vec) {
    _data[12] = vec.x();
    _data[13] = vec.y();
    _data[14] = vec.z();
}

void Matrix::SetScale(const Vector & scale) {
    _data[0] = scale.x();
    _data[5] = scale.y();
    _data[10] = scale.z();
}

void Matrix::SetScale(const float & scale) {
    _data[0] = scale;
    _data[5] = scale;
    _data[10] = scale;
}

void Matrix::RotX(const float & angle) {
    _data[5] = (float)cos(M_PI * angle / 180);
    _data[6] = (float)sin(M_PI * angle / 180);

    _data[9] = -_data[6];
    _data[10] = _data[5];
}

void Matrix::RotY(const float & angle) {
    _data[0] = (float)cos(M_PI * angle / 180);
    _data[2] = -(float)sin(M_PI * angle / 180);

    _data[8] = -_data[2];
    _data[10] = _data[0];
}

void Matrix::RotZ(const float & angle) {
    _data[0] = (float)cos(M_PI * angle / 180);
    _data[1] = (float)sin(M_PI * angle / 180);

    _data[4] = -_data[1];
    _data[5] = _data[0];
}

void Matrix::Rotate(const float & angle, const Vector & axis) {
    Vector nor = axis.Normalize();

    float sinAngle = (float)sin(M_PI * angle / 180);
    float cosAngle = (float)cos(M_PI * angle / 180);
    float oneMinusCosAngle = 1.f - cosAngle;

    _data[0] = pow(nor.x(), 2) + cosAngle * (1 - pow(nor.x(), 2));
    _data[4] = nor.x() * nor.y() * oneMinusCosAngle - sinAngle * nor.z();
    _data[8] = nor.x() * nor.z() * oneMinusCosAngle + sinAngle * nor.y();

    _data[1] = nor.x() * nor.y() * oneMinusCosAngle + sinAngle * nor.z();
    _data[5] = nor.y() * nor.y() * cosAngle * (1 - nor.y() * nor.y());
    _data[9] = nor.y() * nor.z() * oneMinusCosAngle - sinAngle * nor.x();

    _data[2] = nor.x() * nor.z() * oneMinusCosAngle - sinAngle * nor.y();
    _data[6] = nor.y() * nor.z() * oneMinusCosAngle + sinAngle * nor.x();
    _data[10] = nor.z() * nor.z() + cosAngle * (1 - nor.z() * nor.z());
}

float Calculate3x3Det(float arr[9])
{
    float val1 = arr[0] * (arr[4] * arr[8] - arr[5] * arr[7]);
    float val2 = arr[1] * (arr[3] * arr[8] - arr[5] * arr[6]);
    float val3 = arr[2] * (arr[3] * arr[7] - arr[4] * arr[6]);

    return val1 - val2 + val3;
}

void Matrix::Inverse(const Matrix & another)
{
    float val1 = another[0] * Calculate3x3Det(new float[]{another[5], another[6], another[7],
                                                          another[9], another[10], another[11],
                                                          another[13], another[14], another[15]});

    float val2 = another[1] * Calculate3x3Det(new float[]{another[6], another[7], another[4],
                                                         another[10], another[11], another[8],
                                                         another[14], another[15], another[12]});

    float val3 = another[2] * Calculate3x3Det(new float[]{another[4], another[5], another[7],
                                                          another[8], another[9], another[11],
                                                          another[12], another[13], another[15]});

    float val4 = another[3] * Calculate3x3Det(new float[]{another[4], another[5], another[6],
                                                          another[8], another[9], another[10],
                                                          another[12], another[13], another[14]});

    float det = val1 - val2 + val3 - val4;

    if(det == 0) return;

    float newTab[16] = {0};

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int s = -1;

            if((i + j) % 2 == 0)
                s = 1;

            newTab[i * 4 + j] = (float)s * Calculate3x3Det(GetMatrix3x3From4x4(another, i, j));
        }
    }

    Matrix m(newTab);

    m.Transponse();

    *this = m * (1.f/det);
}

Matrix& Matrix::operator=(const Matrix & another) {

    if(&another != this)
    {
        for(int i = 0; i < SIZE; i++)
        {
            _data[i] = another[i];
        }
    }

    return *this;
}

void Matrix::Inverse() {
    Inverse(*this);
}

Vector Matrix::operator*(const Vector & v) const {

    return Vector(0, 0);
}

float* Matrix::RotateVec(Vector & v, float w) const {
    float result[4] = {0};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            switch (j) {
                case 0:
                {
                    result[i] += _data[i * 4 + j] * v.x();
                    break;
                }
                case 1:
                {
                    result[i] += _data[i * 4 + j] * v.y();
                    break;
                }
                case 2:
                {
                    result[i] += _data[i * 4 + j] * v.z();
                    break;
                }
                case 3:
                {
                    result[i] += _data[i * 4 + j] * w;
                    break;
                }
            }
        }
    }

    return result;
}

float* GetMatrix3x3From4x4(const Matrix & another, int i, int j)
{
    float *arr = new float[9]{0};

    int ctr = 0;

    for(int k = 0; k < 4; k++)
    {
        if(k == i)
            continue;

        for(int l = 0; l < 4; l++)
        {
            if(l == j)
                continue;

            arr[ctr] = another[k * 4 + l];
            ctr++;
        }
    }

    return arr;
}


//void Matrix::Transponse(Matrix & matrix) {
//    float temp;
//
//    for(int i = 0; i < 4; i++)
//    {
//        for(int j = i; j < 4; j++)
//        {
//            if(i == j) continue;
//
//            temp = matrix[i * 4 + j];
//            matrix._data[i * 4 + j] = matrix[j * 4 + i];
//            matrix._data[j * 4 + i] = temp;
//        }
//    }
//}


//void Matrix::Inverse(const Matrix & another) {
//    float t1 = another[0] * another[4];
//    float t2 = another[0] * another[7];
//    float t3 = another[3] * another[1];
//    float t4 = another[6] * another[1];
//    float t5 = another[3] * another[2];
//    float t6 = another[6] * another[2];
//
//    float det = t1 * another[8] - t2 * another[5] -
//            t3 * another[8] + t4 * another[5] + t5 * another[7] -
//            t6 * another[4];
//
//    if(det == 0) return;
//
//    float invd = 1.f/det;
//
//    float m0 = (another[4] * another[8] - another[7] * another[5]) * invd;
//    float m1 = (another[1] * another[8] - another[7] * another[2]) * invd;
//    float m2 = (another[1] * another[5] - another[4] * another[2]) * invd;
//    float m3 = (another[3] * another[8] - another[6] * another[5]) * invd;
//    float m4 = (another[0] * another[8] - t6) * invd;
//    float m5 = (another[4] * another[8] - another[7] * another[5]) * invd;
//    float m6 = (another[4] * another[8] - another[7] * another[5]) * invd;
//    float m7 = (another[4] * another[8] - another[7] * another[5]) * invd;
//    float m8 = (another[4] * another[8] - another[7] * another[5]) * invd;
//
//}
//