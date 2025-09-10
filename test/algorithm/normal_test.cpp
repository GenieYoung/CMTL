#include "CMTL/algorithm/normal.h"

#include "CMTL/geo2d/point.h"

typedef CMTL::geo3d::Point<double> PointF;

using namespace CMTL::algorithm;

void test1() {
  std::cout << "test1" << std::endl;
  std::cout << normal(PointF(0, 0, 0), PointF(2, 0, 0), PointF(0, 2, 0))
            << std::endl;
}

int main() { test1(); }