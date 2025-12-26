#include "rhombus.h"

#include <stdexcept>

Rhombus::Rhombus() : d1(1), d2(1), center({0,0}) {}

Rhombus::Rhombus(double _d1, double _d2, Point c) : d1(_d1), d2(_d2), center(c) {
    if (d1 <= 0 || d2 <= 0)
        throw std::invalid_argument("Rhombus diagonals must be positive.");
}

Rhombus::Rhombus(const Rhombus& other)
    : d1(other.d1), d2(other.d2), center(other.center) {}

Rhombus::Rhombus(Rhombus&& other) noexcept
    : d1(std::move(other.d1)),
      d2(std::move(other.d2)),
      center(std::move(other.center)) {}

Rhombus& Rhombus::operator=(const Rhombus& other) {
    if (this != &other) {
        d1 = other.d1;
        d2 = other.d2;
        center = other.center;
    }
    return *this;
}

Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
    if (this != &other) {
        d1 = std::move(other.d1);
        d2 = std::move(other.d2);
        center = std::move(other.center);
    }
    return *this;
}

bool Rhombus::operator==(const Figure& other) const {
    const Rhombus* o = dynamic_cast<const Rhombus*>(&other);
    
    if (!o) 
        return false;

    return (d1 == o->d1 && d2 == o->d2 && center == o->center);
}

Point Rhombus::Center() const {
    return center;
}

Rhombus::operator double() const {
    return (d1 * d2) / 2.0;
}

void Rhombus::Print(std::ostream& os) const {
    os << "Rhombus[d1=" << d1 
       << ", d2=" << d2
       << ", center=(" << center.first 
       << "," << center.second 
       << ")]";
}

void Rhombus::Read(std::istream& is) {
    is >> d1 >> d2 >> center.first >> center.second;
    if (d1 <= 0 || d2 <= 0)
        throw std::invalid_argument("Rhombus diagonals cannot be negative.");
}
