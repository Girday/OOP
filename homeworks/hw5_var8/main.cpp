/*
    Вариант 8:
        Однонаправленный список
    
    Стратегия memory_resource 2: 
        Фиксированный блок памяти (выделяется один раз), 
        информация о выделенных блоках памяти хранится в std::vector
*/

#include <iostream>
#include <memory_resource>

#include "FixedBlockResource.h"
#include "ForwardList.h"

struct Person {
    std::string name;
    int age;
};

int main() {
    std::cout << "\n\t| DEMONSTRATION |\n\n";

    FixedBlockResource mem(2048);

    // =============================================================
    // 1. ТЕСТ НА ПРОСТЫХ ТИПАХ (int)
    // =============================================================
    std::cout << "=== ForwardList<int> ===\n";

    ForwardList<int> list(&mem);

    std::cout << "Pushing values 10, 20 and 30...\n";
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::cout << "List contents: ";
    for (int v : list)
        std::cout << v << " ";
    std::cout << "\n\n";

    std::cout << "Manual iteration: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";

    // Тест на повторное использование памяти
    std::cout << "Creating temporary list to test memory reuse...\n";
    {
        ForwardList<int> temp(&mem);
        temp.push_back(111);
        temp.push_back(222);

        std::cout << "Temp list: ";
        for (int x : temp) 
            std::cout << x << " ";
        std::cout << "\n";
    }

    std::cout << "(Temporary list destroyed, its memory is now reusable)\n\n";

    std::cout << "Creating a reused list...\n";
    ForwardList<int> reused(&mem);

    std::cout << "Pushing values 999 and 888...\n";
    reused.push_back(999);
    reused.push_back(888);

    std::cout << "Reused list: ";
    for (int x : reused) 
        std::cout << x << " ";
    std::cout << "\n\n";

    // =============================================================
    // 2. ТЕСТ НА СЛОЖНОМ ТИПЕ (struct)
    // =============================================================
    std::cout << "=== ForwardList<Person> ===\n";

    ForwardList<Person> people(&mem);

    std::cout << "Adding persons...\n";
    people.push_back({"Alice", 30});
    people.push_back({"Bob", 25});
    people.push_back({"Charlie", 40});

    std::cout << "People list:\n";
    for (const auto& p : people)
        std::cout << "  " << p.name << ", age " << p.age << "\n";

    std::cout << "\n";

    return 0;
}
    