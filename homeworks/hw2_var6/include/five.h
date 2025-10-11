#pragma once

#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Five {
public:
    // === КОНСТРУКТОРЫ ===
    Five();
    Five(const std::string& base5Number);
    Five(const std::initializer_list<unsigned char>& digits);
    Five(const Five& other);        // копирующий
    Five(Five&& other) noexcept;    // перемещающий

    // === ОПЕРАТОРЫ ПРИСВАИВАНИЯ ===
    Five& operator=(const Five& other);        // копирующий
    Five& operator=(Five&& other) noexcept;    // перемещающий

    // === ОПЕРАЦИИ ===
    Five add(const Five& other) const;
    Five subtract(const Five& other) const;
    bool equals(const Five& other) const;
    bool greater(const Five& other) const;
    bool less(const Five& other) const;

    // === ВЫВОД ===
    std::ostream& print(std::ostream& os) const;
    
    // === ДЕСТРУКТОР ===
    virtual ~Five() noexcept;

private:
    size_t size;
    unsigned char* digits{nullptr};

    void normalize(); 
};