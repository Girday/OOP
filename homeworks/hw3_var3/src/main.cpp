#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "array.h"

#include <iostream>

int main() {
    Array figures;
    int choice;

    while (true) {
        std::cout << "\n1. Add Rectangle"
                     "\n2. Add Trapezoid"
                     "\n3. Add Rhombus"
                     "\n4. Print All"
                     "\n5. Print Centers"
                     "\n6. Total Area"
                     "\n7. Remove Figure"
                     "\n0. Exit"
                     "\n-> ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 0:
                return 0;
            
            case 1: {
                // СОЗДАНИЕ УМНОГО УКАЗАТЕЛЯ: make_shared создаёт объект и оборачивает его
                // в shared_ptr для автоматического управления памятью
                auto rect = std::make_shared<Rectangle>();
                std::cout << "Enter x1 y1 x2 y2: ";
                std::cin >> *rect;
                figures.Add(rect);
                // НЕТ delete! Объект удалится автоматически, когда больше не будет нужен
                break;
            }

            case 2: {
                auto trap = std::make_shared<Trapezoid>();
                std::cout << "Enter topBase bottomBase height centerX centerY: ";
                std::cin >> *trap;
                figures.Add(trap);
                break;
            }

            case 3: {
                auto rh = std::make_shared<Rhombus>();
                std::cout << "Enter d1 d2 centerX centerY: ";
                std::cin >> *rh;
                figures.Add(rh);
                break;
            }

            case 4: {
                figures.PrintAll();
                break;
            }

            case 5: {
                figures.PrintCenters();
                break;
            }

            case 6: {
                std::cout << "Total area: " << figures.TotalArea() << "\n";
                break;
            }

            case 7: {
                size_t idx;
                std::cout << "Index to remove: ";
                std::cin >> idx;
                try {
                    figures.Remove(idx);
                } catch (const std::exception& e) {
                    std::cerr << e.what() << "\n";
                }
                break;
            }
            
            default: {
                std::cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }

    return 0;
}
