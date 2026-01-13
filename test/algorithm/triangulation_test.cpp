#include "CMTL/algorithm/triangulation.h"

#include "CMTL/io/triangulation/write_obj.h"

#include <iostream>

void test1() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  pslg._points = std::vector<Point>{{-1, 0}, {1, 0}, {0, 0.5}, {0, 1}};
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "triangulation_test1.obj");
}

void test2() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  for (unsigned i = 0; i < 10; ++i)
    pslg._points.emplace_back(std::cos(i * 2.0 * M_PI / 10.0),
                              std::sin(i * 2.0 * M_PI / 10.0));
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "triangulation_test2.obj");
}

void test3() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  unsigned n = 10;
  for (unsigned i = 0; i <= n; ++i) {
    pslg._points.emplace_back(2.0 * i / n - 1, -1);
    pslg._points.emplace_back(2.0 * i / n - 1, 1);
  }
  for (unsigned i = 1; i < n; ++i) {
    pslg._points.emplace_back(-1, 2.0 * i / n - 1);
    pslg._points.emplace_back(1, 2.0 * i / n - 1);
  }
  for (unsigned i = 1; i < n; ++i) {
    for (unsigned j = 1; j < n; ++j) {
      pslg._points.emplace_back(2.0 * i / n - 1, 2.0 * j / n - 1);
    }
  }
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "triangulation_test3.obj");
}

void test4() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  unsigned n = 100;
  pslg._points.reserve(n);
  for (unsigned i = 0; i < n; ++i) {
    pslg._points.emplace_back(rand() % 20000 / 10000.0 - 1,
                              rand() % 20000 / 10000.0 - 1);
  }
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "triangulation_test4.obj");
}

void test5() {
  typedef CMTL::geo2d::Point<double> Point;
  CMTL::geo2d::PSLG<double> pslg;
  pslg._points = std::vector<Point>{{-1, 0},  {-1, 0}, {0, 0}, {1, 0},
                                    {0, 0.5}, {0, 1},  {0, 0}};
  CMTL::algorithm::Triangulation<double> T(pslg);
  CMTL::io::write_obj(T, "triangulation_test5.obj");
}

int main() {
  srand(42); 

  test1();
  test2();
  test3();
  test4();
  test5();
  return 0;
}