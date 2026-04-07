#include "CMTL/geo3d/point.h"

#include <gtest/gtest.h>

typedef CMTL::geo3d::Point<int> PointI;
typedef CMTL::geo3d::Point<double> PointF;
#ifdef USE_GMP
typedef CMTL::geo3d::Point<mpq_class> PointR;
#endif

TEST(Point3Test, ConstructTest) {
  EXPECT_EQ(PointI::dimension(), 3);

  EXPECT_EQ(PointI::Origin.x(), 0);
  EXPECT_EQ(PointI::Origin.y(), 0);
  EXPECT_EQ(PointI::Origin.z(), 0);

  PointI pi0(1);
  EXPECT_EQ(pi0.x(), 1);
  EXPECT_EQ(pi0.y(), 1);
  EXPECT_EQ(pi0.z(), 1);

  PointI pi1(1, -1, 0);
  EXPECT_EQ(pi1.x(), 1);
  EXPECT_EQ(pi1.y(), -1);
  EXPECT_EQ(pi1.z(), 0);

  PointI pi2({1, -1, 0});
  EXPECT_EQ(pi2.x(), 1);
  EXPECT_EQ(pi2.y(), -1);
  EXPECT_EQ(pi2.z(), 0);
}

TEST(Point3Test, OperationTest) {
  PointF pf_cross_0(1, 2, 3);
  PointF pf_cross_1(4, 5, 6);
  EXPECT_EQ(pf_cross_0 % pf_cross_1, PointF(-3, 6, -3));
#ifdef USE_GMP
  PointR pr_cross_0(mpq_class(1, 3), mpq_class(-2, 7), 1);
  PointR pr_cross_1(mpq_class(3, 7), mpq_class(2, 9), 0.5);
  EXPECT_EQ(
      pr_cross_0 % pr_cross_1,
      PointR(mpq_class(-23, 63), mpq_class(11, 42), mpq_class(260, 1323)));
#endif
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