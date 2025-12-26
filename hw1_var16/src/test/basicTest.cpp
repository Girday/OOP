#include <gtest/gtest.h>
#include "../include/gcd.h"
#include <limits>

// --- Базовые тесты ---
TEST(gcdTest, PositiveNumbers) {
    EXPECT_EQ(gcd(48, 18), 6);
    EXPECT_EQ(gcd(54, 24), 6);
    EXPECT_EQ(gcd(101, 103), 1); // простые числа
}

TEST(gcdTest, WithZero) {
    EXPECT_EQ(gcd(0, 5), 5);
    EXPECT_EQ(gcd(7, 0), 7);
    EXPECT_EQ(gcd(0, 0), 0); // gcd(0,0) обычно определяют, как 0
}

TEST(gcdTest, NegativeNumbers) {
    EXPECT_EQ(gcd(-48, 18), 6);
    EXPECT_EQ(gcd(48, -18), 6);
    EXPECT_EQ(gcd(-48, -18), 6);
}

TEST(gcdTest, SameNumbers) {
    EXPECT_EQ(gcd(10, 10), 10);
    EXPECT_EQ(gcd(-7, -7), 7);
}

// --- Тестирование свойств ---
TEST(gcdProperties, Symmetry) {
    EXPECT_EQ(gcd(270, 192), gcd(192, 270)); 
}

TEST(gcdProperties, DividesBoth) {
    int a = 84, b = 36;
    int g = gcd(a, b);
    EXPECT_EQ(a % g, 0);
    EXPECT_EQ(b % g, 0);
}

TEST(gcdProperties, LargeNumbers) {
    // Проверим работу на больших числах
    int big1 = std::numeric_limits<int>::max() - 1;
    int big2 = std::numeric_limits<int>::max() - 3;
    EXPECT_EQ(gcd(big1, big2), 2); // оба чётные
}
