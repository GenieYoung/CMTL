#include "CMTL/geometry_process/intersect.h"

#include <gtest/gtest.h>

typedef CMTL::geo2d::Point<mpq_class> Point2R;
typedef CMTL::geo2d::Box<mpq_class> Box2R;
typedef CMTL::geo2d::Segment<mpq_class> Segment2R;
typedef CMTL::geo2d::Line<mpq_class> Line2R;
typedef CMTL::geo2d::Ray<mpq_class> Ray2R;

using CMTL::geometry_process::intersect;

TEST(IntersectTest, BoxSegment2DIntersectTest)
{
    mpq_class tr0, tr1;

    Box2R box1 = Box2R(Point2R(0,0), Point2R(1,1));
    
    Segment2R seg1 = Segment2R(Point2R(-1, -2), Point2R(2,4));
    EXPECT_TRUE(intersect(box1, seg1, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, mpq_class(1,3));
    EXPECT_EQ(tr1, mpq_class(1,2));

    Segment2R seg2 = Segment2R(Point2R(-1, 0), Point2R(1,2));
    EXPECT_TRUE(intersect(box1, seg2, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, mpq_class(1,2));
    EXPECT_EQ(tr1, mpq_class(1,2));

    Segment2R seg3 = Segment2R(Point2R(-1, mpq_class(1,1e20)), Point2R(1,2));
    EXPECT_FALSE(intersect(box1, seg3, tr0, tr1)) << tr0 << " " << tr1;

    Segment2R seg4 = Segment2R(Point2R(0, 0), Point2R(0,1));
    EXPECT_TRUE(intersect(box1, seg4, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 1);

    Segment2R seg5 = Segment2R(Point2R(0, 0), Point2R(1,0));
    EXPECT_TRUE(intersect(box1, seg5, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 1);

    Segment2R seg6 = Segment2R(Point2R(0, -0.5), Point2R(0,0.5));
    EXPECT_TRUE(intersect(box1, seg6, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0.5);
    EXPECT_EQ(tr1, 1);

    Segment2R seg7 = Segment2R(Point2R(0.5, 0), Point2R(1.5,0));
    EXPECT_TRUE(intersect(box1, seg7, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 0.5);

    Segment2R seg8 = Segment2R(Point2R(0.5, 0.5), Point2R(0.5,0.75));
    EXPECT_TRUE(intersect(box1, seg8, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 1);

    Segment2R seg9 = Segment2R(Point2R(0.5, -2), Point2R(0.5,-1));
    EXPECT_FALSE(intersect(box1, seg9, tr0, tr1)) << tr0 << " " << tr1;
}

TEST(IntersectTest, BoxLine2DIntersectTest)
{
    mpq_class tr0, tr1;

    Box2R box1 = Box2R(Point2R(0,0), Point2R(1,1));
    
    Line2R line1 = Line2R(Point2R(-1, -2), Point2R(3,6));
    EXPECT_TRUE(intersect(box1, line1, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, mpq_class(1,3));
    EXPECT_EQ(tr1, mpq_class(1,2));

    Line2R line2 = Line2R(Point2R(-1, 0), Point2R(2,2));
    EXPECT_TRUE(intersect(box1, line2, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, mpq_class(1,2));
    EXPECT_EQ(tr1, mpq_class(1,2));

    Line2R line3 = Line2R(Point2R(-1, mpq_class(1,1e20)), Point2R(2,2));
    EXPECT_FALSE(intersect(box1, line3, tr0, tr1)) << tr0 << " " << tr1;

    Line2R line4 = Line2R(Point2R(0, 0), Point2R(0,1));
    EXPECT_TRUE(intersect(box1, line4, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 1);

    Line2R line5 = Line2R(Point2R(0, 0), Point2R(1,0));
    EXPECT_TRUE(intersect(box1, line5, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 1);

    Line2R line6 = Line2R(Point2R(0, -0.5), Point2R(0, 1));
    EXPECT_TRUE(intersect(box1, line6, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0.5);
    EXPECT_EQ(tr1, 1.5);

    Line2R line7 = Line2R(Point2R(0.5, 0), Point2R(1,0));
    EXPECT_TRUE(intersect(box1, line7, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, -0.5);
    EXPECT_EQ(tr1, 0.5);

    Line2R line8 = Line2R(Point2R(0.5, 0.5), Point2R(1,0));
    EXPECT_TRUE(intersect(box1, line8, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, -0.5);
    EXPECT_EQ(tr1, 0.5);

    Line2R line9 = Line2R(Point2R(0.5, -2), Point2R(0,1));
    EXPECT_TRUE(intersect(box1, line9, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 2);
    EXPECT_EQ(tr1, 3);
}

TEST(IntersectTest, BoxRay2DIntersectTest)
{
    mpq_class tr0, tr1;

    Box2R box1 = Box2R(Point2R(0,0), Point2R(1,1));
    
    Ray2R ray1 = Ray2R(Point2R(-1, -2), Point2R(3,6));
    EXPECT_TRUE(intersect(box1, ray1, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, mpq_class(1,3));
    EXPECT_EQ(tr1, mpq_class(1,2));

    Ray2R ray2 = Ray2R(Point2R(-1, 0), Point2R(2,2));
    EXPECT_TRUE(intersect(box1, ray2, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, mpq_class(1,2));
    EXPECT_EQ(tr1, mpq_class(1,2));

    Ray2R ray3 = Ray2R(Point2R(-1, mpq_class(1,1e20)), Point2R(2,2));
    EXPECT_FALSE(intersect(box1, ray3, tr0, tr1)) << tr0 << " " << tr1;

    Ray2R ray4 = Ray2R(Point2R(0, 0), Point2R(0,1));
    EXPECT_TRUE(intersect(box1, ray4, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 1);

    Ray2R ray5 = Ray2R(Point2R(0, 0), Point2R(1,0));
    EXPECT_TRUE(intersect(box1, ray5, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 1);

    Ray2R ray6 = Ray2R(Point2R(0, -0.5), Point2R(0, 1));
    EXPECT_TRUE(intersect(box1, ray6, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0.5);
    EXPECT_EQ(tr1, 1.5);

    Ray2R ray7 = Ray2R(Point2R(0.5, 0), Point2R(1,0));
    EXPECT_TRUE(intersect(box1, ray7, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 0.5);

    Ray2R ray8 = Ray2R(Point2R(0.5, 0.5), Point2R(1,0));
    EXPECT_TRUE(intersect(box1, ray8, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 0);
    EXPECT_EQ(tr1, 0.5);

    Ray2R ray9 = Ray2R(Point2R(0.5, -2), Point2R(0,1));
    EXPECT_TRUE(intersect(box1, ray9, tr0, tr1)) << tr0 << " " << tr1;
    EXPECT_EQ(tr0, 2);
    EXPECT_EQ(tr1, 3);
}

TEST(IntersectTest, SegmentSegmentIntersectTest)
{
    Segment2R seg1(Point2R(0,0), Point2R(1,1));
    Segment2R seg2(Point2R(0,1), Point2R(1,0));
    EXPECT_TRUE(intersect(seg1, seg2));
    EXPECT_TRUE(intersect(seg1, seg1));
    EXPECT_TRUE(intersect(seg2, seg2));
    EXPECT_TRUE(intersect(seg1, seg1, true));
    EXPECT_TRUE(intersect(seg2, seg2, true));

    Segment2R seg3(Point2R(0,0), Point2R(-1,1));
    EXPECT_TRUE(intersect(seg1, seg3));
    EXPECT_FALSE(intersect(seg1, seg3, true));

    Segment2R seg4(Point2R(0,0), Point2R(1,-1));
    EXPECT_TRUE(intersect(seg4, seg1));
    EXPECT_FALSE(intersect(seg4, seg1, true));

    Segment2R seg5(Point2R(1,1), Point2R(0,2));
    EXPECT_TRUE(intersect(seg1, seg5));
    EXPECT_FALSE(intersect(seg1, seg5, true));

    Segment2R seg6(Point2R(1,1), Point2R(2,0));
    EXPECT_TRUE(intersect(seg6, seg1));
    EXPECT_FALSE(intersect(seg6, seg1, true));

    Segment2R seg7(Point2R(0.5,0.5), Point2R(0,2));
    EXPECT_TRUE(intersect(seg1, seg7));
    EXPECT_FALSE(intersect(seg1, seg7, true));

    Segment2R seg8(Point2R(0.5,0.5), Point2R(2,0));
    EXPECT_TRUE(intersect(seg8, seg1));
    EXPECT_FALSE(intersect(seg8, seg1, true));

    Segment2R seg9(Point2R(0,0), Point2R(-1,-1));
    EXPECT_TRUE(intersect(seg1, seg9));
    EXPECT_TRUE(intersect(seg9, seg1));
    EXPECT_FALSE(intersect(seg1, seg9, true));

    Segment2R seg10(Point2R(0,0), Point2R(0.5,0.5));
    EXPECT_TRUE(intersect(seg1, seg10));
    EXPECT_TRUE(intersect(seg10, seg1));
    EXPECT_TRUE(intersect(seg1, seg10, true));
    EXPECT_TRUE(intersect(seg10, seg1, true));

    Segment2R seg11(Point2R(-1,-1), Point2R(-2,-2));
    EXPECT_FALSE(intersect(seg11, seg1));

    Segment2R seg12(Point2R(0.3,0.3), Point2R(0.8,0.8));
    EXPECT_TRUE(intersect(seg1, seg12));

    Segment2R seg13(Point2R(0.3,0.3), Point2R(1.8,1.8));
    EXPECT_TRUE(intersect(seg1, seg13));

    Segment2R seg14(Point2R(1,1), Point2R(1.8,1.8));
    EXPECT_TRUE(intersect(seg1, seg14));
    EXPECT_FALSE(intersect(seg1, seg14, true));

    Segment2R seg15(Point2R(1.1,1.1), Point2R(1.8,1.8));
    EXPECT_FALSE(intersect(seg1, seg15));

    Segment2R seg16(Point2R(-1,-1), Point2R(2,2));
    EXPECT_TRUE(intersect(seg1, seg16));
}