#include <iostream>
#include "five.h"

// DEMONSTRATION

int main() {
    std::cout << "\n=== HW2_VAR6: Class Five ===\n";

    // === Конструкторы ===
    std::cout << "\n--- Constructors ---\n";

    Five def;
    std::cout << "Default: ";
    def.print(std::cout) << "\n";

    Five fromStr("00243");
    std::cout << "From string (\"00243\"): ";
    fromStr.print(std::cout) << "\n";

    Five fromList{4, 3, 2, 1};
    std::cout << "From list {4,3,2,1}: ";
    fromList.print(std::cout) << "\n";

    Five copy(fromStr);
    std::cout << "Copy fromStr: ";
    copy.print(std::cout) << "\n";

    Five moved(std::move(copy));
    std::cout << "Moved (copy -> moved): ";
    moved.print(std::cout) << "\n";

    std::cout << "Old copy (after move): ";
    copy.print(std::cout) << "\n";

    // === Операторы ===
    std::cout << "\n--- Math operations ---\n";

    Five a("132");
    Five b("43");

    std::cout << "a = "; a.print(std::cout) << "\n";
    std::cout << "b = "; b.print(std::cout) << "\n";

    Five sum = a.add(b);
    std::cout << "a + b = ";
    sum.print(std::cout) << "\n";

    Five diff = a.subtract(Five("40"));
    std::cout << "a - 40 = ";
    diff.print(std::cout) << "\n";

    // === Сравнение ===
    std::cout << "\n--- Compare ---\n";
    std::cout << "a == b ? " << (a.equals(b) ? "Yes" : "No") << "\n";
    std::cout << "a > b ? " << (a.greater(b) ? "Yes" : "No") << "\n";
    std::cout << "a < b ? " << (a.less(b) ? "Yes" : "No") << "\n";

    // === Исключения ===
    std::cout << "\n--- Exception test ---\n";
    try {
        Five x("10");
        Five y("21");
        std::cout << "x = "; x.print(std::cout);
        std::cout << ", y = "; y.print(std::cout);
        std::cout << "\n";

        Five bad = x.subtract(y);
        std::cout << "Result (no throw): ";
        bad.print(std::cout) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }

    // === Перемещение и присваивание ===
    std::cout << "\n--- Move and assign ---\n";

    Five c("444");
    Five d("11");

    std::cout << "c = "; c.print(std::cout);
    std::cout << ", d = "; d.print(std::cout);
    std::cout << "\n";

    Five e = c.add(d);
    std::cout << "e = c + d = ";
    e.print(std::cout) << "\n";

    Five f;
    f = std::move(e);
    std::cout << "f (after move): ";
    f.print(std::cout) << "\n";

    std::cout << "e (after move): ";
    e.print(std::cout) << "\n";

    std::cout << "\n--- End of program ---\n";
    std::cout << "All destructors will be called now.\n";

    std::cout << "\n=== End ===\n\n";

    return 0;
}
