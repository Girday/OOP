#include "trapezoid.h"
#include <cmath>
#include <stdexcept>

Trapezoid::Trapezoid() : topBase(0), bottomBase(0), height(0), center({0,0}) {}

Trapezoid::Trapezoid(double top, double bottom, double h, std::pair<double,double> c)
    : topBase(top), bottomBase(bottom), height(h), center(c) {
    if (topBase < 0 || bottomBase < 0 || height < 0)
        throw std::invalid_argument("Trapezoid parameters cannot be negative");
}

Trapezoid::Trapezoid(const Trapezoid& other)
    : topBase(other.topBase), bottomBase(other.bottomBase), 
      height(other.height), center(other.center) {}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept
    : topBase(std::move(other.topBase)), bottomBase(std::move(other.bottomBase)),
      height(std::move(other.height)), center(std::move(other.center)) {}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        topBase = other.topBase;
        bottomBase = other.bottomBase;
        height = other.height;
        center = other.center;
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        topBase = std::move(other.topBase);
        bottomBase = std::move(other.bottomBase);
        height = std::move(other.height);
        center = std::move(other.center);
    }
    return *this;
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* o = dynamic_cast<const Trapezoid*>(&other);
    
    if (!o) 
        return false;
    
    return (topBase == o->topBase && bottomBase == o->bottomBase && 
            height == o->height && center == o->center);
}

std::pair<double,double> Trapezoid::Center() const {
    return center;
}

Trapezoid::operator double() const {
    return (topBase + bottomBase) * height / 2.0;
}

void Trapezoid::Print(std::ostream& os) const {
    os << "Trapezoid[top=" << topBase 
       << ", bottom=" << bottomBase
       << ", height=" << height
       << ", center=(" << center.first << "," << center.second << ")]";
}

void Trapezoid::Read(std::istream& is) {
    is >> topBase >> bottomBase >> height >> center.first >> center.second;
    if (topBase < 0 || bottomBase < 0 || height < 0)
        throw std::invalid_argument("Trapezoid parameters cannot be negative");
}