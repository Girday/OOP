#include "array.h"

#include <iostream>
#include <stdexcept>

Array::Array() : size(0), capacity(4) {
    data = std::make_unique<std::unique_ptr<Figure>[]>(capacity);
}

void Array::Add(std::unique_ptr<Figure> fig) {
    if (size >= capacity) 
        resize();
    
    data[size++] = std::move(fig);
    std::cout << "Figure added. Total figures: " << size << "\n";
}

void Array::Remove(size_t index) {
    if (index >= size) 
        throw std::out_of_range("Invalid index");
    
    data[index].reset();
    
    for (size_t i = index; i < size - 1; ++i)
        data[i] = std::move(data[i + 1]);
    
    data[--size].reset();
    std::cout << "Figure removed. Total figures: " << size << "\n";
}

void Array::PrintAll() const {
    if (size == 0) {
        std::cout << "No figures to display.\n";
        return;
    }

    for (size_t i = 0; i < size; ++i)
        std::cout << i << ": " << *data[i]
                  << " | Area = " << static_cast<double>(*data[i]) << "\n";
}

void Array::PrintCenters() const {
    if (size == 0) {
        std::cout << "No figures to display their centers.\n";
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        auto c = data[i]->Center();
        std::cout << i << ": Center = (" << c.first << ", " << c.second << ")\n";
    }
}

double Array::TotalArea() const {
    double total = 0;
    
    for (size_t i = 0; i < size; ++i)
        total += static_cast<double>(*data[i]);

    return total;
}

size_t Array::Size() const {
    return size;
}

void Array::resize() {
    capacity *= 2;
    auto newData = std::make_unique<std::unique_ptr<Figure>[]>(capacity);
    
    for (size_t i = 0; i < size; ++i)
        newData[i] = std::move(data[i]);
    
    data = std::move(newData);
}
