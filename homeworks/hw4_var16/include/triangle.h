#pragma once

#include "point.h"
#include "figure.h"
#include <memory>
#include <cmath>

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() : a(std::make_unique<Point<T>>()),
                 b(std::make_unique<Point<T>>()),
                 c(std::make_unique<Point<T>>()) {}

    Triangle(const Point<T>& _a, const Point<T>& _b, const Point<T>& _c)
        : a(std::make_unique<Point<T>>(_a)),
          b(std::make_unique<Point<T>>(_b)),
          c(std::make_unique<Point<T>>(_c)) {}
    
    Point<T> center() const override {
        T centerX = (a->x() + b->x() + c->x()) / 3;
        T centerY = (a->y() + b->y() + c->y()) / 3;
        return Point<T>(centerX, centerY);
    }

    operator double() const override {
        return 0.5 * std::abs(
            (a->x() - c->x()) * (b->y() - a->y()) -
            (a->x() - b->x()) * (c->y() - a->y())
        );
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* otherTriangle = dynamic_cast<const Triangle<T>*>(&other);
        
        if (!otherTriangle)
            return false;

        return (*a == *(otherTriangle->a)) &&
               (*b == *(otherTriangle->b)) &&
               (*c == *(otherTriangle->c));
    }

protected:
    void print(std::ostream& os) const override {
        os << "Triangle: A" << *a << ", B" << *b << ", C" << *c;
    }

    void read(std::istream& is) override {
        is >> *a >> *b >> *c;
    }

private:
    std::unique_ptr<Point<T>> a;
    std::unique_ptr<Point<T>> b;
    std::unique_ptr<Point<T>> c;
};
