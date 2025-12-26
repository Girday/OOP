#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "array.h"

#include <iostream>
#include <climits>

void ClearInput() {
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

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
            ClearInput();
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 0:
                return 0;
            
            case 1: {
                auto rect = std::make_unique<Rectangle>();
                std::cout << "Enter x1 y1 x2 y2: ";

                try {
                    std::cin >> *rect;
                    figures.Add(std::move(rect));
                } catch (const std::exception& e) {
                    std::cerr << "Error creating rectangle: " << e.what() << "\n";
                    ClearInput();
                }
                break;
            }

            case 2: {
                auto trap = std::make_unique<Trapezoid>();
                std::cout << "Enter topBase bottomBase height centerX centerY: ";

                try {
                    std::cin >> *trap;
                    figures.Add(std::move(trap));
                } catch (const std::exception& e) {
                    std::cerr << "Error creating trapezoid: " << e.what() << "\n";
                    ClearInput();
                }
                break;
            }

            case 3: {
                auto rh = std::make_unique<Rhombus>();
                std::cout << "Enter d1 d2 centerX centerY: ";

                try {
                    std::cin >> *rh;
                    figures.Add(std::move(rh));
                } catch (const std::exception& e) {
                    std::cerr << "Error creating rhombus: " << e.what() << "\n";
                    ClearInput();
                }
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
                if (figures.Size() == 0) {
                    std::cout << "No figures to remove.\n";
                    break;
                }
                
                size_t idx;
                std::cout << "Index to remove: ";
                
                if (!(std::cin >> idx)) {
                    ClearInput();
                    std::cout << "Invalid index. Please enter a valid index: " 
                              << "from 0 to " << (figures.Size() - 1) << ".\n";
                    break;
                }
                
                try {
                    figures.Remove(idx);
                } catch (const std::exception& e) {
                    std::cerr << "Error removing figure: " << e.what() << "\n";
                    std::cerr << "Invalid index. Please enter a valid index: " 
                              << "from 0 to " << (figures.Size() - 1) << ".\n";
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
