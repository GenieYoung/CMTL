#ifndef __common_utils_h__
#define __common_utils_h__

#ifdef USE_GMP
#include "gmpxx.h"
#endif

#ifdef USE_CORE
#include "CORE/CORE.h"
#endif

#include <cmath>
#include <string>
#include <type_traits>

/**
 * @brief Computational Mathematics Tool Library
 */
namespace CMTL {

/* auxiliary class for number type conversion */
template <typename T_IN, typename T_OUT>
struct util_cast_impl {
  static constexpr T_OUT cast(const T_IN& v) noexcept {
    return static_cast<T_OUT>(v);
  }
};

/* template specialization class, used for converting number type to string */
template <typename T_IN>
struct util_cast_impl<T_IN, std::string> {
  static std::string cast(const T_IN& v) noexcept { return std::to_string(v); }
};

/**
 * @brief number type conversion function
 * @tparam T_IN input number type
 * @tparam T_OUT output number type
 */
template <typename T_IN, typename T_OUT>
inline constexpr T_OUT util_cast(const T_IN& v) {
  return util_cast_impl<T_IN, T_OUT>::cast(v);
}

#ifdef USE_GMP
/* template specialization function, used for converting number type to double
 */
template <>
inline double util_cast<mpq_class, double>(const mpq_class& v) {
  return v.get_d();
}

/* template specialization function, used for converting number type to string
 */
template <>
inline std::string util_cast<mpq_class, std::string>(const mpq_class& v) {
  return v.get_str();
}
#endif  // USE_GMP

#ifdef USE_CORE
/* template specialization function, used for converting number type to double
 */
template <>
inline double util_cast<CORE::Expr, double>(const CORE::Expr& v) {
  return v.doubleValue();
}

/* template specialization function, used for converting number type to string
 */
template <>
inline std::string util_cast<CORE::Expr, std::string>(const CORE::Expr& v) {
  CORE::Expr tmp(v);
  return tmp.toString();
}
#endif // USE_CORE

/**
 * @brief convert number to double type
 */
template <typename T>
inline double to_double(const T& v) {
  return util_cast<T, double>(v);
}

/**
 * @brief convert number to string type
 */
template <typename T>
inline std::string to_string(const T& v) {
  return util_cast<T, std::string>(v);
}

/**
 * @brief calculate the absolute value of a number
 */
template <typename T>
inline T abs(const T& v) {
  using std::abs;
  return abs(v);
}

#ifdef USE_GMP
/**
 * @brief template specialization function, calculate the absolute value of a number
 * @note absolute(expression) may crash, call absolute(T(expression)) instead.
 */
inline mpq_class abs(const mpq_class& v) {
  if(v < 0) return -v;
  return v;
}
#endif

/**
 * @brief calculate the minimal value of two numbers
 */
template <typename T>
inline T min(const T& v1, const T& v2) {
  if (v1 < v2) return v1;
  return v2;
}

/**
 * @brief calculate the minimal value of two numbers
 */
template <typename T>
inline T max(const T& v1, const T& v2) {
  if (v1 > v2) return v1;
  return v2;
}

/**
 * @brief calculate the square root value of a number
 */
template <typename T>
inline T sqrt(const T& v) {
  using std::sqrt;
  return sqrt(v);
}

#ifdef USE_GMP
/* template specialization, calculate the square root value of a number */
template <>
inline mpq_class sqrt(const mpq_class& v) {
  return mpq_class(sqrt(to_double(v)));     // TODO
}
#endif

template <typename T, typename = void>
class numeric_comparator {
 public:
  static T tolerance() { return T(0); }

  static bool is_equal(const T& v1, const T& v2, const T& tol = T(0)) {
    return v1 == v2;
  }

  static bool is_not_equal(const T& v1, const T& v2, const T& tol = T(0)) {
    return !(is_equal(v1, v2, tol));
  }

  static bool is_less(const T& v1, const T& v2, const T& tol = T(0)) {
    return v1 < v2;
  }

  static bool is_less_equal(const T& v1, const T& v2, const T& tol = T(0)) {
    return v1 <= v2;
  }

  static bool is_greater(const T& v1, const T& v2, const T& tol = T(0)) {
    return v1 > v2;
  }

  static bool is_greater_equal(const T& v1, const T& v2, const T& tol = T(0)) {
    return v1 >= v2;
  }
};

template <typename T>
class numeric_comparator<
    T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
 public:
  static T& tolerance() { return _tol; }

  static bool is_equal(const T& v1, const T& v2, const T& tol = _tol) {
    return abs(v1 - v2) <= _tol;
  }

  static bool is_not_equal(const T& v1, const T& v2, const T& tol = _tol) {
    return !(is_equal(v1, v2, tol));
  }

  static bool is_zero(const T& v, const T& tol = _tol) {
    return is_equal(v, T(0), _tol);
  }

  static bool is_less(const T& v1, const T& v2, const T& tol = _tol) {
    return v1 < v2 - tol;
  }

  static bool is_less_equal(const T& v1, const T& v2, const T& tol = _tol) {
    return v1 <= v2 + tol;
  }

  static bool is_greater(const T& v1, const T& v2, const T& tol = _tol) {
    return v1 > v2 + tol;
  }

  static bool is_greater_equal(const T& v1, const T& v2, const T& tol = _tol) {
    return v1 >= v2 - tol;
  }

 private:
  static T _tol;
};

constexpr float default_float_tolerance = 1e-5;
constexpr double default_double_tolerance = 1e-13;

template <>
inline float numeric_comparator<float>::_tol = default_float_tolerance;

template <>
inline double numeric_comparator<double>::_tol = default_double_tolerance;

template <typename T>
T numeric_comparator<
    T, typename std::enable_if<std::is_floating_point<T>::value>::type>::_tol =
    std::numeric_limits<T>::epsilon();

/**
 * @brief check whether two number are equal
 * @param tolerance tolerance that prevents the floating point error
 * @note if the number type is from gmp, it should be in canonical form!
 */
template <typename T>
bool is_equal(const T& v1, const T& v2,
              const T& tolerance = numeric_comparator<T>::tolerance()) {
  return numeric_comparator<T>::is_equal(v1, v2, tolerance);
}

/**
 * @brief check whether two number are not equal
 * @param tolerance tolerance that prevents the floating point error
 */
template <typename T>
bool is_not_equal(const T& v1, const T& v2,
                  const T& tolerance = numeric_comparator<T>::tolerance()) {
  return numeric_comparator<T>::is_not_equal(v1, v2, tolerance);
}

/**
 * @brief check whether number is same as zero
 * @param tolerance tolerance that prevents the floating point error
 * @note if the number type is from gmp, it should be in canonical form!
 */
template <typename T>
bool is_zero(const T& v,
             const T& tolerance = numeric_comparator<T>::tolerance()) {
  return numeric_comparator<T>::is_zero(v, tolerance);
}

/**
 * @brief check whether v1 is less than v2
 * @param tolerance tolerance that prevents the floating point error
 */
template <typename T>
bool is_less(const T& v1, const T& v2,
             const T& tolerance = numeric_comparator<T>::tolerance()) {
  return numeric_comparator<T>::is_less(v1, v2, tolerance);
}

/**
 * @brief check whether v1 is less than v2 or same as v2
 * @param tolerance tolerance that prevents the floating point error
 */
template <typename T>
bool is_less_equal(const T& v1, const T& v2,
                   const T& tolerance = numeric_comparator<T>::tolerance()) {
  return numeric_comparator<T>::is_less_equal(v1, v2, tolerance);
}

/**
 * @brief check whether v1 is greater than v2
 * @param tolerance tolerance that prevents the floating point error
 */
template <typename T>
bool is_greater(const T& v1, const T& v2,
                const T& tolerance = numeric_comparator<T>::tolerance()) {
  return numeric_comparator<T>::is_greater(v1, v2, tolerance);
}

/**
 * @brief check whether v1 is greater than v2 or same as v2
 * @param tolerance tolerance that prevents the floating point error
 */
template <typename T>
bool is_greater_equal(const T& v1, const T& v2,
                      const T& tolerance = numeric_comparator<T>::tolerance()) {
  return numeric_comparator<T>::is_greater_equal(v1, v2, tolerance);
}

}  // namespace CMTL

#endif  // __common_utils_h__