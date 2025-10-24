#include <gtest/gtest.h>
#include <sstream>
#include <memory>

#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "array.h"

// ==================== FIXTURES ====================

class FigureTest : public ::testing::Test {
protected:
    void SetUp() override {
        rect = std::make_unique<Rectangle>(0, 0, 4, 3);
        rhombus = std::make_unique<Rhombus>(4, 6, Point{1, 1});
        trapezoid = std::make_unique<Trapezoid>(2, 4, 3, Point{0, 0});
    }

    std::unique_ptr<Rectangle> rect;
    std::unique_ptr<Rhombus> rhombus;
    std::unique_ptr<Trapezoid> trapezoid;
};

class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        array.Add(std::make_unique<Rectangle>(0, 0, 2, 2));
        array.Add(std::make_unique<Rhombus>(2, 2, Point{0, 0}));
        array.Add(std::make_unique<Trapezoid>(1, 3, 2, Point{1, 1}));
    }

    Array array;
};

// ==================== RECTANGLE TESTS ====================

TEST(RectangleTest, DefaultConstructor) {
    Rectangle rect;
    EXPECT_NO_THROW(rect.Center());
    EXPECT_GT(static_cast<double>(rect), 0);
}

TEST(RectangleTest, ValidConstructor) {
    EXPECT_NO_THROW(Rectangle(0, 0, 5, 5));
    EXPECT_NO_THROW(Rectangle(-2, -2, 2, 2));
}

TEST(RectangleTest, InvalidConstructor) {
    EXPECT_THROW(Rectangle(0, 0, 0, 5), std::invalid_argument);
    EXPECT_THROW(Rectangle(1, 1, 1, 2), std::invalid_argument);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle rect(0, 0, 4, 6);
    Point center = rect.Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle rect(0, 0, 4, 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(rect), 12.0);
    
    Rectangle rect2(-2, -2, 2, 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(rect2), 16.0);
}

TEST(RectangleTest, Equality) {
    Rectangle rect1(0, 0, 4, 3);
    Rectangle rect2(0, 0, 4, 3);
    Rectangle rect3(1, 1, 5, 4);
    
    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
}

TEST(RectangleTest, IOStreamOperations) {
    Rectangle rect(1, 2, 5, 6);
    std::stringstream ss;
    
    // Test output
    ss << rect;
    EXPECT_FALSE(ss.str().empty());
    EXPECT_NE(ss.str().find("Rectangle"), std::string::npos);
    
    // Test input
    Rectangle rect2;
    std::stringstream ss_input("1 2 5 6");
    EXPECT_NO_THROW(ss_input >> rect2);
    
    EXPECT_TRUE(rect == rect2);
}

TEST(RectangleTest, InvalidInput) {
    Rectangle rect;
    std::stringstream ss_invalid("0 0 0 5");
    EXPECT_THROW(ss_invalid >> rect, std::invalid_argument);
}

// ==================== RHOMBUS TESTS ====================

TEST(RhombusTest, DefaultConstructor) {
    Rhombus rh;
    EXPECT_NO_THROW(rh.Center());
    EXPECT_GT(static_cast<double>(rh), 0);
}

TEST(RhombusTest, ValidConstructor) {
    EXPECT_NO_THROW(Rhombus(3, 4, Point{1, 1}));
    EXPECT_NO_THROW(Rhombus(5, 5));
}

TEST(RhombusTest, InvalidConstructor) {
    EXPECT_THROW(Rhombus(0, 5), std::invalid_argument);
    EXPECT_THROW(Rhombus(-1, 3), std::invalid_argument);
}

TEST(RhombusTest, Center) {
    Rhombus rh(4, 6, Point{2, 3});
    Point center = rh.Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 3.0);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus rh(4, 6);
    EXPECT_DOUBLE_EQ(static_cast<double>(rh), 12.0);
}

TEST(RhombusTest, Equality) {
    Rhombus rh1(4, 6, Point{1, 1});
    Rhombus rh2(4, 6, Point{1, 1});
    Rhombus rh3(3, 5, Point{1, 1});
    
    EXPECT_TRUE(rh1 == rh2);
    EXPECT_FALSE(rh1 == rh3);
}

// ==================== TRAPEZOID TESTS ====================

TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid trap;
    EXPECT_NO_THROW(trap.Center());
    EXPECT_GT(static_cast<double>(trap), 0);
}

TEST(TrapezoidTest, ValidConstructor) {
    EXPECT_NO_THROW(Trapezoid(2, 4, 3));
    EXPECT_NO_THROW(Trapezoid(1, 5, 2, Point{1, 1}));
}

TEST(TrapezoidTest, InvalidConstructor) {
    EXPECT_THROW(Trapezoid(0, 4, 3), std::invalid_argument);
    EXPECT_THROW(Trapezoid(2, -1, 3), std::invalid_argument);
}

TEST(TrapezoidTest, Center) {
    Trapezoid trap(2, 4, 3, Point{1, 2});
    Point center = trap.Center();
    EXPECT_DOUBLE_EQ(center.first, 1.0);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid trap(2, 4, 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(trap), 9.0); // (2+4)*3/2 = 9
}

// ==================== ARRAY TESTS ====================

TEST_F(ArrayTest, AddFigures) {
    EXPECT_EQ(array.Size(), 3);
    
    array.Add(std::make_unique<Rectangle>(0, 0, 1, 1));
    EXPECT_EQ(array.Size(), 4);
}

TEST_F(ArrayTest, RemoveValidIndex) {
    EXPECT_NO_THROW(array.Remove(1));
    EXPECT_EQ(array.Size(), 2);
}

TEST_F(ArrayTest, RemoveInvalidIndex) {
    EXPECT_THROW(array.Remove(5), std::out_of_range);
    EXPECT_THROW(array.Remove(10), std::out_of_range);
}

TEST_F(ArrayTest, TotalArea) {
    double area = array.TotalArea();
    EXPECT_GT(area, 0);
    
    // Добавляем еще одну фигуру и проверяем что площадь увеличилась
    double initialArea = area;
    array.Add(std::make_unique<Rectangle>(0, 0, 2, 2));
    EXPECT_GT(array.TotalArea(), initialArea);
}

TEST_F(ArrayTest, PrintAllEmpty) {
    Array emptyArray;
    testing::internal::CaptureStdout();
    emptyArray.PrintAll();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No figures"), std::string::npos);
}

TEST_F(ArrayTest, PrintCentersEmpty) {
    Array emptyArray;
    testing::internal::CaptureStdout();
    emptyArray.PrintCenters();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No figures"), std::string::npos);
}

TEST_F(ArrayTest, Size) {
    EXPECT_EQ(array.Size(), 3);
    
    array.Remove(0);
    EXPECT_EQ(array.Size(), 2);
    
    array.Add(std::make_unique<Rectangle>(0, 0, 1, 1));
    EXPECT_EQ(array.Size(), 3);
}

// ==================== POLYMORPHISM TESTS ====================

TEST(PolymorphismTest, FigurePointerOperations) {
    std::unique_ptr<Figure> rect = std::make_unique<Rectangle>(0, 0, 4, 3);
    std::unique_ptr<Figure> rhombus = std::make_unique<Rhombus>(4, 6);
    std::unique_ptr<Figure> trapezoid = std::make_unique<Trapezoid>(2, 4, 3);
    
    // Проверяем что виртуальные функции работают корректно
    EXPECT_NO_THROW(rect->Center());
    EXPECT_NO_THROW(rhombus->Center());
    EXPECT_NO_THROW(trapezoid->Center());
    
    EXPECT_GT(static_cast<double>(*rect), 0);
    EXPECT_GT(static_cast<double>(*rhombus), 0);
    EXPECT_GT(static_cast<double>(*trapezoid), 0);
}

TEST(PolymorphismTest, ArrayWithDifferentFigures) {
    Array array;
    
    // Добавляем разные фигуры через указатель на базовый класс
    array.Add(std::make_unique<Rectangle>(0, 0, 2, 2));
    array.Add(std::make_unique<Rhombus>(3, 4));
    array.Add(std::make_unique<Trapezoid>(1, 3, 2));
    
    EXPECT_EQ(array.Size(), 3);
    EXPECT_GT(array.TotalArea(), 0);
    
    // Проверяем что PrintAll работает с разными типами
    testing::internal::CaptureStdout();
    array.PrintAll();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Rectangle"), std::string::npos);
    EXPECT_NE(output.find("Rhombus"), std::string::npos);
    EXPECT_NE(output.find("Trapezoid"), std::string::npos);
}

// ==================== COMPREHENSIVE TESTS ====================

TEST(ComprehensiveTest, AllFiguresInArray) {
    Array figures;
    
    // Создаем различные фигуры
    figures.Add(std::make_unique<Rectangle>(0, 0, 5, 5));
    figures.Add(std::make_unique<Rhombus>(6, 8, Point{2, 2}));
    figures.Add(std::make_unique<Trapezoid>(3, 7, 4, Point{1, 1}));
    
    // Проверяем общую функциональность
    EXPECT_EQ(figures.Size(), 3);
    
    double totalArea = figures.TotalArea();
    EXPECT_NEAR(totalArea, 25.0 + 24.0 + 20.0, 0.001); // 25 + 24 + 20
    
    // Проверяем что центры вычисляются
    testing::internal::CaptureStdout();
    figures.PrintCenters();
    std::string centersOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(centersOutput.empty());
    
    // Удаляем одну фигуру и проверяем
    figures.Remove(1);
    EXPECT_EQ(figures.Size(), 2);
    EXPECT_LT(figures.TotalArea(), totalArea);
}

// ==================== EXCEPTION SAFETY TESTS ====================

TEST(ExceptionSafetyTest, ArrayOperationsWithExceptions) {
    Array array;
    
    // Добавляем валидные фигуры
    array.Add(std::make_unique<Rectangle>(0, 0, 2, 2));
    
    // Попытка удалить невалидный индекс не должна ломать состояние
    EXPECT_THROW(array.Remove(5), std::out_of_range);
    EXPECT_EQ(array.Size(), 1); // Размер не должен измениться
    
    // После исключения массив должен оставаться в валидном состоянии
    array.Add(std::make_unique<Rhombus>(2, 2));
    EXPECT_EQ(array.Size(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}