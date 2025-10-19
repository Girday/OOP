#pragma once

#include "figure.h"
#include <utility>

class Rhombus : public Figure {
public:
    Rhombus();
    Rhombus(double d1, double d2, std::pair<double, double> center = {0.0, 0.0});
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;

    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;
    bool operator==(const Figure& other) const override;

    std::pair<double, double> Center() const override;
    operator double() const override;

protected:
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;

private:
    double d1, d2;
    std::pair<double, double> center;
};
