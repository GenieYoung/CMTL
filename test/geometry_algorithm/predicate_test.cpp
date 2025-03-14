#include "CMTL/geometry_algorithm/predicate.h"

#include <gtest/gtest.h>

typedef CMTL::geo2d::Point<double> Point2D;
typedef CMTL::geo2d::Point<mpq_class> Point2R;
typedef CMTL::geo3d::Point<double> Point3D;
typedef CMTL::geo3d::Point<mpq_class> Point3R;

using namespace CMTL;
using namespace CMTL::geometry_algorithm;

TEST(PredicateTest, Orient2dTest)
{
    Point2D pd1(0, 0), pd2(1, 6);
    EXPECT_TRUE(orient_2d(pd1, pd2, {0.5, 3+1e-10})==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_2d(pd1, pd2, {0.5, 3-1e-10})==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_2d(pd1, pd2, {0.5, 3})==ORIENTATION::ON);
    
    double d1[2] = {0, 0};
    double d2[2] = {1, 6};
    double d3[2] = {0.5, 3+1e10};
    double d4[2] = {0.5, 3-1e10};
    double d5[2] = {0.5, 3};
    EXPECT_TRUE(orient_2d(d1, d2, d3)==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_2d(d1, d2, d4)==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_2d(d1, d2, d5)==ORIENTATION::ON);


    Point2R pr1(0, 0), pr2(1, 6);
    EXPECT_TRUE(orient_2d(pr1, pr2, {0.5, mpq_class(1, 1e100)+3})==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_2d(pr1, pr2, {0.5, -mpq_class(1, 1e100)+3})==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_2d(pr1, pr2, {0.5, 3})==ORIENTATION::ON);

    mpq_class r1[2] = {0, 0};
    mpq_class r2[2] = {1, 6};
    mpq_class r3[2] = {0.5, mpq_class(1, 1e100) + 3};
    mpq_class r4[2] = {0.5, -mpq_class(1, 1e100) + 3};
    mpq_class r5[2] = {0.5, 3};
    EXPECT_TRUE(orient_2d(r1, r2, r3)==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_2d(r1, r2, r4)==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_2d(r1, r2, r5)==ORIENTATION::ON);
}

TEST(PredicateTest, Orient3dTest)
{
    Point3D pd1(0, 1, 0), pd2(0, 0, 0), pd3(3, 0, 7);
    EXPECT_TRUE(orient_3d(pd1, pd2, pd3, {1.5, 0.5, 3.5+1e-10})==ORIENTATION::POSITIVE);
    EXPECT_TRUE(orient_3d(pd1, pd2, pd3, {1.5, -0.5, 3.5-1e-10})==ORIENTATION::NEGATIVE);
    EXPECT_TRUE(orient_3d(pd1, pd2, pd3, {1.5, 0, 3.5})==ORIENTATION::ON);
    
    double d1[3] = {0, 1, 0};
    double d2[3] = {0, 0, 0};
    double d3[3] = {3, 0, 7};
    double d4[3] = {1.5, 0.5, 3.5+1e10};
    double d5[3] = {1.5, -0.5, 3.5-1e10};
    double d6[3] = {1.5, 0, 3.5};
    EXPECT_TRUE(orient_3d(d1, d2, d3, d4)==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_3d(d1, d2, d3, d5)==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_3d(d1, d2, d3, d6)==ORIENTATION::ON);

    Point3R pr1(0, 1, 0), pr2(0, 0, 0), pr3(3, 0, 7);
    EXPECT_TRUE(orient_3d(pr1, pr2, pr3, {1.5, 0.5, mpq_class(1, 1e100)+3.5})==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_3d(pr1, pr2, pr3, {1.5, -0.5, -mpq_class(1, 1e100)+3.5})==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_3d(pr1, pr2, pr3, {1.5, 0, 3.5})==ORIENTATION::ON);

    mpq_class r1[3] = {0, 1, 0};
    mpq_class r2[3] = {0, 0, 0};
    mpq_class r3[3] = {3, 0, 7};
    mpq_class r4[3] = {1.5, 0.5, mpq_class(1, 1e100)+3.5};
    mpq_class r5[3] = {1.5, -0.5, -mpq_class(1, 1e100)+3.5};
    mpq_class r6[3] = {1.5, 0, 3.5};
    EXPECT_TRUE(orient_3d(r1, r2, r3, r4)==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_3d(r1, r2, r3, r5)==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_3d(r1, r2, r3, r6)==ORIENTATION::ON);

    geo3d::Plane<mpq_class> plane(Point3R(0, 0, 0), Point3R(1, 1, 1));
    EXPECT_TRUE(orient_3d(plane, Point3R(1, 1, 1))==ORIENTATION::ABOVE);
    EXPECT_TRUE(orient_3d(plane, Point3R(-1, -1, -1))==ORIENTATION::BELOW);
    EXPECT_TRUE(orient_3d(plane, Point3R(0, 0, 0))==ORIENTATION::ON);
}

TEST(PredicateTest, LocalDelaunayTest)
{
    Point2D pd1(1, 0), pd2(0, 1), pd3(0, 0), pd4(1, 1);
    EXPECT_TRUE(is_locally_delaunay(pd1, pd2, pd3, pd4));
    EXPECT_TRUE(is_locally_delaunay(pd1, pd2, pd3, pd4+Point2D(1e-10, 1e-10)));
    EXPECT_FALSE(is_locally_delaunay(pd1, pd2, pd3, pd4-Point2D(1e-10, 1e-10)));

    double d1[2] = {1, 0};
    double d2[2] = {0, 1};
    double d3[2] = {0, 0};
    double d4[2] = {1, 1};
    double d5[2] = {1+1e-10, 1+1e-10};
    double d6[2] = {1-1e-10, 1-1e-10};
    EXPECT_TRUE(is_locally_delaunay(d1, d2, d3, d4));
    EXPECT_TRUE(is_locally_delaunay(d1, d2, d3, d5));
    EXPECT_FALSE(is_locally_delaunay(d1, d2, d3, d6));

    Point2R pr1(1, 0), pr2(0, 1), pr3(0, 0), pr4(1, 1);
    EXPECT_TRUE(is_locally_delaunay(pr1, pr2, pr3, pr4));
    EXPECT_FALSE(is_locally_delaunay(pr1, pr2, pr3, pr4, true));
    EXPECT_TRUE(is_locally_delaunay(pr1, pr2, pr3, pr4+Point2D(mpq_class(1,1e100), mpq_class(1,1e100))));
    EXPECT_FALSE(is_locally_delaunay(pr1, pr2, pr3, pr4-Point2D(mpq_class(1,1e100), mpq_class(1,1e100))));
}

// int main()
// {
// }


