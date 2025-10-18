#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "array.h"

#include <iostream>
#include <memory>

int main() {
    Array figures;
    int choice;

    while (true) {
        std::cout << "\n1. Add Rectangle\n2. Add Trapezoid\n3. Add Rhombus\n"
                     "4. Print All\n5. Print Centers\n6. Total Area\n"
                     "7. Remove Figure\n0. Exit\n> ";
        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            auto rect = std::make_shared<Rectangle>();
            std::cout << "Enter x1 y1 x2 y2: ";
            std::cin >> *rect;
            figures.Add(rect);
        } 
        else if (choice == 2) {
            auto trap = std::make_shared<Trapezoid>();
            std::cout << "Enter 4 points (x y): ";
            std::cin >> *trap;
            figures.Add(trap);
        } 
        else if (choice == 3) {
            auto rh = std::make_shared<Rhombus>();
            std::cout << "Enter d1 d2 centerX centerY: ";
            std::cin >> *rh;
            figures.Add(rh);
        } 
        else if (choice == 4) {
            figures.PrintAll();
        } 
        else if (choice == 5) {
            figures.PrintCenters();
        } 
        else if (choice == 6) {
            std::cout << "Total area: " << figures.TotalArea() << "\n";
        } 
        else if (choice == 7) {
            size_t idx;
            std::cout << "Index to remove: ";
            std::cin >> idx;
            try {
                figures.Remove(idx);
            } catch (const std::exception& e) {
                std::cerr << e.what() << "\n";
            }
        }
    }

    return 0;
}
