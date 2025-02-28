#include "CMTL/common/vectorT.h"
#include <gtest/gtest.h>

using namespace CMTL;

TEST(VectorTest, ConstructTest)
{
    Vec2d v2d_0;
    EXPECT_EQ(v2d_0.dimension(), 2);
    EXPECT_DEATH({v2d_0[2];}, "index out of range");
    EXPECT_EQ(v2d_0[0], 0);
    EXPECT_EQ(v2d_0[1], 0);

    EXPECT_EQ(Vec2d::Origin[0], 0);
    EXPECT_EQ(Vec2d::Origin[1], 0);

    v2d_0.fill(1);
    EXPECT_EQ(v2d_0[0], 1);
    EXPECT_EQ(v2d_0[1], 1);

    Vec2d v2d_1(0, mpq_class(1,2));
    EXPECT_EQ(v2d_1[0], 0);
    EXPECT_EQ(v2d_1[1], 0.5);

    Vec2i v2i_0(1.5, -0.5);
    EXPECT_EQ(v2i_0[0], 1);
    EXPECT_EQ(v2i_0[1], 0);

    v2d_1 = v2d_0;
    EXPECT_EQ(v2d_1, v2d_0);

    v2d_1 = Vec3d(1, 2, 3);
    EXPECT_EQ(v2d_1[0], 1);
    EXPECT_EQ(v2d_1[1], 2);
    EXPECT_EQ(v2d_1.dimension(), 2);
    
    Vec2d v2d_2(VecXT<mpq_class, 2>(mpq_class(1,3), mpq_class(1,2)));
    EXPECT_DOUBLE_EQ(v2d_2[0], 1/3.0);
    EXPECT_EQ(v2d_2[1], 0.5);

    Vec2d v2d_3({0, mpq_class(1,2)});
    EXPECT_EQ(v2d_3[0], 0);
    EXPECT_EQ(v2d_3[1], 0.5);

    Vec3d v3d_0(2, 3, 4);
    v3d_0 = Vec2d(1, 2);
    EXPECT_EQ(v3d_0[0], 1);
    EXPECT_EQ(v3d_0[1], 2);
    EXPECT_EQ(v3d_0[2], 4);
}

TEST(VectorTest, OperationTest)
{
    Vec2d v2d_0(0.5, -1.5);
    Vec2i v2i_0(1, 1);
    EXPECT_EQ(v2d_0, Vec2d(0.5, -1.5));
    EXPECT_EQ(v2i_0, Vec2i(1.1, 1.9));
    EXPECT_NE(v2d_0, Vec2d(0.5, 1.5));
    EXPECT_NE(v2i_0, Vec2i(0.9, 2.1));
    EXPECT_EQ(v2d_0+v2i_0, Vec2d(1.5, -0.5));
    EXPECT_EQ(v2i_0+v2d_0, Vec2i(1, 0));
    EXPECT_EQ(v2d_0-v2i_0, Vec2d(-0.5, -2.5));
    EXPECT_EQ(v2i_0-v2d_0, Vec2i(1, 2));
    EXPECT_EQ(v2d_0*v2i_0, -1);
    EXPECT_EQ(v2i_0*v2d_0, -1);
    EXPECT_EQ(v2d_0*2, Vec2d(1, -3));
    EXPECT_EQ(v2i_0*2.5, Vec2i(2, 2));
    EXPECT_EQ(v2d_0/2.0, Vec2d(0.25, -0.75));
    EXPECT_EQ(v2i_0/1.5, Vec2i(1, 1));
    
    EXPECT_TRUE(v2d_0 < Vec2d(0.6, -1.5));
    EXPECT_TRUE(v2i_0 < Vec2i(2.1, 0.9));

    EXPECT_EQ(*v2d_0.data(), 0.5);
    EXPECT_EQ(v2d_0.data()[1], -1.5);

    VecXT<double, 5> v5d_0(0.2, 0.1, -0.1, 0.3, 0);
    std::sort(v5d_0.data(), v5d_0.data()+v5d_0.size());
    EXPECT_EQ(v5d_0, (VecXT<double, 5>(-0.1, 0, 0.1, 0.2, 0.3)));

    VecXT<double, 10> v10d_0(0.2, 0.1, -0.4, 0.3, 0.4, 0.3, 0, 0.1, -0.4, 0);
    EXPECT_EQ(v10d_0.max(), 4);
    EXPECT_EQ(v10d_0.min(), 2);
    EXPECT_EQ(v10d_0.max_abs(), 2);
    EXPECT_EQ(v10d_0.min_abs(), 6);

    EXPECT_EQ(v2d_0.norm_square(), 2.5);
}

// int main()
// {
//     Vec2d vd0;
//     std::cout << vd0 << std::endl;

//     Vec2d vd1(0, 1);     // specific constructor
//     Vec2d vd2 = vd1;     // default constructor
//     vd2.fill(10);
//     std::cout << vd2 << std::endl;
//     std::cout << Vec2d::Origin << std::endl;
//     vd2 = vd1;    // assign operator

//     Vec2f vf1(0);
//     //Vec2f vf2 = vd1;    // call the copy constructor, but can not implicit convert from vec2d to vef2d
//     Vec2f vf3(vd1);     // specific copy constructor
//     vf3 = vd1;      // specific assign operator


//     Vec1d v1d1(0);
//     std::cout << vd0 << std::endl;
//     Vec1d v1d2 = v1d1;  // specific constructor
//     //Vec1f v1f1 = v1d1;    // call the specific constructor, wrong

//     VecXT<double, 10> v10d(10);
//     std::cout << v10d << std::endl;

//     Vec3d v3d0(5, 9, 4);
//     std::cout << v3d0.max().first << " " << v3d0.max().second << std::endl;
//     Vec3d v3d1(5, -9, 4);
//     std::cout << v3d1.max_abs().first << " " << v3d1.max_abs().second << std::endl;
//     Vec3d v3d2(5, -9, 4);
//     std::cout << v3d2.min_abs().first << " " << v3d2.min_abs().second << std::endl;

//     Vec3d v3d3(Vec2d(1,2));
//     std::cout << v3d3 << std::endl;
// }