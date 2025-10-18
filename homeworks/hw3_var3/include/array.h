#pragma once

#include "figure.h"
#include <vector>
#include <memory>

class Array {
public:
    void Add(std::shared_ptr<Figure> fig);
    void Remove(size_t index);
    void PrintAll() const;
    double TotalArea() const;
    void PrintCenters() const;

private:
    std::vector<std::shared_ptr<Figure>> data;
};
