#include "CMTL/geo3d/geo3d_plane.h"

void test1()
{
    CMTL::geo3d::Plane<double> plane(CMTL::geo3d::Point<double>(0, 0, 0), CMTL::geo3d::Point<double>(1, 0, 0));
    CMTL::geo3d::Point<double> p(0, 3, 3);
    std::cout << plane.project_2d(p) << std::endl;
    std::cout << plane.project_3d(plane.project_2d(p)) << std::endl;
    std::cout << plane.project_2d(plane.project_3d(plane.project_2d(p))) << std::endl;
    std::cout << plane.project_3d(plane.project_2d(plane.project_3d(plane.project_2d(p)))) << std::endl;

    std::cout << std::endl;

    CMTL::geo3d::Plane<double> plane2(CMTL::geo3d::Point<double>(0, 0, 0), CMTL::geo3d::Point<double>(1, 1, 1));
    CMTL::geo3d::Point<double> p2(2, -1, -1);
    std::cout << plane2.project_2d(p2) << std::endl;
    std::cout << plane2.project_3d(plane2.project_2d(p2)) << std::endl;
    std::cout << plane2.project_2d(plane2.project_3d(plane2.project_2d(p2))) << std::endl;
    std::cout << plane2.project_3d(plane2.project_2d(plane2.project_3d(plane2.project_2d(p2)))) << std::endl;
}

int main()
{
    test1();
    }