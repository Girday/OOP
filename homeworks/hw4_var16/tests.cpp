#include <gtest/gtest.h>

#include "point.h"
#include "square.h"
#include "triangle.h"
#include "octagon.h"
#include "array.h"

#include <memory>
#include <cmath>

TEST(PointTest, EqualityAndAccessors) {
    Point<double> p1(3.5, -2.1);
    Point<double> p2(3.5, -2.1);
    Point<double> p3(1.0, 1.0);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_DOUBLE_EQ(p1.x(), 3.5);
    EXPECT_DOUBLE_EQ(p1.y(), -2.1);
}

TEST(SquareTest, AreaAndCenter) {
    Square<double> sq({0, 0}, {0, 2});
    double expectedArea = 4.0;
    EXPECT_NEAR(static_cast<double>(sq), expectedArea, 1e-9);

    auto c = sq.center();
    EXPECT_NEAR(c.x(), -1.0, 1e-9);
    EXPECT_NEAR(c.y(), 1.0, 1e-9);
}

TEST(SquareTest, DegenerateCase) {
    testing::internal::CaptureStdout();
    Square<double> sq({1, 1}, {1, 1});
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Points are identical"), std::string::npos);
}

TEST(TriangleTest, AreaAndCenter) {
    Triangle<double> tri({0, 0}, {4, 0}, 3);
    double expectedArea = 0.5 * 4 * 3;
    EXPECT_NEAR(static_cast<double>(tri), expectedArea, 1e-9);

    auto c = tri.center();
    EXPECT_NEAR(c.x(), 2.0, 1e-9);
    EXPECT_NEAR(c.y(), 1.0, 1e-9);
}

TEST(TriangleTest, InvalidHeight) {
    testing::internal::CaptureStdout();
    Triangle<double> tri({0, 0}, {1, 0}, -2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Height must be positive"), std::string::npos);
}

TEST(OctagonTest, AreaAndCenter) {
    Octagon<double> oct({0, 0}, {1, 0});

    double radius = 1.0;
    double side = std::sqrt(2 - std::sqrt(2)) * radius;  // side = sqrt(2 - sqrt(2)) * radius
    double expectedArea = 2 * (1 + std::sqrt(2)) * side * side;

    EXPECT_NEAR(static_cast<double>(oct), expectedArea, 1e-6);

    auto c = oct.center();
    EXPECT_NEAR(c.x(), 0.0, 1e-9);
    EXPECT_NEAR(c.y(), 0.0, 1e-9);
}

TEST(OctagonTest, IdenticalPoints) {
    testing::internal::CaptureStdout();
    Octagon<double> oct({1, 1}, {1, 1});
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Points are identical"), std::string::npos);
}

TEST(ArrayTest, AddAndRemove) {
    Array<Figure<double>> arr;

    auto s1 = std::make_shared<Square<double>>(Point<double>(0, 0), Point<double>(0, 2));
    auto t1 = std::make_shared<Triangle<double>>(Point<double>(0, 0), Point<double>(4, 0), 3);

    arr.add(s1);
    arr.add(t1);
    EXPECT_EQ(arr.getSize(), 2);

    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 1);
}

TEST(ArrayTest, RemoveOutOfRange) {
    Array<Figure<double>> arr;
    EXPECT_THROW(arr.remove(0), std::out_of_range);
}

TEST(ArrayTest, MoveSemantics) {
    Array<Figure<double>> arr1;
    arr1.add(std::make_shared<Square<double>>(Point<double>(0, 0), Point<double>(1, 0)));

    Array<Figure<double>> arr2 = std::move(arr1);
    EXPECT_EQ(arr1.getSize(), 0);
    EXPECT_EQ(arr2.getSize(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
