#include <gtest/gtest.h>
#include "five.h"
#include <sstream>

// === ТЕСТЫ КОНСТРУКТОРОВ ===

TEST(FiveConstructorTest, DefaultConstructor) {
    Five num;
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "0");
}

TEST(FiveConstructorTest, StringConstructorValid) {
    Five num("243");
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "243");
}

TEST(FiveConstructorTest, StringConstructorSingleDigit) {
    Five num("4");
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "4");
}

TEST(FiveConstructorTest, StringConstructorInvalidDigit) {
    EXPECT_THROW(Five num("456"), std::invalid_argument);
    EXPECT_THROW(Five num("12a"), std::invalid_argument);
    EXPECT_THROW(Five num("9"), std::invalid_argument);
}

TEST(FiveConstructorTest, InitializerListValid) {
    Five num{4, 3, 2, 1};
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "4321");
}

TEST(FiveConstructorTest, InitializerListInvalid) {
    EXPECT_THROW(Five num({5, 3, 2}), std::invalid_argument);
    EXPECT_THROW(Five num({1, 2, 9}), std::invalid_argument);
}

TEST(FiveConstructorTest, CopyConstructor) {
    Five original("1234");
    Five copy(original);
    
    std::ostringstream oss1, oss2;
    original.print(oss1);
    copy.print(oss2);
    
    EXPECT_EQ(oss1.str(), oss2.str());
    EXPECT_TRUE(original.equals(copy));
}

TEST(FiveConstructorTest, MoveConstructor) {
    Five original("4321");
    Five moved(std::move(original));
    
    std::ostringstream oss;
    moved.print(oss);
    EXPECT_EQ(oss.str(), "4321");
}

// === ТЕСТЫ СЛОЖЕНИЯ ===

TEST(FiveAddTest, SimpleAddition) {
    Five a("12");
    Five b("23");
    Five result = a.add(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "40"); // 12₅ + 23₅ = 40₅
}

TEST(FiveAddTest, AdditionWithCarry) {
    Five a("44");
    Five b("11");
    Five result = a.add(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "110"); // 44₅ + 11₅ = 110₅
}

TEST(FiveAddTest, AdditionWithZero) {
    Five a("123");
    Five b("0");
    Five result = a.add(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "123");
}

TEST(FiveAddTest, AdditionDifferentSizes) {
    Five a("1234");
    Five b("2");
    Five result = a.add(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "1241");
}

TEST(FiveAddTest, AdditionMaxDigits) {
    Five a("444");
    Five b("1");
    Five result = a.add(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "1000");
}

// === ТЕСТЫ ВЫЧИТАНИЯ ===

TEST(FiveSubtractTest, SimpleSubtraction) {
    Five a("43");
    Five b("21");
    Five result = a.subtract(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "22");
}

TEST(FiveSubtractTest, SubtractionWithBorrow) {
    Five a("100");
    Five b("1");
    Five result = a.subtract(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "44"); // 100₅ - 1₅ = 44₅
}

TEST(FiveSubtractTest, SubtractionResultZero) {
    Five a("123");
    Five b("123");
    Five result = a.subtract(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "0");
}

TEST(FiveSubtractTest, SubtractionNegativeResult) {
    Five a("10");
    Five b("20");
    EXPECT_THROW(a.subtract(b), std::invalid_argument);
}

TEST(FiveSubtractTest, SubtractionFromLarger) {
    Five a("1234");
    Five b("234");
    Five result = a.subtract(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "1000");
}

// === ТЕСТЫ СРАВНЕНИЯ ===

TEST(FiveComparisonTest, EqualsTrue) {
    Five a("1234");
    Five b("1234");
    EXPECT_TRUE(a.equals(b));
}

TEST(FiveComparisonTest, EqualsFalse) {
    Five a("1234");
    Five b("1233");
    EXPECT_FALSE(a.equals(b));
}

TEST(FiveComparisonTest, EqualsDifferentSize) {
    Five a("123");
    Five b("1234");
    EXPECT_FALSE(a.equals(b));
}

TEST(FiveComparisonTest, GreaterTrue) {
    Five a("1234");
    Five b("123");
    EXPECT_TRUE(a.greater(b));
}

TEST(FiveComparisonTest, GreaterFalse) {
    Five a("123");
    Five b("1234");
    EXPECT_FALSE(a.greater(b));
}

TEST(FiveComparisonTest, GreaterSameSize) {
    Five a("234");
    Five b("123");
    EXPECT_TRUE(a.greater(b));
}

TEST(FiveComparisonTest, GreaterEqual) {
    Five a("123");
    Five b("123");
    EXPECT_FALSE(a.greater(b));
}

TEST(FiveComparisonTest, LessTrue) {
    Five a("123");
    Five b("1234");
    EXPECT_TRUE(a.less(b));
}

TEST(FiveComparisonTest, LessFalse) {
    Five a("1234");
    Five b("123");
    EXPECT_FALSE(a.less(b));
}

TEST(FiveComparisonTest, LessSameSize) {
    Five a("123");
    Five b("234");
    EXPECT_TRUE(a.less(b));
}

TEST(FiveComparisonTest, LessEqual) {
    Five a("123");
    Five b("123");
    EXPECT_FALSE(a.less(b));
}

// === ТЕСТЫ ВЫВОДА ===

TEST(FivePrintTest, PrintSingleDigit) {
    Five num("3");
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "3");
}

TEST(FivePrintTest, PrintMultipleDigits) {
    Five num("43210");
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "43210");
}

TEST(FivePrintTest, PrintZero) {
    Five num("0");
    std::ostringstream oss;
    num.print(oss);
    EXPECT_EQ(oss.str(), "0");
}

// === КОМПЛЕКСНЫЕ ТЕСТЫ ===

TEST(FiveComplexTest, ChainedOperations) {
    Five a("100");
    Five b("23");
    Five c("12");
    
    Five result = a.add(b).subtract(c);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "111");
}

TEST(FiveComplexTest, CopyAndModify) {
    Five original("123");
    Five copy(original);
    
    Five modified = copy.add(Five("1"));
    
    EXPECT_FALSE(original.equals(modified));
    
    std::ostringstream oss1, oss2;
    original.print(oss1);
    modified.print(oss2);
    
    EXPECT_EQ(oss1.str(), "123");
    EXPECT_EQ(oss2.str(), "124");
}

TEST(FiveComplexTest, NormalizationAfterSubtraction) {
    Five a("1000");
    Five b("1");
    Five result = a.subtract(b);
    
    std::ostringstream oss;
    result.print(oss);
    EXPECT_EQ(oss.str(), "444");
}

// === ГРАНИЧНЫЕ СЛУЧАИ ===

TEST(FiveEdgeCaseTest, LeadingZeros) {
    Five a("0123");
    std::ostringstream oss;
    a.print(oss);
    EXPECT_EQ(oss.str(), "0123");
}

TEST(FiveEdgeCaseTest, MultipleAdditions) {
    Five sum("0");
    for (int i = 0; i < 5; ++i) {
        sum = sum.add(Five("1"));
    }
    
    std::ostringstream oss;
    sum.print(oss);
    EXPECT_EQ(oss.str(), "10"); // 5 в десятичной = 10 в пятеричной
}

TEST(FiveEdgeCaseTest, SelfComparison) {
    Five num("1234");
    EXPECT_TRUE(num.equals(num));
    EXPECT_FALSE(num.greater(num));
    EXPECT_FALSE(num.less(num));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}