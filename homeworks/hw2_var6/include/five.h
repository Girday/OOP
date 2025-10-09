#pragma once

#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Five {
public:
    // === КОНСТРУКТОРЫ ===
    Five();                                                     // по умолчанию
    Five(const std::string& base5Number);                       // из строки (например "4312")
    Five(const std::initializer_list<unsigned char>& digits);   // из списка цифр
    Five(const Five& other);                                    // копирующий
    Five(Five&& other) noexcept;                                // перемещающий

    // === ОПЕРАЦИИ ===
    Five add(const Five& other) const;                // сложение
    Five subtract(const Five& other) const;           // вычитание
    bool equals(const Five& other) const;             // ==
    bool greater(const Five& other) const;            // >
    bool less(const Five& other) const;               // <

    // === ВЫВОД ===
    std::ostream& print(std::ostream& os) const;

    // === ДЕСТРУКТОР ===
    virtual ~Five() noexcept;

private:
    size_t size;              // количество цифр
    unsigned char* digits;    // динамический массив (младший разряд — digits[0])

    // === ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ===
    static Five fromDecimal(unsigned long long value); // из десятичного числа
    unsigned long long toDecimal() const;              // в десятичное число
};
