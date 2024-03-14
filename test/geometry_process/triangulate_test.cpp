#include <set>
#include "geo2d/geo2d_polygon.h"
#include "geometry_process/triangulate.h"

int main()
{
    std::vector<CMTL::geo2d::Point<double>> points;
    points.push_back(CMTL::geo2d::Point<double>{0,0});
    points.push_back(CMTL::geo2d::Point<double>{1,0});
    points.push_back(CMTL::geo2d::Point<double>{0,1});
    CMTL::geo2d::Polygon<double> polygon(points);
    std::vector<std::array<unsigned int, 3>> clip_triangles;
    CMTL::geometry_process::triangulate(polygon, clip_triangles);
}