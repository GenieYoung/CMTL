#include "geo2d/geo2d_point.h"

int main()
{
    CMTL::geo2d::Point<double> p(1, 2);
    CMTL::geo2d::Point<double> q(3, 4);
    std::cout << p << std::endl;
    std::cout << p*q << std::endl;
    std::cout << p%q << std::endl;
}