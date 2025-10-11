#include <gtest/gtest.h>
#include "../include/gcd.h"
#include <random>
#include <algorithm>

using namespace std;

// --- Настройка генератора случайных чисел ---
mt19937 rng(random_device{}());
uniform_int_distribution<int> dist(-1000000, 1000000); // диапазон случайных чисел

// --- Тесты с рандомизированными числами ---
TEST(GcdRandomTest, RandomCases) {
    for (int i = 0; i < 100; ++i) { // 100 случайных тестов
        int a = dist(rng);
        int b = dist(rng);

        int g = gcd(a, b);

        // Свойство 1: результат ≥ 0
        EXPECT_GE(g, 0) << "Failed on a=" << a << ", b=" << b;

        // Свойство 2: результат делит оба числа
        if (g != 0) { // чтобы избежать деления на 0
            EXPECT_EQ(a % g, 0) << "Failed on a=" << a << ", b=" << b;
            EXPECT_EQ(b % g, 0) << "Failed on a=" << a << ", b=" << b;
        }

        // Свойство 3: симметрия
        EXPECT_EQ(g, gcd(b, a)) << "Symmetry failed on a=" << a << ", b=" << b;
    }
}

// --- Тест с нулями отдельно ---
TEST(GcdRandomTest, Zeros) {
    for (int i = 0; i < 10; ++i) {
        int x = dist(rng);
        EXPECT_EQ(gcd(0, x), abs(x)) << "Failed on 0," << x;
        EXPECT_EQ(gcd(x, 0), abs(x)) << "Failed on " << x << ",0";
    }
}
