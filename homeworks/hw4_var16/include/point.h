#pragma once

#include <type_traits>
#include <concepts>
#include <iostream>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point {
public:
    T x{}, y{};

    Point() = default;
    Point(T _x, T _y) : x(_x), y(_y) {}
    Point(const Point& other) = default;
    Point(Point&& other) noexcept = default;

    Point& operator=(const Point& other) = default;
    Point& operator=(Point&& other) noexcept = default;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
};
