#ifndef __common_utils_h__
#define __common_utils_h__

#include "gmpxx.h"
#include <cmath>

/**
 * @brief Computational Mathematics Tool Library
 */
namespace CMTL{

/* auxiliary class for number type conversion */
template<typename T_IN, typename T_OUT>
struct util_cast_impl
{
    static T_OUT cast(const T_IN& v)
    {
        return static_cast<T_OUT>(v);
    }
};

/* template specialization class, used for converting number type to string */
template<typename T_IN>
struct util_cast_impl<T_IN, std::string>
{
    static std::string cast(const T_IN& v)
    {
        return std::to_string(v);
    }
};

/**
 * @brief number type conversion function
 * @tparam T_IN input number type
 * @tparam T_OUT output number type
 */
template<typename T_IN, typename T_OUT>
inline T_OUT util_cast(const T_IN& v)
{
    return util_cast_impl<T_IN, T_OUT>::cast(v);
}

/* template specialization function, used for converting number type to double */
template<>
inline double util_cast<mpq_class, double>(const mpq_class& v)
{
    return v.get_d();
}

/* template specialization function, used for converting number type to string */
template<>
inline std::string util_cast<mpq_class, std::string>(const mpq_class& v)
{
    return v.get_str();
}

/**
 * @brief convert number to double type
 */
template<typename T>
inline double to_double(const T& v)
{
    return util_cast<T, double>(v);
}

/**
 * @brief convert number to string type
 */
template<typename T>
inline std::string to_string(const T& v)
{
    return util_cast<T, std::string>(v);
}

/**
 * @brief calculate the absolute value of a number
 */
template<typename T>
inline T absolute(const T& v)
{
    if(v > 0)   return v;
    else    return -v;
}

/**
 * @brief calculate the square root value of a number
 */
template<typename T>
inline T square_root(const T& v)
{
    return T(std::sqrt(to_double(v)));
}

}   // namespace CMTL

#endif  // __common_utils_h__