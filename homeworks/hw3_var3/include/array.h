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
    // УМНЫЕ УКАЗАТЕЛИ: автоматическое управление памятью
    // shared_ptr автоматически удаляет объекты, когда они больше не нужны
    // Это предотвращает утечки памяти и делает код безопаснее
    std::vector<std::shared_ptr<Figure>> data;
};
