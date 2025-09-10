#include <set>
#include "CMTL/geo2d/polygon.h"

void test1()
{
    std::cout << "test1" << std::endl;
    std::set<CMTL::geo2d::Point<double>> points;
    points.insert(CMTL::geo2d::Point<double>{0,0});
    points.insert(CMTL::geo2d::Point<double>{1,0});
    points.insert(CMTL::geo2d::Point<double>{1,2});
    points.insert(CMTL::geo2d::Point<double>{0,2});
    CMTL::geo2d::Polygon<double> polygon(points.begin(), points.end());
    std::cout << polygon << std::endl;
}

void test2()
{
    std::cout << "test2" << std::endl;
    std::vector<CMTL::geo2d::Point<double>> points;
    points.push_back(CMTL::geo2d::Point<double>{0,0});
    points.push_back(CMTL::geo2d::Point<double>{1,0});
    points.push_back(CMTL::geo2d::Point<double>{1,2});
    points.push_back(CMTL::geo2d::Point<double>{0,2});
    CMTL::geo2d::Polygon<double> polygon(points.begin(), points.end());
    std::cout << polygon << std::endl;
    std::cout << "area : " << polygon.area() << std::endl;
}

int main()
{
    test1();
    test2();
}