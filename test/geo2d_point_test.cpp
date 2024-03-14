#include "geo2d/geo2d_point.h"

int main()
{
    geo2d::PointT<double> p(0, 1);
    std::cout << p << std::endl;
    std::cout << p[0] << " " << p[1] << std::endl;
}