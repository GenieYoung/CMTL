#ifndef __common_utils_h__
#define __common_utils_h__

#include "gmpxx.h"

namespace CMTL{
namespace geometry{

typedef mpq_class rational;

template<typename T>
inline double to_double(const T& v)
{
    return static_cast<double>(v);
}

template<>
inline double to_double(const rational& v)
{
    return v.get_d();
}

}   // namespace geometry
}   // namespace CMTL

#endif  // __common_utils_h__