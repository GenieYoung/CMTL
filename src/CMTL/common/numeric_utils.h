#ifndef __common_utils_h__
#define __common_utils_h__

#include "gmpxx.h"
#include <cmath>
#include <type_traits>

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
 * @note if the number type is from gmp, absolute(expression) may crash, call absolute(T(expression)) instead.
 */
template<typename T>
inline T absolute(const T& v)
{
    if(v >= 0)   
        return v;
    return -v;
}

/**
 * @brief calculate the minimal value of two numbers
 */
template<typename T>
inline T min(const T& v1, const T& v2)
{
    if(v1 < v2)
        return v1;
    return v2;
}

/**
 * @brief calculate the minimal value of two numbers
 */
template<typename T>
inline T max(const T& v1, const T& v2)
{
    if(v1 > v2)
        return v1;
    return v2;
}

/**
 * @brief calculate the square root value of a number
 */
template<typename T>
inline T square_root(const T& v)
{
    return T(std::sqrt(to_double(v)));
}

template<typename T, typename = void>
class numeric_comparator
{
    public:
        static T tolerance()
        {
            return T(0);
        }

        static bool is_equal(const T& v1, const T& v2, const T& tol = T(0))
        {
            return v1 == v2;
        }

        static bool is_not_equal(const T& v1, const T& v2, const T& tol = T(0))
        {
            return !(is_equal(v1, v2, tol));
        }

        static bool is_less(const T& v1, const T& v2, const T& tol = T(0))
        {
            return v1 < v2;
        }

        static bool is_less_equal(const T& v1, const T& v2, const T& tol = T(0))
        {
            return v1 <= v2;
        }

        static bool is_greater(const T& v1, const T& v2, const T& tol = T(0))
        {
            return v1 > v2;
        }

        static bool is_greater_equal(const T& v1, const T& v2, const T& tol = T(0))
        {
            return v1 >= v2;
        }
};

template<typename T>
class numeric_comparator<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    public:
        static T& tolerance()
        {
            return _tol;
        }

        static bool is_equal(const T& v1, const T& v2, const T& tol = _tol)
        {
            return absolute(v1 - v2) <= _tol;
        }

        static bool is_not_equal(const T& v1, const T& v2, const T& tol = _tol)
        {
            return !(is_equal(v1, v2, tol));
        }

        static bool is_zero(const T& v, const T& tol = _tol)
        {
            return is_equal(v, T(0), _tol);
        }

        static bool is_less(const T& v1, const T& v2, const T& tol = _tol)
        {
            return v1 < v2 - tol;
        }

        static bool is_less_equal(const T& v1, const T& v2, const T& tol = _tol)
        {
            return v1 <= v2 + tol;
        }

        static bool is_greater(const T& v1, const T& v2, const T& tol = _tol)
        {
            return v1 > v2 + tol;
        }

        static bool is_greater_equal(const T& v1, const T& v2, const T& tol = _tol)
        {
            return v1 >= v2 - tol;
        }


    private:
        static T _tol;
};

constexpr float default_float_tolerance = 1e-5;
constexpr double default_double_tolerance = 1e-13;

template<>
float numeric_comparator<float>::_tol = default_float_tolerance;

template<>
double numeric_comparator<double>::_tol = default_double_tolerance;

template<typename T>
T numeric_comparator<T, typename std::enable_if<
            std::is_floating_point<T>::value>::type>::_tol 
                    = std::numeric_limits<T>::epsilon();

/**
 * @brief check whether two number are equal
 * @param tolerance tolerance that prevents the floating point error
 * @note if the number type is from gmp, it should be in canonical form!
 */
template<typename T>
bool is_equal(const T& v1, const T& v2, const T& tolerance = numeric_comparator<T>::tolerance())
{
    return numeric_comparator<T>::is_equal(v1, v2, tolerance);
}

/**
 * @brief check whether two number are not equal
 * @param tolerance tolerance that prevents the floating point error
 */
template<typename T>
bool is_not_equal(const T& v1, const T& v2, const T& tolerance = numeric_comparator<T>::tolerance())
{
    return numeric_comparator<T>::is_not_equal(v1, v2, tolerance);
}

/**
 * @brief check whether number is same as zero
 * @param tolerance tolerance that prevents the floating point error
 * @note if the number type is from gmp, it should be in canonical form!
 */
template<typename T>
bool is_zero(const T& v, const T& tolerance = numeric_comparator<T>::tolerance())
{
    return numeric_comparator<T>::is_zero(v, tolerance);
}

/**
 * @brief check whether v1 is less than v2
 * @param tolerance tolerance that prevents the floating point error
 */
template<typename T>
bool is_less(const T& v1, const T& v2, const T& tolerance = numeric_comparator<T>::tolerance())
{
    return numeric_comparator<T>::is_less(v1, v2, tolerance);
}

/**
 * @brief check whether v1 is less than v2 or same as v2
 * @param tolerance tolerance that prevents the floating point error
 */
template<typename T>
bool is_less_equal(const T& v1, const T& v2, const T& tolerance = numeric_comparator<T>::tolerance())
{
    return numeric_comparator<T>::is_less_equal(v1, v2, tolerance);
}

/**
 * @brief check whether v1 is greater than v2
 * @param tolerance tolerance that prevents the floating point error
 */
template<typename T>
bool is_greater(const T& v1, const T& v2, const T& tolerance = numeric_comparator<T>::tolerance())
{
    return numeric_comparator<T>::is_greater(v1, v2, tolerance);
}

/**
 * @brief check whether v1 is greater than v2 or same as v2
 * @param tolerance tolerance that prevents the floating point error
 */
template<typename T>
bool is_greater_equal(const T& v1, const T& v2, const T& tolerance = numeric_comparator<T>::tolerance())
{
    return numeric_comparator<T>::is_greater_equal(v1, v2, tolerance);
}

}   // namespace CMTL

#endif  // __common_utils_h__