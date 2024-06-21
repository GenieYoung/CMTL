#include "CMTL/geometry/geo2d/geo2d_point.h"
#include "CMTL/geometry/geometry_process/normal.h"

typedef CMTL::geometry::geo3d::Point<double> PointF;

using namespace CMTL::geometry::geometry_process;

void test1()
{
    std::cout << "test1" << std::endl;
    std::cout << normal(PointF(0,0,0), PointF(2,0,0), PointF(0,2,0)) << std::endl;
}

int main()
{
    test1();
}