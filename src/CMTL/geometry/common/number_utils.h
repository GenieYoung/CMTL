#ifndef __common_utils_h__
#define __common_utils_h__

#include "gmpxx.h"
#include <cmath>

namespace CMTL{
namespace geometry{

template<typename T>
inline double to_double(const T& v)
{
    return static_cast<double>(v);
}

template<>
inline double to_double<mpq_class>(const mpq_class& v)
{
    return v.get_d();
}

template<typename T>
inline T sqrt(const T& v)
{
    return T(std::sqrt(to_double(v)));
}

}   // namespace geometry
}   // namespace CMTL

#endif  // __common_utils_h__