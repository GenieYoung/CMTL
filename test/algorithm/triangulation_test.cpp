#include "CMTL/algorithm/triangulation.h"

#include "CMTL/io/triangulation/write_obj.h"

#include <iostream>

void test1() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  for(unsigned i = 0; i < 10; ++i)
    pslg._points.emplace_back(std::cos(i * 2.0 * M_PI / 10.0),
                              std::sin(i * 2.0 * M_PI / 10.0));
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "triangulation_test1.obj");
}

void test2() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  unsigned n = 10;
  for(unsigned i = 0; i < n; ++i) {
    pslg._points.emplace_back(i, 0);
    pslg._points.emplace_back(i, n-1);
  }
  for(unsigned i = 1; i < n-1; ++i) {
    pslg._points.emplace_back(0, i);
    pslg._points.emplace_back(n-1, i);
  }
  for(unsigned i = 1; i < n-1; ++i){
    for(unsigned j = 1; j < n-1; ++j){
      pslg._points.emplace_back(i, j);
    }
  }
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "triangulation_test2.obj");
}

int main() {
  test1();
  test2();
  return 0;
}