#pragma once

#include "figure.h"
#include <array>

class Trapezoid : public Figure {
public:
    Trapezoid();
    Trapezoid(const std::array<std::pair<double,double>,4>& pts);
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    bool operator==(const Figure& other) const override;
    std::pair<double,double> Center() const override;
    operator double() const override;

protected:
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;

private:
    std::array<std::pair<double,double>,4> points;
};
