#include "CMTL/geo3d/geo3d_plane.h"

#include <cstdlib>
#include <gtest/gtest.h>

typedef CMTL::geo2d::Point<mpq_class> Point2R;
typedef CMTL::geo3d::Point<mpq_class> PointR;
typedef CMTL::geo3d::Plane<mpq_class> PlaneR;

TEST(PlaneTest, ConstructTest)
{
    PointR origin(1, 1, 1);
    PointR normal(1, 1, 1);
    PlaneR plane(origin, normal);
}

TEST(PlaneTest, ProjectTest)
{
    std::srand(42);
    PointR origin(1, 1, 1);
    PointR normal(1.1, 1.2, 1.3);
    PlaneR plane(origin, normal);
    for(unsigned i = 0; i < 100; ++i)
    {
        Point2R rp(rand()%10000/100.0 - 100, rand()%10000/100.0 - 100);
        Point2R rp2(rand()%10000/100.0 - 100, rand()%10000/100.0 - 100);
        EXPECT_EQ(plane.project_2d(plane.project_3d(rp)), rp);
        EXPECT_EQ(plane.project_3d(plane.project_2d(plane.project_3d(rp2))), plane.project_3d(rp2));
    }
}

TEST(PlaneTest, ComparatorTest)
{
    PointR origin(1, 1, 1);
    PointR normal(1.1, 1.2, 1.3);
    PlaneR plane1(origin, normal);
    PlaneR plane2(origin, -normal);
    EXPECT_TRUE(plane1.is_equal(plane2));
    EXPECT_FALSE(plane1.is_equal(plane2, true));
    EXPECT_TRUE(PlaneR::less_cmp_with_orientation(plane2, plane1));

    std::set<PlaneR> plane_set_not_consider_orientation;
    plane_set_not_consider_orientation.insert(plane1);
    plane_set_not_consider_orientation.insert(plane2);
    EXPECT_TRUE(plane_set_not_consider_orientation.size() == 1);
    EXPECT_TRUE(plane1.is_equal(*plane_set_not_consider_orientation.begin(), true));

    std::set<PlaneR, decltype(&PlaneR::less_cmp_with_orientation)> plane_set_consider_orientation(PlaneR::less_cmp_with_orientation);
    plane_set_consider_orientation.insert(plane1);
    plane_set_consider_orientation.insert(plane2);
    EXPECT_TRUE(plane_set_consider_orientation.size() == 2);
    EXPECT_TRUE(plane2.is_equal(*plane_set_consider_orientation.begin(), true));
    EXPECT_TRUE(plane1.is_equal(*(++plane_set_consider_orientation.begin()), true));
}

// void test1()
// {
//     CMTL::geo3d::Plane<double> plane(CMTL::geo3d::Point<double>(0, 0, 0), CMTL::geo3d::Point<double>(1, 0, 0));
//     CMTL::geo3d::Point<double> p(0, 3, 3);
//     std::cout << plane.project_2d(p) << std::endl;
//     std::cout << plane.project_3d(plane.project_2d(p)) << std::endl;
//     std::cout << plane.project_2d(plane.project_3d(plane.project_2d(p))) << std::endl;
//     std::cout << plane.project_3d(plane.project_2d(plane.project_3d(plane.project_2d(p)))) << std::endl;

//     std::cout << std::endl;

//     CMTL::geo3d::Plane<double> plane2(CMTL::geo3d::Point<double>(0, 0, 0), CMTL::geo3d::Point<double>(1, 1, 1));
//     CMTL::geo3d::Point<double> p2(2, -1, -1);
//     std::cout << plane2.project_2d(p2) << std::endl;
//     std::cout << plane2.project_3d(plane2.project_2d(p2)) << std::endl;
//     std::cout << plane2.project_2d(plane2.project_3d(plane2.project_2d(p2))) << std::endl;
//     std::cout << plane2.project_3d(plane2.project_2d(plane2.project_3d(plane2.project_2d(p2)))) << std::endl;
// }

// int main()
// {
//     //test1();
//     PointR origin(rand()%10000/100.0 - 100, rand()%10000/100.0 - 100, rand()%10000/100.0 - 100);
//     PointR below_point = origin + PointR(0, 0, double(rand()%100)/1e10);
//     std::cout << origin << std::endl;
//     std::cout << below_point << std::endl;
// }