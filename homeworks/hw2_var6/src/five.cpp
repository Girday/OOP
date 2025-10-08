#include "five.h"

// === КОНСТРУКТОРЫ ===

Five::Five() : size(0), digits(nullptr) {}

Five::Five(const std::string& base5Number) {
    for (char c : base5Number)
        if (c < '0' || c > '4')
            throw std::invalid_argument("Invalid symbol in base-5 number");

    size = base5Number.size();
    digits = new unsigned char[size];

    for (size_t i = 0; i < size; ++i)
        digits[i] = base5Number[size - i - 1] - '0';
}

Five::Five(const std::initializer_list<unsigned char>& list) {
    size = list.size();
    digits = new unsigned char[size];
    size_t i = 0;
    
    for (auto value : list) {
        if (value > 4) 
            throw std::invalid_argument("Digits are only from 0 to 4");
        
        digits[i++] = value;
    }
}

Five::Five(const Five& other) : size(other.size) {
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) digits[i] = other.digits[i];
}

Five::Five(Five&& other) noexcept : size(other.size), digits(other.digits) {
    other.size = 0;
    other.digits = nullptr;
}

// === АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ===

Five Five::add(const Five& other) const {
    size_t maxSize = std::max(size, other.size);
    unsigned char* result = new unsigned char[maxSize + 1];
    unsigned char carry = 0;

    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char a = (i < size) ? digits[i] : 0;
        unsigned char b = (i < other.size) ? other.digits[i] : 0;
        unsigned char sum = a + b + carry;
        result[i] = sum % 5;
        carry = sum / 5;
    }

    if (carry > 0)
        result[maxSize++] = carry;

    Five res;
    res.size = maxSize;
    res.digits = new unsigned char[maxSize];
    for (size_t i = 0; i < maxSize; ++i) res.digits[i] = result[i];
    delete[] result;

    return res;
}

Five Five::subtract(const Five& other) const {
    if (less(other))
        throw std::invalid_argument("Res is less than 0");

    unsigned char* result = new unsigned char[size];
    int borrow = 0;

    for (size_t i = 0; i < size; ++i) {
        int a = digits[i] - borrow;
        int b = (i < other.size) ? other.digits[i] : 0;

        if (a < b) {
            a += 5;
            borrow = 1;
        } else
            borrow = 0;

        result[i] = a - b;
    }

    size_t newSize = size;
    while (newSize > 1 && result[newSize - 1] == 0) newSize--;

    Five res;
    res.size = newSize;
    res.digits = new unsigned char[newSize];
    for (size_t i = 0; i < newSize; ++i) res.digits[i] = result[i];
    delete[] result;
    
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

// === ВЫВОД ===

std::ostream& Five::print(std::ostream& os) const {
    for (size_t i = size; i-- > 0; )
        os << static_cast<int>(digits[i]);
    
    return os;
}

// === ДЕСТРУКТОР ===

Five::~Five() noexcept {
    delete[] digits;
    digits = nullptr;
    size = 0;
}
