#include "rectangle.h"

#include <cmath>
#include <stdexcept>

Rectangle::Rectangle() : x1(0), y1(0), x2(1), y2(1) {}

Rectangle::Rectangle(double _x1, double _y1, double _x2, double _y2)
    : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
    if (x1 == x2 || y1 == y2)
        throw std::invalid_argument("Rectangle sides cannot be zero.");
}

Rectangle::Rectangle(const Rectangle& other)
    : x1(other.x1), y1(other.y1), x2(other.x2), y2(other.y2) {}

Rectangle::Rectangle(Rectangle&& other) noexcept
    : x1(std::move(other.x1)),
      y1(std::move(other.y1)),
      x2(std::move(other.x2)),
      y2(std::move(other.y2)) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        x1 = other.x1;
        y1 = other.y1;
        x2 = other.x2;
        y2 = other.y2;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        x1 = std::move(other.x1);
        y1 = std::move(other.y1);
        x2 = std::move(other.x2);
        y2 = std::move(other.y2);
    }
    return *this;
}

bool Rectangle::operator==(const Figure& other) const {
    const Rectangle* o = dynamic_cast<const Rectangle*>(&other);
    if (!o) 
        return false;
    return (x1 == o->x1 && y1 == o->y1 && x2 == o->x2 && y2 == o->y2);
}

Point Rectangle::Center() const {
    return { (x1 + x2) / 2.0, (y1 + y2) / 2.0 };
}

Rectangle::operator double() const {
    return std::abs((x2 - x1) * (y2 - y1));
}

void Rectangle::Print(std::ostream& os) const {
    os << "Rectangle[(" << x1 
       << "," << y1 
       << "),(" << x2 
       << "," << y2 
       << ")]";
}

void Rectangle::Read(std::istream& is) {
    is >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2 || y1 == y2)
        throw std::invalid_argument("Rectangle sides cannot be zero.");
}
