#include "CMTL/geometry/geo3d/geo3d_polygon_soup.h"

void test1()
{
    std::cout << "test1" << std::endl;
    std::vector<std::vector<double>> points;
    points.push_back({0, 0, 0});
    points.push_back({0, 0, 0});
    points.push_back({0, 0, 0});
    points.push_back({0, 0, 0});
    std::vector<std::vector<unsigned>> faces(4);
    CMTL::geometry::geo3d::PolygonSoup<float> polygon_soup(points, faces);
    std::cout << polygon_soup.n_points() << " " << polygon_soup.n_faces() << std::endl;
    CMTL::geometry::geo3d::PolygonSoup<float> other_polygon_soup = polygon_soup;
    std::cout << other_polygon_soup.n_points() << " " << other_polygon_soup.n_faces() << std::endl;
}

int main()
{
    test1();
}