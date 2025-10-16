#include "CMTL/algorithm/triangulation.h"

#include "CMTL/io/triangulation/write_obj.h"

#include <iostream>

int main() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  pslg._points = {Point(0, 0), Point(0, 1), Point(1, 0), Point(1,1)};
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "test.obj");
  return 0;
}