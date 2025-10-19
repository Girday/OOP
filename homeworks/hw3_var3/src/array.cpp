#include "array.h"

#include <iostream>
#include <stdexcept>

void Array::Add(std::shared_ptr<Figure> fig) {
    data.push_back(std::move(fig));
    std::cout << "Figure added. Total figures: " << data.size() << "\n";
}

void Array::Remove(size_t index) {
    if (index >= data.size()) 
        throw std::out_of_range("Invalid index");
    data.erase(data.begin() + index);
    std::cout << "Figure removed. Total figures: " << data.size() << "\n";
}

void Array::PrintAll() const {
    if (data.empty()) {
        std::cout << "No figures to display.\n";
        return;
    }

    for (size_t i = 0; i < data.size(); ++i)
        std::cout << i << ": " << *data[i]
                  << " | Area = " << static_cast<double>(*data[i]) << "\n";
}

void Array::PrintCenters() const {
    if (data.empty()) {
        std::cout << "No figures to display their centers.\n";
        return;
    }

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
