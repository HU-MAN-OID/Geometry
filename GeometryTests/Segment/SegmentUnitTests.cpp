#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

#include "../../Geometry/Segment.h"

using namespace Kantarion::Geometry;

// Test case for segments that are parallel and overlapping
TEST(SegmentTest, ParallelOverlappingSegments)
{
    Segment seg1(Point(0, 0, 0), Point(5, 5, 5));
    Segment seg2(Point(1, 1, 1), Point(8, 8, 8));
    EXPECT_NEAR(Segment::closestDistance(seg1, seg2), 0.0, sc_Precision);
}

// Test case for segments that are perpendicular
TEST(SegmentTest, PerpendicularSegments)
{
    Segment seg1(Point(0, 0, 0), Point(5, 0, 0));
    Segment seg2(Point(2, -2, 0), Point(2, 2, 0));
    EXPECT_NEAR(Segment::closestDistance(seg1, seg2), 0.0, sc_Precision);
}

// Test case for segments that are not parallel or intersecting
TEST(SegmentTest, SkewSegments)
{
    Segment seg1(Point(0, 0, 0), Point(5, 0, 0));
    Segment seg2(Point(0, 3, 1), Point(5, 3, 1));
    EXPECT_NEAR(Segment::closestDistance(seg1, seg2), 1.0, sc_Precision);
}

// Test case for segments that share an endpoint
TEST(SegmentTest, SharedEndpoint)
{
    Segment seg1(Point(0, 0, 0), Point(3, 3, 3));
    Segment seg2(Point(3, 3, 3), Point(6, 6, 6));
    EXPECT_DOUBLE_EQ(Segment::closestDistance(seg1, seg2), 0.0);
}

// Test case for segments that are coincident
TEST(SegmentTest, CoincidentSegments)
{
    Segment seg1(Point(0, 0, 0), Point(5, 5, 5));
    Segment seg2(Point(0, 0, 0), Point(5, 5, 5));
    EXPECT_NEAR(Segment::closestDistance(seg1, seg2), 0.0, sc_Precision);
}

// Test case for segments that are very far apart
TEST(SegmentTest, DistantSegments)
{
    Segment seg1(Point(0, 0, 0), Point(1, 1, 1));
    Segment seg2(Point(10, 10, 10), Point(15, 15, 15));
    EXPECT_NEAR(Segment::closestDistance(seg1, seg2), std::sqrt(300), sc_Precision);
}

// Test case for segments that are reversed but should still yield the same distance
TEST(SegmentTest, ReversedSegments)
{
    Segment seg1(Point(0, 0, 0), Point(5, 0, 0));
    Segment seg2(Point(0, 3, 1), Point(5, 3, 1));
    Segment seg1Reversed(Point(5, 0, 0), Point(0, 0, 0));
    Segment seg2Reversed(Point(5, 3, 1), Point(0, 3, 1));
    EXPECT_NEAR(
        Segment::closestDistance(seg1, seg2),
        Segment::closestDistance(seg1Reversed, seg2Reversed),
        sc_Precision);
}
