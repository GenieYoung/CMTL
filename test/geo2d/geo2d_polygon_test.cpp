#include <set>
#include "geo2d/geo2d_polygon.h"

int main()
{
    std::set<CMTL::geo2d::Point<double>> points;
    points.insert(CMTL::geo2d::Point<double>{0,0});
    points.insert(CMTL::geo2d::Point<double>{1,1});
    CMTL::geo2d::Polygon<double> polygon(points.begin(), points.end());
    std::cout << polygon << std::endl;
}