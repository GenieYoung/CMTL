#ifndef __common_utils_h__
#define __common_utils_h__

#include "gmpxx.h"
#include <cmath>

namespace CMTL{
namespace geometry{
    
template<typename T_IN, typename T_OUT>
inline T_OUT util_cast(const T_IN& v)
{
    return static_cast<T_OUT>(v);
}

template<>
inline double util_cast<mpq_class, double>(const mpq_class& v)
{
    return v.get_d();
}

template<typename T>
inline double to_double(const T& v)
{
    return util_cast<T, double>(v);
}

template<typename T>
inline T square_root(const T& v)
{
    return T(std::sqrt(to_double(v)));
}

}   // namespace geometry
}   // namespace CMTL

#endif  // __common_utils_h__