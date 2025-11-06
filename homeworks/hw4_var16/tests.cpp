#include <gtest/gtest.h>
#include "array.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"


// ---------- Point ----------

TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x(), 0.0);
    EXPECT_DOUBLE_EQ(p.y(), 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.x(), 3.5);
    EXPECT_DOUBLE_EQ(p.y(), 4.2);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 3.0);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}


// ---------- Square ----------

TEST(SquareTest, CenterAndArea) {
    Square<double> sq(Point<double>(0, 0), Point<double>(2, 0));
    auto c = sq.center();
    EXPECT_NEAR(c.x(), 1.0, 1e-9);
    EXPECT_NEAR(c.y(), 1.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(sq), 4.0, 1e-9);
}

TEST(SquareTest, EqualityOperator) {
    Square<double> s1(Point<double>(0, 0), Point<double>(1, 0));
    Square<double> s2(Point<double>(0, 0), Point<double>(1, 0));
    const Figure<double>& f1 = s1;
    const Figure<double>& f2 = s2;
    EXPECT_TRUE(f1 == f2);
}


// ---------- Triangle ----------

TEST(TriangleTest, CenterAndArea) {
    Triangle<double> tri(Point<double>(0, 0), Point<double>(2, 0), 2.0);
    auto c = tri.center();
    EXPECT_NEAR(c.x(), 1.0, 1e-9);
    EXPECT_NEAR(c.y(), 2.0 / 3.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(tri), 2.0, 1e-9);
}

TEST(TriangleTest, EqualityOperator) {
    Triangle<double> t1(Point<double>(0, 0), Point<double>(2, 0), 2.0);
    Triangle<double> t2(Point<double>(0, 0), Point<double>(2, 0), 2.0);
    const Figure<double>& f1 = t1;
    const Figure<double>& f2 = t2;
    EXPECT_TRUE(f1 == f2);
}


// ---------- Octagon ----------

TEST(OctagonTest, CenterAndArea) {
    Octagon<double> o(Point<double>(0, 0), Point<double>(1, 0));
    auto c = o.center();
    EXPECT_NEAR(c.x(), 0.0, 1e-9);
    EXPECT_NEAR(c.y(), 0.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(o), 2.82842712, 1e-6);
}

TEST(OctagonTest, EqualityOperator) {
    Octagon<double> o1(Point<double>(0, 0), Point<double>(1, 0));
    Octagon<double> o2(Point<double>(0, 0), Point<double>(1, 0));
    const Figure<double>& f1 = o1;
    const Figure<double>& f2 = o2;
    EXPECT_TRUE(f1 == f2);
}


// ---------- Array (shared_ptr<Figure>) ----------

class ArrayPolyTest : public ::testing::Test {
protected:
    void SetUp() override {
        sq = std::make_shared<Square<double>>(Point<double>(0, 0), Point<double>(1, 0));
        tri = std::make_shared<Triangle<double>>(Point<double>(0, 0), Point<double>(2, 0), 2.0);
        oct = std::make_shared<Octagon<double>>(Point<double>(0, 0), Point<double>(1, 0));
    }

    Array<std::shared_ptr<Figure<double>>> arr;
    std::shared_ptr<Square<double>> sq;
    std::shared_ptr<Triangle<double>> tri;
    std::shared_ptr<Octagon<double>> oct;
};

TEST_F(ArrayPolyTest, AddAndSize) {
    EXPECT_EQ(arr.getSize(), 0);
    arr.add(sq);
    arr.add(tri);
    EXPECT_EQ(arr.getSize(), 2);
}

TEST_F(ArrayPolyTest, RemoveWorks) {
    arr.add(sq);
    arr.add(tri);
    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 1);
}

TEST_F(ArrayPolyTest, RemoveInvalidThrows) {
    EXPECT_THROW(arr.remove(0), std::out_of_range);
}

TEST_F(ArrayPolyTest, PrintEmptyThrows) {
    EXPECT_THROW(arr.printAll(), std::out_of_range);
    EXPECT_THROW(arr.printCenters(), std::out_of_range);
    EXPECT_THROW(arr.printTotalArea(), std::out_of_range);
}

TEST_F(ArrayPolyTest, TotalAreaOutput) {
    arr.add(sq);
    arr.add(tri);
    testing::internal::CaptureStdout();
    arr.printTotalArea();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Total Area") != std::string::npos);
}

TEST_F(ArrayPolyTest, MoveSemantics) {
    arr.add(sq);
    arr.add(tri);
    Array<std::shared_ptr<Figure<double>>> moved = std::move(arr);
    EXPECT_EQ(moved.getSize(), 2);
    EXPECT_EQ(arr.getSize(), 0);
}


// ---------- Array (Square<double>) ----------

TEST(ArrayConcreteTest, WorksWithValueType) {
    Array<Square<double>> squares;
    squares.add(Square<double>(Point<double>(0, 0), Point<double>(1, 0)));
    squares.add(Square<double>(Point<double>(0, 0), Point<double>(2, 0)));
    EXPECT_EQ(squares.getSize(), 2);
    EXPECT_NO_THROW(squares.printCenters());
    EXPECT_NO_THROW(squares.printTotalArea());
    squares.remove(0);
    EXPECT_EQ(squares.getSize(), 1);
}


// ---------- Integration Test ----------

TEST(IntegrationTest, AddRemoveAndPrintAll) {
    Array<std::shared_ptr<Figure<double>>> figs;

    auto sq = std::make_shared<Square<double>>(Point<double>(0, 0), Point<double>(1, 0));
    auto tri = std::make_shared<Triangle<double>>(Point<double>(0, 0), Point<double>(2, 0), 2.0);
    auto oct = std::make_shared<Octagon<double>>(Point<double>(0, 0), Point<double>(1, 0));

    figs.add(sq);
    figs.add(tri);
    figs.add(oct);
    
    EXPECT_EQ(figs.getSize(), 3);

    EXPECT_NO_THROW(figs.printAll());
    EXPECT_NO_THROW(figs.printCenters());
    EXPECT_NO_THROW(figs.printTotalArea());

    figs.remove(1);
    EXPECT_EQ(figs.getSize(), 2);
}


// ---------- Type Difference ----------

TEST(FigureTest, DifferentTypesNotEqual) {
    Square<double> s(Point<double>(0, 0), Point<double>(1, 0));
    Triangle<double> t(Point<double>(0, 0), Point<double>(1, 0), 1.0);
    const Figure<double>& f1 = s;
    const Figure<double>& f2 = t;
    EXPECT_FALSE(f1 == f2);
}

TEST(FigureTest, DifferentTypesNotEqual_SameArea) {
    Square<double> sq(Point<double>(0,0), Point<double>(2,0));
    Triangle<double> tri(Point<double>(0,0), Point<double>(4,0), 2);

    const Figure<double>& f1 = sq;
    const Figure<double>& f2 = tri;

    EXPECT_FALSE(f1 == f2);
}

TEST(FigureTest, DifferentTypesNotEqual_SameCenters) {
    Square<double> sq(Point<double>(0,0), Point<double>(2,0));
    Octagon<double> oct(Point<double>(1,1), Point<double>(2,1));

    const Figure<double>& f1 = sq;
    const Figure<double>& f2 = oct;

    EXPECT_FALSE(f1 == f2);
}

TEST(FigureTest, DegenerateFiguresStillNotEqual) {
    Triangle<double> t1(Point<double>(0,0), Point<double>(0,0), 0);
    Square<double> sq(Point<double>(0,0), Point<double>(0,0));

    const Figure<double>& f1 = t1;
    const Figure<double>& f2 = sq;

    EXPECT_FALSE(f1 == f2); 
}

TEST(FigureTest, SameTypeEqualButDifferentParameters) {
    Square<double> s1(Point<double>(0,0), Point<double>(1,0));
    Square<double> s2(Point<double>(0,0), Point<double>(2,0));

    const Figure<double>& f1 = s1;
    const Figure<double>& f2 = s2;

    EXPECT_FALSE(f1 == f2);
}

TEST(FigureTest, OctagonAndTriangleNeverEqual) {
    Octagon<double> o(Point<double>(0,0), Point<double>(3,0));
    Triangle<double> t(Point<double>(0,0), Point<double>(6,0), 3);

    const Figure<double>& f1 = o;
    const Figure<double>& f2 = t;

    EXPECT_FALSE(f1 == f2);
}


// ---------- Main ----------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
