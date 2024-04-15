#include "CMTL/geometry/geo2d/geo2d_point.h"
#include "CMTL/geometry/geometry_process/area.h"

void test1()
{
    std::cout << "test1" << std::endl;
    std::vector<CMTL::geometry::geo2d::Point<double>> points;
    points.push_back(CMTL::geometry::geo2d::Point<double>{0,0});
    points.push_back(CMTL::geometry::geo2d::Point<double>{1,0});
    points.push_back(CMTL::geometry::geo2d::Point<double>{1,1});
    points.push_back(CMTL::geometry::geo2d::Point<double>{0,1});
    CMTL::geometry::geo2d::Polygon<double> polygon(points);
    std::cout << "area : " << CMTL::geometry::geometry_process::area(polygon) << std::endl;
    double area1;
    CMTL::geometry::geometry_process::area_2d(points.begin(), points.end(), area1);
    std::cout << "area1 : " << area1 << std::endl;
    double area2;
    CMTL::geometry::geometry_process::area_2d(points, area2);
    std::cout << "area2 : " << area2 << std::endl;
}

int main()
{
    test1();
    }