#pragma once

#include <iostream>
#include <utility>

// === Абстрактный базовый класс ===
class Figure {
public:
    virtual ~Figure() noexcept = default;

    // Геометрический центр
    virtual std::pair<double, double> Center() const = 0;

    // Площадь (через оператор приведения к double)
    virtual operator double() const = 0;

    // Ввод / вывод
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        fig.Print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        fig.Read(is);
        return is;
    }

    virtual bool operator==(const Figure& other) const = 0;

protected:
    virtual void Print(std::ostream& os) const = 0;
    virtual void Read(std::istream& is) = 0;
};
