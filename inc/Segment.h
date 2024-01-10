#ifndef SEGMENT_H
#define SEGMENT_H
#include "Vector.h"
#include <string>
#include <sstream>

class Segment {
public:
    Vector s;  // Punkt początkowy odcinka
    Vector e;  // Punkt końcowy odcinka
    Vector v;  // Wektor kierunkowy odcinka

    // Konstruktor domyślny
    Segment() {}

    // Konstruktor kopiujący
    Segment(const Segment& seg) : s(seg.s), e(seg.e), v(seg.v) {}

    // Konstruktor z dwoma punktami
    Segment(const Vector& s, const Vector& e) : s(s), e(e), v((e - s).Normalize()) {}

    // Metoda ToString dla reprezentacji tekstowej odcinka
    std::string ToString() const {
        std::stringstream ss;
        ss << "Segment: Start = " << s.ToString() << ", End = " << e.ToString() << ", Vector = " << v.ToString();
        return ss.str();
    }
};
#endif