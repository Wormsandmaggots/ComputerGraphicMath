#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include <fstream>

void Zadanie1();
void Zadanie2();
void Zadanie3();

int main() {
    Zadanie2();

    return 0;
}

void Zadanie1()
{
    Vector v(1, 2, 3);
    Vector v2(3, 2, 1);

    std::ofstream outFile("output.txt");

    auto log = [&outFile](const std::string& message) {
        std::cout << message;
        outFile << message;
    };

    log(v.ToString() + "\n" + v2.ToString() + "\nCzy przemiennosc dodawania dziala?\n");
    log(std::string((v + v2) == (v2 + v) ? "Tak" : "Nie") + "\n");
    log("--------------------------------\n");

    v = {0, 3, 0};
    v2 = {5, 5, 0};

    log("Kat miedzy " + v.ToString() + " oraz " + v2.ToString() + " jest rowny ");
    log(std::to_string(v.AngleBetween(v2)) + " stopni\n");

    log("--------------------------------\n");

    v = {4, 5, 1};
    v2 = {4, 1, 3};

    Vector v_1 = v.CrossProduct(v2);

    log("Czy " + v_1.ToString() + " jest prostopadly do " + v.ToString() + " oraz " + v2.ToString() + "\n");
    log(std::string(v.DotProduct(v_1) == 0 ? "Tak" : "Nie") + "\n");

    log("--------------------------------\n");
    log("Znormalizowany wektor ma postac: " + v_1.Normalize().ToString() + "\n");

    outFile.close();
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
    Matrix m12(tab);
    Matrix m13(tab);
    Matrix m2(tab2);
    Matrix m3(tab3);
    Matrix m4(tab4);

    std::ofstream out("output.txt");  // Utwórz i otwórz strumień plikowy

    // Zapisz do pliku zamiast wyświetlać na terminalu
    out << "Dodanie dwoch macierzy:\n" << (m1 + m3).ToString() << std::endl;
    out << "Odjecie dwoch macierzy:\n" << (m1 - m3).ToString() << std::endl;
    out << "Pomnozenie dwoch macierzy:\n" << (m1 * m3).ToString() << std::endl;
    out << "Pomnozenie macierzy przez skalar: \n" << (m3 * 3).ToString() << std::endl;
    out << "Macierz jednostkowa: \n" << Matrix::Indentity().ToString() << std::endl;

    m4.Inverse();
    out << "Odwrocona macierz: \n" << m4.ToString() << std::endl;

    m1.Translate(Vector(0, 3, 3));
    out << "Macierz po translacji: \n" << m1.ToString() << std::endl;

    m1.SetScale(2);
    out << "Macierz po ustawieniu skali: \n" << m1.ToString() << std::endl;

    m1.SetScale(Vector(1, 2, 3));
    out << "Macierz po ustawieniu skali: \n" << m1.ToString() << std::endl;

    m1.RotX(45);
    out << "Macierz po zrotowaniu w x: \n" << m1.ToString() << std::endl;

    m12.RotY(45);
    out << "Macierz po zrotowaniu w y: \n" << m12.ToString() << std::endl;

    m13.RotZ(45);
    out << "Macierz po zrotowaniu w z: \n" << m13.ToString() << std::endl;

    m1.Rotate(45, Vector(1, 2, 3));
    out << "Macierz po zrotowaniu wzdluz osi: \n" << m1.ToString() << std::endl;

    float newTab[16] = {1, 0, 0, 1,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1};

    Matrix rot(newTab);
    rot.RotY(90);
//    out << "Zrotowana macierz: \n" << rot.ToString() << std::endl;

//    Quaternion q(1,0,0,1);
//    q.Rotate(90, Vector(0,1,0));
//
//    out << q.ToString() << "\n\n";

    Vector v(1,0,0);

    out << "wektor zrotowany o 90 stopni w y:" << rot.RotateVecInY(v, 90).ToString() << "\n\n";

    out << "Czy dziala przemiennosc mnozenia macierzy? \n";
    if ((m1 * m2) == (m2 * m1))
        out << "Tak" << std::endl;
    else
        out << "Nie" << std::endl;

    out.close();  // Zamknij strumień plikowy
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
