#include "CMTL/algorithm/triangulation.h"

#include <iostream>

int main() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  pslg._points = {Point(0, 0), Point(0, 1), Point(1, 0)};
  CMTL::algorithm::Triangulation<double> T(pslg);
}