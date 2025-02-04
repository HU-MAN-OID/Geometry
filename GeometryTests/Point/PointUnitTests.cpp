#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

#include "../../Geometry/Point.h"

#include <sstream>

using namespace Kantarion::Geometry;

// Test fixture for Point class
class PointTest : public ::testing::Test {
protected:
    static constexpr Scalar_t EPSILON = std::numeric_limits<Scalar_t>::epsilon();
};

TEST_F(PointTest, DefaultConstructor)
{
    Point p;
    EXPECT_NEAR(p.getX(), 0.0, EPSILON);
    EXPECT_NEAR(p.getY(), 0.0, EPSILON);
    EXPECT_NEAR(p.getZ(), 0.0, EPSILON);
}

TEST_F(PointTest, ParameterizedConstructor)
{
    Point p(1.0, 2.0, 3.0);
    EXPECT_NEAR(p.getX(), 1.0, EPSILON);
    EXPECT_NEAR(p.getY(), 2.0, EPSILON);
    EXPECT_NEAR(p.getZ(), 3.0, EPSILON);
}

TEST_F(PointTest, CopyConstructor)
{
    Point p1(4.0, 5.0, 6.0);
    Point p2(p1);
    EXPECT_EQ(p1, p2);
}

TEST_F(PointTest, MoveConstructor)
{
    Point p1(7.0, 8.0, 9.0);
    Point p2(std::move(p1));
    EXPECT_NEAR(p2.getX(), 7.0, EPSILON);
    EXPECT_NEAR(p2.getY(), 8.0, EPSILON);
    EXPECT_NEAR(p2.getZ(), 9.0, EPSILON);
}

TEST_F(PointTest, AssignmentOperators)
{
    Point p1(10.0, 11.0, 12.0);
    Point p2;
    p2 = p1;
    EXPECT_EQ(p1, p2);

    Point p3;
    p3 = std::move(p2);
    EXPECT_EQ(p1, p3);
}

TEST_F(PointTest, Magnitude)
{
    Point p(3.0, 4.0, 0.0);
    EXPECT_NEAR(p.magnitude(), 5.0, EPSILON);
}

TEST_F(PointTest, Normalize)
{
    Point p(1.0, 2.0, 2.0);
    Point norm = p.normalize();
    EXPECT_NEAR(norm.magnitude(), 1.0, EPSILON);
}

TEST_F(PointTest, Distance)
{
    Point p1(1.0, 1.0, 1.0);
    Point p2(4.0, 5.0, 1.0);
    EXPECT_NEAR(p1.distance(p2), 5.0, EPSILON);
}

TEST_F(PointTest, ArithmeticOperations)
{
    Point p1(1.0, 2.0, 3.0);
    Point p2(4.0, 5.0, 6.0);
    Point p3 = p1 + p2;
    EXPECT_NEAR(p3.getX(), 5.0, EPSILON);
    EXPECT_NEAR(p3.getY(), 7.0, EPSILON);
    EXPECT_NEAR(p3.getZ(), 9.0, EPSILON);
}

TEST_F(PointTest, DotProduct)
{
    Point p1(1.0, 2.0, 3.0);
    Point p2(4.0, -5.0, 6.0);
    EXPECT_NEAR(p1.dot(p2), 12.0, EPSILON);
}

TEST_F(PointTest, CrossProduct)
{
    Point p1(1.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point cross = p1.cross(p2);
    EXPECT_NEAR(cross.getX(), 0.0, EPSILON);
    EXPECT_NEAR(cross.getY(), 0.0, EPSILON);
    EXPECT_NEAR(cross.getZ(), 1.0, EPSILON);
}
