#ifndef LINE_H
#define LINE_H

#include "Vector.h"
#include <string>
#include <sstream>

class Line {
public:
    Vector p;  // Punkt na prostej
    Vector v;  // Wektor kierunkowy

    // Konstruktor domyślny
    Line() {}

    // Konstruktor kopiujący
    Line(const Line& l) : p(l.p), v(l.v) {}

    // Konstruktor z punktem i wektorem kierunkowym
    Line(const Vector& p, const Vector& v) : p(p), v(v) {}

    // Metoda tworząca prostą na podstawie dwóch punktów
    static Line StartToEnd(const Vector& s, const Vector& e) {
        return Line(s, e - s);
    }

    // Metoda konwertująca reprezentację prostej na łańcuch znaków
    std::string ToString() const {
        std::stringstream ss;
        ss << "P = " << p.ToString() << " + " << v.ToString() << " * t";
        return ss.str();
    }


};

#endif