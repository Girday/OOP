#include <gtest/gtest.h>
#include <sstream>
#include <memory>

#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "array.h"


// Фикстуры

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


// Прямоугольник

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
    
    ss << rect;
    EXPECT_FALSE(ss.str().empty());
    EXPECT_NE(ss.str().find("Rectangle"), std::string::npos);
    
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


// Ромб

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

TEST(RhombusTest, IOStreamOperations) {
    Rhombus rh(4, 6, Point{1, 2});
    std::stringstream ss;
    
    ss << rh;
    EXPECT_FALSE(ss.str().empty());
    EXPECT_NE(ss.str().find("Rhombus"), std::string::npos);
    
    Rhombus rh2;
    std::stringstream ss_input("4 6 1 2");
    EXPECT_NO_THROW(ss_input >> rh2);
    
    EXPECT_TRUE(rh == rh2);
}

TEST(RhombusTest, InvalidInput) {
    Rhombus rh;
    std::stringstream ss_invalid("0 5 0 0");
    EXPECT_THROW(ss_invalid >> rh, std::invalid_argument);
    
    std::stringstream ss_negative("-1 5 0 0");
    EXPECT_THROW(ss_negative >> rh, std::invalid_argument);
}


// Трапеция

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
    EXPECT_DOUBLE_EQ(static_cast<double>(trap), 9.0);
}

TEST(TrapezoidTest, IOStreamOperations) {
    Trapezoid trap(2, 4, 3, Point{1, 2});
    std::stringstream ss;
    
    ss << trap;
    EXPECT_FALSE(ss.str().empty());
    EXPECT_NE(ss.str().find("Trapezoid"), std::string::npos);
    
    Trapezoid trap2;
    std::stringstream ss_input("2 4 3 1 2");
    EXPECT_NO_THROW(ss_input >> trap2);
    
    EXPECT_TRUE(trap == trap2);
}

TEST(TrapezoidTest, InvalidInput) {
    Trapezoid trap;
    std::stringstream ss_invalid("0 4 3 0 0");
    EXPECT_THROW(ss_invalid >> trap, std::invalid_argument);
    
    std::stringstream ss_negative("2 -1 3 0 0");
    EXPECT_THROW(ss_negative >> trap, std::invalid_argument);
    
    std::stringstream ss_zero_height("2 4 0 0 0");
    EXPECT_THROW(ss_zero_height >> trap, std::invalid_argument);
}


// Массив фигур

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

// Полиморфизм

TEST(PolymorphismTest, FigurePointerOperations) {
    std::unique_ptr<Figure> rect = std::make_unique<Rectangle>(0, 0, 4, 3);
    std::unique_ptr<Figure> rhombus = std::make_unique<Rhombus>(4, 6);
    std::unique_ptr<Figure> trapezoid = std::make_unique<Trapezoid>(2, 4, 3);
    
    EXPECT_NO_THROW(rect->Center());
    EXPECT_NO_THROW(rhombus->Center());
    EXPECT_NO_THROW(trapezoid->Center());
    
    EXPECT_GT(static_cast<double>(*rect), 0);
    EXPECT_GT(static_cast<double>(*rhombus), 0);
    EXPECT_GT(static_cast<double>(*trapezoid), 0);
}

TEST(PolymorphismTest, ArrayWithDifferentFigures) {
    Array array;
    
    array.Add(std::make_unique<Rectangle>(0, 0, 2, 2));
    array.Add(std::make_unique<Rhombus>(3, 4));
    array.Add(std::make_unique<Trapezoid>(1, 3, 2));
    
    EXPECT_EQ(array.Size(), 3);
    EXPECT_GT(array.TotalArea(), 0);
    
    testing::internal::CaptureStdout();
    array.PrintAll();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Rectangle"), std::string::npos);
    EXPECT_NE(output.find("Rhombus"), std::string::npos);
    EXPECT_NE(output.find("Trapezoid"), std::string::npos);
}


// Комплексный тест

TEST(ComprehensiveTest, AllFiguresInArray) {
    Array figures;
    
    figures.Add(std::make_unique<Rectangle>(0, 0, 5, 5));
    figures.Add(std::make_unique<Rhombus>(6, 8, Point{2, 2}));
    figures.Add(std::make_unique<Trapezoid>(3, 7, 4, Point{1, 1}));
    
    EXPECT_EQ(figures.Size(), 3);
    
    double totalArea = figures.TotalArea();
    EXPECT_NEAR(totalArea, 25.0 + 24.0 + 20.0, 0.001);
    
    testing::internal::CaptureStdout();
    figures.PrintCenters();
    std::string centersOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(centersOutput.empty());
    
    figures.Remove(1);
    EXPECT_EQ(figures.Size(), 2);
    EXPECT_LT(figures.TotalArea(), totalArea);
}


// Обработка исключений

TEST(ExceptionSafetyTest, ArrayOperationsWithExceptions) {
    Array array;
    
    array.Add(std::make_unique<Rectangle>(0, 0, 2, 2));
    
    EXPECT_THROW(array.Remove(5), std::out_of_range);
    EXPECT_EQ(array.Size(), 1);
    
    array.Add(std::make_unique<Rhombus>(2, 2));
    EXPECT_EQ(array.Size(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}