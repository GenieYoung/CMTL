#include "CMTL/geo3d/polygon_soup.h"

void test1() {
  std::cout << "test1" << std::endl;
  std::vector<std::vector<double>> points;
  points.push_back({0, 0, 0});
  points.push_back({0, 0, 0});
  points.push_back({0, 0, 0});
  points.push_back({0, 0, 0});
  std::vector<std::vector<unsigned>> faces(4);
  CMTL::geo3d::PolygonSoup<float> polygon_soup(points, faces);
  std::cout << polygon_soup.n_points() << " " << polygon_soup.n_polygons()
            << std::endl;
  CMTL::geo3d::PolygonSoup<float> other_polygon_soup = polygon_soup;
  std::cout << other_polygon_soup.n_points() << " "
            << other_polygon_soup.n_polygons() << std::endl;
}

int main() { test1(); }