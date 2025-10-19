#pragma once

#include <iostream>

class Figure {
public:

    // Эти конструкции создают безопасный и выразительный интерфейс:
    //     = 0 - "Наследники, реализуйте это сами!"
    //     const - "Я обещаю не менять объект"
    //     = default - "Компилятор, сгенерируй стандартное поведение"
    //     virtual - "Это поведение может меняться в наследниках"

    virtual ~Figure() noexcept = default;
    virtual std::pair<double, double> Center() const = 0;
    virtual operator double() const = 0;

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
