#include "five.h"

// === КОНСТРУКТОРЫ ===

Five::Five() : size(1), digits(new unsigned char[1]{0}) {}  // по умолчанию

Five::Five(const std::string& base5Number) { // из строки
    for (char c : base5Number)
        if (c < '0' || c > '4')
            throw std::invalid_argument("Digits are only from 0 to 4");

    size = base5Number.size();
    digits = new unsigned char[size];

    for (size_t i = 0; i < size; ++i)
        digits[i] = base5Number[size - i - 1] - '0';
}

Five::Five(const std::initializer_list<unsigned char>& list) { // из списка цифр
    size = list.size();
    digits = new unsigned char[size];
    size_t i = 0;
    
    for (auto value : list) {
        if (value > 4) 
            throw std::invalid_argument("Digits are only from 0 to 4");
        
        digits[i++] = value;
    }
}

Five::Five(const Five& other) : size(other.size) { // копирующий
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) 
        digits[i] = other.digits[i];
}

Five::Five(Five&& other) noexcept : size(other.size), digits(other.digits) { // перемещающий
    other.size = 0;
    other.digits = nullptr;
}

// === ОПЕРАТОРЫ ПРИСВАИВАНИЯ ===

Five& Five::operator=(const Five& other) { // копирующий
    if (this != &other) {
        delete[] digits;
        
        size = other.size;
        digits = new unsigned char[size];
        
        for (size_t i = 0; i < size; ++i)
            digits[i] = other.digits[i];
    }

    return *this;
}

Five& Five::operator=(Five&& other) noexcept { // перемещающий
    if (this != &other) {
        delete[] digits;
        
        size = other.size;
        digits = other.digits;
        
        other.size = 0;
        other.digits = nullptr;
    }

    return *this;
}

// === АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ===

Five Five::add(const Five& other) const {
    size_t maxSize = std::max(size, other.size);
    unsigned char carry = 0;

    Five res;
    res.size = maxSize + 1;
    res.digits = new unsigned char[res.size]{0};

    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char a = (i < size) ? digits[i] : 0;
        unsigned char b = (i < other.size) ? other.digits[i] : 0;
        unsigned char sum = a + b + carry;

        res.digits[i] = sum % 5;
        carry = sum / 5;
    }

    res.digits[maxSize] = carry;

    res.normalize();
    return res;
}


Five Five::subtract(const Five& other) const {
    if (less(other))
        throw std::invalid_argument("Res is less than 0");

    Five res;
    res.size = size;
    res.digits = new unsigned char[res.size];

    int borrow = 0;
    for (size_t i = 0; i < size; ++i) {
        int a = digits[i] - borrow;
        int b = (i < other.size) ? other.digits[i] : 0;

        if (a < b) {
            a += 5;
            borrow = 1;
        } else
            borrow = 0;

        res.digits[i] = static_cast<unsigned char>(a - b);
    }

    res.normalize();
    return res;
}

// === СРАВНЕНИЯ ===

bool Five::equals(const Five& other) const {
    if (size != other.size) 
        return false;

    for (size_t i = 0; i < size; ++i)
        if (digits[i] != other.digits[i]) 
            return false;

    return true;
}

bool Five::greater(const Five& other) const {
    if (size != other.size) 
        return size > other.size;
    
    for (size_t i = size; i-- > 0; )
        if (digits[i] != other.digits[i])
            return digits[i] > other.digits[i];
    
    return false;
}

bool Five::less(const Five& other) const {
    if (size != other.size) 
        return size < other.size;
    
    for (size_t i = size; i-- > 0; )
        if (digits[i] != other.digits[i])
            return digits[i] < other.digits[i];
    
    return false;
}

// === НОРМАЛИЗАЦИЯ ===

void Five::normalize() {
    if (size == 0) {
        delete[] digits;
        size = 1;
        digits = new unsigned char[1];
        digits[0] = 0;

        return;
    }

    size_t newSize = size;
    while (newSize > 1 && digits[newSize - 1] == 0) 
        --newSize;

    if (newSize != size) {
        unsigned char* newDigits = new unsigned char[newSize];
        
        for (size_t i = 0; i < newSize; ++i) 
            newDigits[i] = digits[i];
        
        delete[] digits;
        digits = newDigits;
        size = newSize;
    }
}

// === ВЫВОД ===

std::ostream& Five::print(std::ostream& os) const {
    for (size_t i = size; i-- > 0;)
        os << static_cast<int>(digits[i]);
    
    return os;
}

// === ДЕСТРУКТОР ===

Five::~Five() noexcept {
    delete[] digits;
    digits = nullptr;
    size = 0;
}
