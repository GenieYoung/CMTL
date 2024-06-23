#include "CMTL/geometry/common/vectorT.h"

using namespace CMTL::geometry;

int main()
{
    Vec2d vd0;
    std::cout << vd0 << std::endl;

    Vec2d vd1(0, 1);     // specific constructor
    Vec2d vd2 = vd1;     // default constructor
    vd2 = vd1;    // default copy constructor

    Vec2f vf1(0, 1);
    //Vec2f vf2 = vd1;    // call the copy constructor, but can not implicit convert from vec2d to vef2d
    Vec2f vf3(vd1);     // specific copy constructor
    vf3 = vd1;      // specific assign operator


    Vec1d v1d1;
    Vec1d v1d2 = v1d1;  // specific constructor
    //Vec1f v1f1 = v1d1;    // call the specific constructor, wrong
}