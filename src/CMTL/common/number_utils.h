#ifndef __common_utils_h__
#define __common_utils_h__

#include "gmpxx.h"
#include <cmath>

namespace CMTL{

template<typename T_IN, typename T_OUT>
struct util_cast_impl
{
    static T_OUT cast(const T_IN& v)
    {
        return static_cast<T_OUT>(v);
    }
};

template<typename T_IN>
struct util_cast_impl<T_IN, std::string>
{
    static std::string cast(const T_IN& v)
    {
        return std::to_string(v);
    }
};
    
template<typename T_IN, typename T_OUT>
inline T_OUT util_cast(const T_IN& v)
{
    return util_cast_impl<T_IN, T_OUT>::cast(v);
}

template<>
inline double util_cast<mpq_class, double>(const mpq_class& v)
{
    return v.get_d();
}

template<>
inline std::string util_cast<mpq_class, std::string>(const mpq_class& v)
{
    return v.get_str();
}

template<typename T>
inline double to_double(const T& v)
{
    return util_cast<T, double>(v);
}

template<typename T>
inline std::string to_string(const T& v)
{
    return util_cast<T, std::string>(v);
}

template<typename T>
inline T absolute(const T& v)
{
    if(v > 0)   return v;
    else    return -v;
}

template<typename T>
inline T square_root(const T& v)
{
    return T(std::sqrt(to_double(v)));
}

}   // namespace CMTL

#endif  // __common_utils_h__