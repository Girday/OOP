#pragma once

#include "figure.h"

class Trapezoid : public Figure {
public:
    Trapezoid();
    Trapezoid(double top, double bottom, double h, Point center = {0.0, 0.0});
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    bool operator==(const Figure& other) const override;
    Point Center() const override;
    operator double() const override;

protected:
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;

private:
    double topBase, bottomBase, height;
    Point center;
};