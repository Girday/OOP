#pragma once

#include "figure.h"
#include <vector>
#include <memory>

class Array {
public:
    Array();
    void Add(std::unique_ptr<Figure> fig);
    void Remove(size_t index);
    void PrintAll() const;
    double TotalArea() const;
    void PrintCenters() const;
    size_t Size() const;

private:
    std::unique_ptr<std::unique_ptr<Figure>[]> data;
    size_t size;
    size_t capacity;
    void resize();
};
