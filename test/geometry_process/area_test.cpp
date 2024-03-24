#include "geo2d/geo2d_polygon.h"
#include "geometry_process/area.h"

int main()
{
    std::vector<CMTL::geo2d::Point<double>> points;
    points.push_back(CMTL::geo2d::Point<double>{0,0});
    points.push_back(CMTL::geo2d::Point<double>{1,0});
    points.push_back(CMTL::geo2d::Point<double>{1,1});
    points.push_back(CMTL::geo2d::Point<double>{0,1});
    CMTL::geo2d::Polygon<double> polygon(points);
    std::cout << "area : " << CMTL::geometry_process::area(polygon) << std::endl;
    double area1;
    CMTL::geometry_process::area(points.begin(), points.end(), area1);
    std::cout << "area1 : " << area1 << std::endl;
}