#include "CMTL/geo2d/geo2d_point.h"
#include "CMTL/geometry_algorithm/normal.h"

typedef CMTL::geo3d::Point<double> PointF;

using namespace CMTL::geometry_algorithm;

void test1()
{
    std::cout << "test1" << std::endl;
    std::cout << normal(PointF(0,0,0), PointF(2,0,0), PointF(0,2,0)) << std::endl;
}

int main()
{
    test1();
}