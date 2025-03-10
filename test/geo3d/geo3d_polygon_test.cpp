#include <set>
#include "CMTL/geo3d/geo3d_polygon.h"

void test1()
{
    std::vector<CMTL::geo3d::Point<double>> points;
    points.push_back(CMTL::geo3d::Point<double>{0,0,0});
    points.push_back(CMTL::geo3d::Point<double>{1,0,1});
    points.push_back(CMTL::geo3d::Point<double>{1,1,1});
    points.push_back(CMTL::geo3d::Point<double>{0,1,0});
    CMTL::geo3d::Polygon<double> polygon(points.begin(), points.end());
    std::cout << polygon << std::endl;
    std::cout << "area2 : " << polygon.area2() << std::endl;
    std::cout << "normal : " << polygon.normal() << std::endl;
}

int main()
{
    test1();
}