#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

void Zadanie1();
void Zadanie2();
void Zadanie3();

int main() {
    Zadanie3();

    return 0;
}

void Zadanie1()
{
    Vector v(1, 2, 3);
    Vector v2(3, 2, 1);

    std::cout << v.ToString() << "\n" << v2.ToString() << "\nCzy przemiennosc dodawania dziala?" << std::endl;

    std::cout << ((v + v2) == (v2 + v) ? "Tak" : "Nie") << std::endl;

    std::cout << "--------------------------------" << std::endl;

    v = {0, 3, 0};
    v2 = {5, 5, 0};

    std::cout << "Kat miedzy " << v.ToString() << " oraz " << v2.ToString() << " jest rowny ";
    std::cout << v.AngleBetween(v2) << " stopni" << std::endl;

    std::cout << "--------------------------------" << std::endl;

    v = {4, 5, 1};
    v2 = {4, 1, 3};

    Vector v_1 = v.CrossProduct(v2);
    //jeśli iloczyn skalarny(dot product) = 0 to wektory prostopadłe

    std::cout << "Czy " << v_1.ToString() << " jest prostopadly do " << v.ToString() <<
              " oraz " << v2.ToString() << std::endl;

    std::cout << (v.DotProduct(v_1) == 0 ? "Tak" : "Nie") << std::endl;

    std::cout << "--------------------------------" << std::endl;

    std::cout << "Znormalizowany wektor ma postac: " << v_1.Normalize().ToString() << std::endl;
}

void Zadanie2() {
    float tab[16] = {1, 2, 0, -3,
                     3, -4, 1, 0,
                     1, 2, 3, 0,
                     1, 4, 2, 3};

    float tab2[16] = {0, 1, 2, 3,
                      4, 5, 6, 7,
                      8, 9, 10, 11,
                      12, 13, 14, 15};

    float tab3[16] = {1, 1, 1, 1,
                      1, 1, 1, 1,
                      1, 1, 1, 1,
                      1, 1, 1, 1};

    float tab4[16] = {1, 2, 3, 4,
                      2, 3, 1, 2,
                      1, 1, 1, -1,
                      1, 0, -2, -6};

    Matrix m1(tab);
    Matrix m2(tab2);
    Matrix m3(tab3);
    Matrix m4(tab4);

    std::cout << "Dodanie dwoch macierzy:\n" << (m1 + m3).ToString() << std::endl;
    std::cout << "Odjecie dwoch macierzy:\n" << (m1 - m3).ToString() << std::endl;
    std::cout << "Pomnozenie dwoch macierzy:\n" << (m1 * m3).ToString() << std::endl;
    std::cout << "Pomnozenie macierzy przez skalar: \n" << (m3 * 3).ToString() << std::endl;
    std::cout << "Macierz jednostkowa: \n" << Matrix::Indentity().ToString() << std::endl;

    m4.Inverse();
    std::cout << "Odwrocona macierz: \n" << m4.ToString() << std::endl;

    m1.Translate(Vector(0, 3, 3));
    std::cout << "Macierz po translacji: \n" << m1.ToString() << std::endl;

    m1.SetScale(2);
    std::cout << "Macierz po ustawieniu skali: \n" << m1.ToString() << std::endl;

    m1.SetScale(Vector(1, 2, 3));
    std::cout << "Macierz po ustawieniu skali: \n" << m1.ToString() << std::endl;

    m1.RotX(45);
    std::cout << "Macierz po zrotowaniu w x: \n" << m1.ToString() << std::endl;

    m1.RotY(45);
    std::cout << "Macierz po zrotowaniu w y: \n" << m1.ToString() << std::endl;

    m1.RotZ(45);
    std::cout << "Macierz po zrotowaniu w z: \n" << m1.ToString() << std::endl;

    m1.Rotate(45, Vector(1, 2, 3));
    std::cout << "Macierz po zrotowaniu wzdluz osi: \n" << m1.ToString() << std::endl;

    float newTab[16] = {1, 0, 0, 1,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1};

    Matrix rot(newTab);
    rot.RotY(90);

    std::cout << "Zrotowana macierz: \n" << rot.ToString() << std::endl;

    std::cout << "Czy dziala przemiennosc mnozenia macierzy? \n" << std::endl;

    if ((m1 * m2) == (m2 * m1))
        std::cout << "Tak" << std::endl;
    else
        std::cout << "Nie" << std::endl;
}

void Zadanie3()
{
    Quaternion q1(Vector(1, 2, 3), 2);
    Quaternion q2(Vector(4, 6, 8), 3);
    Quaternion q3(Vector(-1, -1, -1), 0);

    std::cout << "Dodawanie quaternionow: " << (q1 + q2).ToString() << std::endl;
    std::cout << "Odejmowanie quaternionow: " << (q1 - q2).ToString() << std::endl;
    std::cout << "Mnozenie quaternionow: " << (q1 * q2).ToString() << std::endl;
    std::cout << "Dzielenie quaternionow: " << (q1 / q2).ToString() << std::endl;

    q3.Rotate(270, {1,0,0});

    std::cout << "Obrot wektora wzdluz osi x: " << q3.ToString() << std::endl;

    std::cout << "Czy przemiennosc mnozenia quaternionow dziala? " << std::endl;

    if((q1 * q2) == (q2 * q1))
        std::cout << "Tak";
    else
        std::cout << "Nie";
}
