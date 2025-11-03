#pragma once

#include "figure.h"

#include <memory>

template <Scalar T>
class Square : public Figure<T> {
public:
    Square() : bl(std::make_unique<Point<T>>()),
               tr(std::make_unique<Point<T>>()) {}

    Square(const Point<T>& _bl, const Point<T>& _tr)
        : bl(std::make_unique<Point<T>>(_bl)),
          tr(std::make_unique<Point<T>>(_tr)) {}
    
    Point<T> center() const override {
        T centerX = (bl->x() + tr->x()) / 2;
        T centerY = (bl->y() + tr->y()) / 2;
        return Point<T>(centerX, centerY);
    }

    operator double() const override {
        T side = tr->x() - bl->x();
        return static_cast<double>(side * side);
    }

    bool operator==(const Figure<T>& other) const override {
        const auto* otherSquare = dynamic_cast<const Square<T>*>(&other);
        
        if (!otherSquare)
            return false;

        return (*bl == *(otherSquare->bl)) &&
               (*tr == *(otherSquare->tr));
    }

protected:
    void print(std::ostream& os) const override {
        os << "Square: Bottom-Left" << *bl << ", Top-Right" << *tr;
    }

    void read(std::istream& is) override {
        std::cout << "Enter bottom-left and top-right points: ";
        is >> *bl >> *tr;
    }

private:
    std::unique_ptr<Point<T>> bl; // bottom-left
    std::unique_ptr<Point<T>> tr; // top-right
};
