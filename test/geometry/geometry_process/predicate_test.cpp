#include "CMTL/geometry/geo2d/geo2d_point.h"
#include "CMTL/geometry/geo3d/geo3d_point.h"
#include "CMTL/geometry/geometry_process/predicate.h"


void orient2d_test()
{
    typedef CMTL::geometry::geo2d::Point<double> PointF;
    PointF p1(0,0), p2(1,0), p3(0.5, -0.00001);
    std::cout << p1 << " " << p2 << " " << p3 << " "
              << CMTL::geometry::geometry_process::orient_2d(p1, p2, p3) << std::endl;
}

void orient3d_test()
{
    typedef CMTL::geometry::geo3d::Point<double> PointF;
    PointF p1(0,0,0), p2(1,0,1), p3(0,1,0), p4(0.5, 0.5, 0.500001);
    std::cout << p1 << " " << p2 << " " << p3 << " " << p4 << " "
              << CMTL::geometry::geometry_process::orient_3d(p1, p2, p3, p4) << std::endl;
}

void locally_delaunay_test()
{
    typedef CMTL::geometry::geo2d::Point<double> PointF;
    PointF p1(-2.88,-5.32), p2(-2.72,-5.67), p3(-2.70, -5.37), p4(-2.67, -6.03);
    //PointF p1(0,0), p2(10,0), p3(5, 5), p4(5, -4);
    std::cout << p1 << " " << p2 << " " << p3 << " " << p4 << " "
              << (CMTL::geometry::geometry_process::is_locally_delaunay(p1, p2, p3, p4) ? "delaunay" : "not delaunay") << std::endl;
}

int main()
{
    orient2d_test();
    orient3d_test();
    locally_delaunay_test();
}


