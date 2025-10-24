#pragma once

#include "figure.h"

class Rhombus : public Figure {
public:
    Rhombus();
    Rhombus(double d1, double d2, Point center = {0.0, 0.0});
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;

    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
    bool operator==(const Figure& other) const override;

    Point Center() const override;
    operator double() const override;

protected:
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;

private:
    double d1, d2;
    Point center;
};
