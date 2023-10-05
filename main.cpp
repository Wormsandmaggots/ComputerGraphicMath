#include <iostream>
#include "Vector.h"

void Zadanie1();

int main() {
    Zadanie1();

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
