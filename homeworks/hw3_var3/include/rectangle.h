#pragma once

#include "figure.h"

class Rectangle : public Figure {
public:
    Rectangle();
    Rectangle(double x1, double y1, double x2, double y2);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
    bool operator==(const Figure& other) const override;

    std::pair<double, double> Center() const override;
    operator double() const override;

protected:
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;

private:
    double x1, y1, x2, y2;
};
