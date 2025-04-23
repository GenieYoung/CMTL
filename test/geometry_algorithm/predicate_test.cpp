#include "CMTL/geometry_algorithm/predicate.h"

#include <gtest/gtest.h>

typedef CMTL::geo2d::Point<double> Point2D;
typedef CMTL::geo2d::Point<mpq_class> Point2R;
typedef CMTL::geo2d::Triangle<mpq_class> Tri2R;
typedef CMTL::geo3d::Point<double> Point3D;
typedef CMTL::geo3d::Point<mpq_class> Point3R;

using namespace CMTL;
using namespace CMTL::geometry_algorithm;

TEST(PredicateTest, Orient2dTest)
{
    Point2R p0(0, 0), p1(1, 1);
    EXPECT_TRUE(orient_2d(p0, p1, Point2R(1, 0)) == ORIENTATION::NEGATIVE);
    EXPECT_TRUE(orient_2d(p0, p1, Point2R(0, 1)) == ORIENTATION::POSITIVE);
    EXPECT_TRUE(orient_2d(p0, p1, Point2R(2, 2)) == ORIENTATION::ON);
}

TEST(PredicateTest, Orient3dTest)
{   
    Point3R p0(1, 0, 0), p1(0, 1, 0), p2(0, 0, 1);
    EXPECT_TRUE(orient_3d(p0, p1, p2, Point3R(1, 1, 1)) == ORIENTATION::NEGATIVE);
    EXPECT_TRUE(orient_3d(p0, p1, p2, Point3R(-1, -1, -1)) == ORIENTATION::POSITIVE);
    EXPECT_TRUE(orient_3d(p0, p1, p2, Point3R(mpq_class(1,10), mpq_class(3,10), mpq_class(3,5))) == ORIENTATION::ON);

    geo3d::Plane<mpq_class> plane(Point3R(0, 0, 0), Point3R(1, 1, 1));
    EXPECT_TRUE(orient_3d(plane, Point3R(1, 1, 1))==ORIENTATION::OUTSIDE);
    EXPECT_TRUE(orient_3d(plane, Point3R(-1, -1, -1))==ORIENTATION::INSIDE);
    EXPECT_TRUE(orient_3d(plane, Point3R(0, 0, 0))==ORIENTATION::ON);
}

TEST(PredicateTest, InCircleTest)
{
    Point2R p1(0, 0), p2(1, 0), p3(0, 1);
    EXPECT_TRUE(in_circle(p1, p2, p3, Point2R(1,1)) == ORIENTATION::ON);
    EXPECT_TRUE(in_circle(p1, p2, p3, Point2R(2,2)) == ORIENTATION::OUTSIDE);
    EXPECT_TRUE(in_circle(p1, p2, p3, Point2R(0.1,0.1)) == ORIENTATION::INSIDE);

    EXPECT_FALSE(in_circle(p1, p3, p2, Point2R(2,2)) == ORIENTATION::OUTSIDE);
    EXPECT_FALSE(in_circle(p1, p3, p2, Point2R(0.1,0.1)) == ORIENTATION::INSIDE);
}

TEST(PredicateTest, LocalDelaunayTest)
{
    Point2R p1(1, 0), p2(0, 1), p3(0, 0);
    EXPECT_TRUE(is_locally_delaunay(p1, p2, p3, Point2R(1, 1)));
    EXPECT_FALSE(is_locally_delaunay(p1, p2, p3, Point2R(1, 1), true));
    EXPECT_TRUE(is_locally_delaunay(p1, p2, p3, Point2R(2, 2)));
    EXPECT_FALSE(is_locally_delaunay(p1, p2, p3, Point2R(0.6, 0.6)));
}

TEST(PredicateTest, InTriangleTest)
{
    Tri2R tri(Point2R(0,0), Point2R(2,0), Point2R(1,1));
    EXPECT_TRUE(in_triangle(tri, Point2R(1, 0.5)) == ORIENTATION::INSIDE);
    EXPECT_TRUE(in_triangle(tri, Point2R(0, 0)) == ORIENTATION::ON);
    EXPECT_TRUE(in_triangle(tri, Point2R(2, 0)) == ORIENTATION::ON);
    EXPECT_TRUE(in_triangle(tri, Point2R(1, 1)) == ORIENTATION::ON);
    EXPECT_TRUE(in_triangle(tri, Point2R(1, 0)) == ORIENTATION::ON);
    EXPECT_TRUE(in_triangle(tri, Point2R(0.5, 0.5)) == ORIENTATION::ON);
    EXPECT_TRUE(in_triangle(tri, Point2R(1.5, 0.5)) == ORIENTATION::ON);
    EXPECT_TRUE(in_triangle(tri, Point2R(1, -0.1)) == ORIENTATION::OUTSIDE);
    EXPECT_TRUE(in_triangle(tri, Point2R(-0.1, -0.1)) == ORIENTATION::OUTSIDE);
    EXPECT_TRUE(in_triangle(tri, Point2R(1, 1.1)) == ORIENTATION::OUTSIDE);
}

// int main()
// {
// }


