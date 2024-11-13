#include "CMTL/common/vectorT.h"

using namespace CMTL::geometry;

int main()
{
    Vec2d vd0;
    std::cout << vd0 << std::endl;

    Vec2d vd1(0, 1);     // specific constructor
    Vec2d vd2 = vd1;     // default constructor
    vd2.fill(10);
    std::cout << vd2 << std::endl;
    std::cout << Vec2d::Origin << std::endl;
    vd2 = vd1;    // default copy constructor

    Vec2f vf1(0);
    //Vec2f vf2 = vd1;    // call the copy constructor, but can not implicit convert from vec2d to vef2d
    Vec2f vf3(vd1);     // specific copy constructor
    vf3 = vd1;      // specific assign operator


    Vec1d v1d1(0);
    std::cout << vd0 << std::endl;
    Vec1d v1d2 = v1d1;  // specific constructor
    //Vec1f v1f1 = v1d1;    // call the specific constructor, wrong

    VecXT<double, 10> v10d(10);
    std::cout << v10d << std::endl;

    Vec3d v3d0(5, 9, 4);
    std::cout << v3d0.max().first << " " << v3d0.max().second << std::endl;
    Vec3d v3d1(5, -9, 4);
    std::cout << v3d1.max_abs().first << " " << v3d1.max_abs().second << std::endl;
    Vec3d v3d2(5, -9, 4);
    std::cout << v3d2.min_abs().first << " " << v3d2.min_abs().second << std::endl;
}