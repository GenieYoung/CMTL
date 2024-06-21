#include "CMTL/geometry/geo3d/geo3d_point.h"
#include <vector>

int main()
{
    CMTL::geometry::geo3d::Point<double> p(1, 2, 3);
    CMTL::geometry::geo3d::Point<double> q(3, 4, 5);
    CMTL::geometry::geo3d::Point<mpq_class> rp(5, 6, 7);

    // operator test
    std::cout << p << std::endl;
    std::cout << p*q << std::endl;
    std::cout << p%q << std::endl;
    std::cout << p/2 << std::endl;
}