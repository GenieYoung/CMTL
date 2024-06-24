#include "CMTL/geometry/geo2d/geo2d_point.h"
#include <vector>

int main()
{
    CMTL::geometry::geo2d::Point<double> origin;
    CMTL::geometry::geo2d::Point<double> p(1);
    CMTL::geometry::geo2d::Point<double> q(p);
    std::cout << "origin :      " << CMTL::geometry::geo2d::Point<double>::Origin << std::endl;
    std::cout << "origin :      " << origin << std::endl;
    std::cout << "p :           " << p << std::endl;
    std::cout << "q :           " << q << std::endl;
    std::cout << "assign :      " << (p=q) << std::endl;
    std::cout << "p add q :     " << (p+q) << std::endl;
    std::cout << "p cross q :   " << (p%q) << std::endl;
    std::cout << "p norm2 :     " << p.length_square() << std::endl;
    std::cout << "p == q :      " << (p==q) << std::endl;

    CMTL::geometry::geo2d::Point<mpq_class> r_origin(origin);
    CMTL::geometry::geo2d::Point<mpq_class> rp(5, 6);
    CMTL::geometry::geo2d::Point<mpq_class> rq(q);
    std::cout << "rorigin :     " << r_origin << std::endl;
    std::cout << "rp :          " << rp << std::endl;
    std::cout << "rq :          " << rq << std::endl;
    std::cout << "rp assign p : " << (p = rp) << std::endl;
}