#ifdef USE_CORE

#include "CORE/CORE.h"
#include "CMTL/geo2d/point.h"
#include "CMTL/algorithm/predicate.h"
#include <iostream>

typedef CORE::Expr FT;

template<typename T>
bool orient_robust_test(unsigned max_iter = 100) {
    CMTL::geo2d::Point<T> p0(0, 1);
    CMTL::geo2d::Point<T> p1(1, 0);
    CMTL::geo2d::Point<T> origin(0.5, 0.5);
    CMTL::geo2d::Point<T> offset(0.5, 0.5);
    CMTL::geo2d::Point<T> p2 = origin + offset;
    CMTL::geo2d::Point<T> last_p2;
    bool result = true;
    unsigned count = 0;
    for(; count < max_iter; ++count) {
        last_p2 = p2;
        CMTL::ORIENTATION check = CMTL::algorithm::orient_2d(p0, p1, p2);
        if(check != CMTL::ORIENTATION::POSITIVE) {
            result = false;
            break;
        }
        offset *= 0.5;
        p2 = origin + offset;
        if(p2 == last_p2) {
            result = false;
            break;
        }
    }
    // std::cout << result << " " << count << " " << offset << " " << p2 << std::endl;
    return result;
}

void test1() {
    FT sqrt2 = CMTL::sqrt(FT(2));
    FT sqrt3 = CMTL::sqrt(FT(3));
    FT sqrt6 = CMTL::sqrt(FT(6));
    FT expression = (sqrt2+sqrt3)*2;
    std::cout << ((sqrt2+sqrt3)*(sqrt2+sqrt3) == (5+2*sqrt6)) << " " <<
        ((std::sqrt(2)+std::sqrt(3))*(std::sqrt(2)+std::sqrt(3)) == (5+2*std::sqrt(6))) << std::endl; 
}

void test2() {
    orient_robust_test<FT>(100);
    orient_robust_test<double>(100);
}

int main() {
    test1();
    test2();
    return 0;
}
#else

int main() {
  return 0;
}

#endif