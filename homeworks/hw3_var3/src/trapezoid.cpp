#include "trapezoid.h"

#include <cmath>
#include <stdexcept>

Trapezoid::Trapezoid() {
    for (auto& p : points) 
        p = {0,0};
}

Trapezoid::Trapezoid(const std::array<std::pair<double,double>,4>& pts) : points(pts) {}

Trapezoid::Trapezoid(const Trapezoid& other) : points(other.points) {}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept : points(std::move(other.points)) {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other)
        points = other.points;
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other)
        points = std::move(other.points);
    return *this;
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* o = dynamic_cast<const Trapezoid*>(&other);
    if (!o) return false;
    return points == o->points;
}

std::pair<double,double> Trapezoid::Center() const {
    double cx = 0, cy = 0;
    for (auto& p : points) {
        cx += p.first;
        cy += p.second;
    }
    return {cx / 4.0, cy / 4.0};
}

Trapezoid::operator double() const {
    double area = 0;
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        area += points[i].first * points[j].second;
        area -= points[j].first * points[i].second;
    }
    return std::abs(area) / 2.0;
}

void Trapezoid::Print(std::ostream& os) const {
    os << "Trapezoid[";
    for (int i = 0; i < 4; ++i) {
        os << "(" << points[i].first 
           << "," << points[i].second 
           << ")";
        
        if (i != 3) 
            os << ",";
    }
    os << "]";
}

void Trapezoid::Read(std::istream& is) {
    for (auto& p : points)
        is >> p.first >> p.second;
}
