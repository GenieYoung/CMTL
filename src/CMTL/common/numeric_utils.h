#ifndef CMTL_NUMERIC_UTILS_H
#define CMTL_NUMERIC_UTILS_H

#ifdef USE_GMP
#include "gmpxx.h"
#endif

#ifdef USE_CORE
#include "CORE/CORE.h"
#endif

#include <cmath>
#include <string>

/**
 * @brief Computational Mathematics Tool Library
 */
namespace CMTL {

/* auxiliary class for number type conversion */
template <typename T_IN, typename T_OUT>
struct util_cast_impl {
  static constexpr T_OUT cast(const T_IN& v) { return static_cast<T_OUT>(v); }
};

/* template specialization class, used for converting number type to string */
template <typename T_IN>
struct util_cast_impl<T_IN, std::string> {
  static std::string cast(const T_IN& v) { return std::to_string(v); }
};

#ifdef USE_GMP
/* template specialization class, used for converting number type to double
 */
template <>
struct util_cast_impl<mpq_class, double> {
  static double cast(const mpq_class& v) { return v.get_d(); }
};

/* template specialization class, used for converting number type to double
 */
template <typename Expression>
struct util_cast_impl<__gmp_expr<mpq_t, Expression>, double> {
  static double cast(const __gmp_expr<mpq_t, Expression>& expr) {
    return mpq_class(expr).get_d();
  }
};

/* template specialization class, used for converting number type to string
 */
template <>
struct util_cast_impl<mpq_class, std::string> {
  static std::string cast(const mpq_class& v) { return v.get_str(); }
};

/* template specialization class, used for converting number type to string
 */
template <typename Expression>
struct util_cast_impl<__gmp_expr<mpq_t, Expression>, std::string> {
  static std::string cast(const __gmp_expr<mpq_t, Expression>& expr) {
    return mpq_class(expr).get_str();
  }
};
#endif  // USE_GMP

#ifdef USE_CORE
/* template specialization class, used for converting number type to double
 */
template <>
struct util_cast_impl<CORE::Expr, double> {
  static double cast(const CORE::Expr& v) { return v.doubleValue(); }
};

/* template specialization class, used for converting number type to string
 */
template <>
struct util_cast_impl<CORE::BigRat, std::string> {
  static std::string cast(const CORE::BigRat& v) { return v.get_str(); }
};

/* template specialization class, used for converting number type to string
 */
template <>
struct util_cast_impl<CORE::Expr, std::string> {
  static std::string cast(const CORE::Expr& v) {
    return CORE::Expr(v).toString();
  }
};
#endif  // USE_CORE

#if defined(USE_GMP) && defined(USE_CORE)
/* convert an mpq_class to an exact CORE::Expr.
 */
template <>
struct util_cast_impl<mpq_class, CORE::Expr> {
  static CORE::Expr cast(const mpq_class& value) {
    CORE::BigRat result;
    mpq_set(result.mp(), value.get_mpq_t());
    return CORE::Expr(result);
  }
};

/** convert a gmp expression to an exact CORE::Expr.
 */
template <typename Expression>
struct util_cast_impl<__gmp_expr<mpq_t, Expression>, CORE::Expr> {
  static CORE::Expr cast(const __gmp_expr<mpq_t, Expression>& expr) {
    const mpq_class value(expr);

    return util_cast_impl<mpq_class, CORE::Expr>::cast(value);
  }
};
#endif  // defined(USE_GMP) && defined(USE_CORE)

/**
 * @brief number type conversion function
 * @tparam T_IN input number type
 * @tparam T_OUT output number type
 */
template <typename T_IN, typename T_OUT>
inline constexpr T_OUT util_cast(const T_IN& v) {
  return util_cast_impl<T_IN, T_OUT>::cast(v);
}

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

#ifdef USE_CORE
template <typename T>
inline CORE::Expr to_core_expr(const T& value) {
  return util_cast<T, CORE::Expr>(value);
}
#endif  // USE_CORE

/**
 * @brief calculate the absolute value of a number
 * @note do not use auto to get the return type if T is a gmp expression
 */
template <typename T>
inline decltype(auto) abs(const T& v) {
  using std::abs;
  return abs(v);
}

/**
 * @brief calculate the minimal value of two numbers
 */
template <typename T>
inline const T& min(const T& v1, const T& v2) {
  return v2 < v1 ? v2 : v1;
}

/**
 * @brief calculate the maximal value of two numbers
 */
template <typename T>
inline const T& max(const T& v1, const T& v2) {
  return v1 < v2 ? v2 : v1;
}

#ifdef USE_GMP
inline const mpq_class& min(const mpq_class& v1, const mpq_class& v2) {
  return v2 < v1 ? v2 : v1;
}

template <typename Expression1, typename Expression2>
inline mpq_class min(const __gmp_expr<mpq_t, Expression1>& expr1,
                     const __gmp_expr<mpq_t, Expression2>& expr2) {
  mpq_class v1(expr1);
  mpq_class v2(expr2);

  if (v2 < v1) return v2;
  return v1;
}

inline const mpq_class& max(const mpq_class& v1, const mpq_class& v2) {
  return v1 < v2 ? v2 : v1;
}

template <typename Expression1, typename Expression2>
inline mpq_class max(const __gmp_expr<mpq_t, Expression1>& expr1,
                     const __gmp_expr<mpq_t, Expression2>& expr2) {
  mpq_class v1(expr1);
  mpq_class v2(expr2);

  if (v1 < v2) return v2;
  return v1;
}
#endif  // USE_GMP

/**
 * @brief calculate the square root value of a number
 */
template <typename T>
inline decltype(auto) sqrt(const T& v) {
  using std::sqrt;
  return sqrt(v);
}

#if defined(USE_GMP) && defined(USE_CORE)
/**
 * @brief calculate the exact square root of a gmp rational expression.
 * @return an exact algebraic expression.
 * @pre expression >= 0
 */
template <typename Expression>
inline CORE::Expr sqrt(const __gmp_expr<mpq_t, Expression>& expr) {
  const CORE::Expr value = to_core_expr(expr);
  using std::sqrt;
  return sqrt(value);
}
#endif  // defined(USE_GMP) && defined(USE_CORE)

}  // namespace CMTL

#endif  // CMTL_NUMERIC_UTILS_H