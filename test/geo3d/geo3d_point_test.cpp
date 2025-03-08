#include "CMTL/geo3d/geo3d_point.h"
#include <gtest/gtest.h>

typedef CMTL::geo3d::Point<int> PointI;
typedef CMTL::geo3d::Point<double> PointF;
typedef CMTL::geo3d::Point<mpq_class> PointR;

TEST(Point3Test, ConstructTest)
{
    PointI pi0(1, 2);
    EXPECT_EQ(pi0.dimension(), 3);
    //EXPECT_DEATH({pi0[3];}, "index out of range");
    EXPECT_EQ(pi0.x(), 1);
    EXPECT_EQ(pi0.y(), 2);
    EXPECT_EQ(pi0.z(), 0);

    EXPECT_EQ(PointI::Origin.x(), 0);
    EXPECT_EQ(PointI::Origin.y(), 0);
    EXPECT_EQ(PointI::Origin.z(), 0);

    PointI pi1(PointI(1, -1));
    EXPECT_EQ(pi1.x(), 1);
    EXPECT_EQ(pi1.y(), -1);
    EXPECT_EQ(pi1.z(), 0);

    PointI pi2(PointF(-1.5, 1.5));
    EXPECT_EQ(pi2.x(), -1);
    EXPECT_EQ(pi2.y(), 1);
    EXPECT_EQ(pi2.z(), 0);

    int v1[3] = {1, 2, 3};
    PointI pi3(v1);
    EXPECT_EQ(pi3.x(), 1);
    EXPECT_EQ(pi3.y(), 2);
    EXPECT_EQ(pi3.z(), 3);
}

TEST(Point3Test, OperationTest)
{
    PointR pr0(mpq_class(1, 3), mpq_class(-2, 7), 1);
    PointR pr1(mpq_class(3, 7), mpq_class(2, 9), 0.5);
    PointF cross(pr0%pr1);
    EXPECT_DOUBLE_EQ(cross.x(), -23/63.0);
    EXPECT_DOUBLE_EQ(cross.y(), 11/42.0);
    EXPECT_DOUBLE_EQ(cross.z(), 260/1323.0);
}

// int main()
// {
//     CMTL::geo3d::Point<double> p(1, 2, 3);
//     CMTL::geo3d::Point<double> q(3, 4, 5);
//     CMTL::geo3d::Point<mpq_class> rp(5, 6, 7);

//     // operator test
//     std::cout << p << std::endl;
//     std::cout << p*q << std::endl;
//     std::cout << p%q << std::endl;
//     std::cout << p/2 << std::endl;
// }