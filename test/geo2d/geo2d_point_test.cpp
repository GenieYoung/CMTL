#include "geo2d/geo2d_point.h"
#include <vector>

int main()
{
    CMTL::geo2d::Point<double> p(1, 2);
    CMTL::geo2d::Point<double> q(3, 4);
    std::cout << p << std::endl;
    std::cout << p*q << std::endl;
    std::cout << p%q << std::endl;

    std::vector<int> a;
    std::vector<int> b(a.begin(), a.end());
}