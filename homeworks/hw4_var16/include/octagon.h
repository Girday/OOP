#pragma once 

#include "point.h"
#include "figure.h"
#include <memory>
#include <array>
#include <cmath>
#include <numbers>

template <Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon() {
        for (auto& point : points)
            point = std::make_unique<Point<T>>();
    }

    Octagon(const Point<T>& center, T radius) {
        calculatePoints(center, radius);
    }

    Point<T> center() const override {
        T sumX = 0;
        T sumY = 0;
        for (const auto& point : points) {
            sumX += point->x();
            sumY += point->y();
        }
        return Point<T>(sumX / 8, sumY / 8);
    }

    operator double() const override {
        T side = std::hypot(points[1]->x() - points[0]->x(),
                            points[1]->y() - points[0]->y());
        return static_cast<double>(2 * (1 + std::sqrt(2)) * side * side);
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* otherOctagon = dynamic_cast<const Octagon<T>*>(&other);
        
        if (!otherOctagon)
            return false;

        for (size_t i = 0; i < 8; ++i)
            if (*(points[i]) != *(otherOctagon->points[i]))
                return false;
        
        return true;
    }

protected:
    void print(std::ostream& os) const override {
        os << "Octagon: ";
        for (const auto& point : points)
            os << *point << " ";
    }

    void read(std::istream& is) override {
        Point<T> center;
        T radius;
        std::cout << "Enter center coordinates and radius: ";
        is >> center >> radius;
        calculatePoints(center, radius);
    }

    void calculatePoints(const Point<T>& center, T radius) {
        if (radius < 0) {
            std::cout << "Radius must be positive. Multiplying by -1.\n";
            radius = -radius;
        } else if (radius == 0) {
            std::cout << "Radius cannot be zero. Setting to 1.\n";
            radius = 1;
        }

        for (int i = 0; i < 8; ++i) {
            T angle = static_cast<T>(std::numbers::pi_v<T> / 4.0 * i);
            T x = center.x() + radius * std::cos(angle);
            T y = center.y() + radius * std::sin(angle);
            points[i] = std::make_unique<Point<T>>(x, y);
        }
    }

private:
    std::array<std::unique_ptr<Point<T>>, 8> points;
};
