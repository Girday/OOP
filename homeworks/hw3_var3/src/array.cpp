#include "array.h"

#include <iostream>
#include <stdexcept>

void Array::Add(std::shared_ptr<Figure> fig) {
    data.push_back(std::move(fig));
}

void Array::Remove(size_t index) {
    if (index >= data.size()) throw std::out_of_range("Invalid index");
    data.erase(data.begin() + index);
}

void Array::PrintAll() const {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << i << ": " << *data[i]
                  << " | Area = " << static_cast<double>(*data[i]) << "\n";
    }
}

void Array::PrintCenters() const {
    for (size_t i = 0; i < data.size(); ++i) {
        auto c = data[i]->Center();
        std::cout << i << ": Center = (" << c.first << ", " << c.second << ")\n";
    }
}

double Array::TotalArea() const {
    double total = 0;
    for (auto& f : data)
        total += static_cast<double>(*f);
    return total;
}
