#include <iostream>
#include "five.h"

int main() {
    std::cout << "=== Class Five ===\n";

    Five a("243");
    Five b("32");
    Five c{4, 3, 2, 1};

    std::cout << "a = "; a.print(std::cout) << "\n";
    std::cout << "b = "; b.print(std::cout) << "\n";
    std::cout << "c = "; c.print(std::cout) << "\n";


    Five sum = a.add(b);
    std::cout << "a + b = "; sum.print(std::cout) << "\n";

    Five diff = a.subtract(b);
    std::cout << "a - b = "; diff.print(std::cout) << "\n";

    std::cout << "a > b ? " << (a.greater(b) ? "YES" : "NO") << "\n";
    std::cout << "a < c ? " << (a.less(c) ? "YES" : "NO") << "\n";
    std::cout << "a == b ? " << (a.equals(b) ? "YES" : "NO") << "\n";
    std::cout << "a == a ? " << (a.equals(a) ? "YES" : "NO") << "\n";

    return 0;
}
