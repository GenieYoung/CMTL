#ifndef CMTL_VECTOR_T_H
#define CMTL_VECTOR_T_H

#include "numeric_utils.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

namespace CMTL {

/**
 * @brief fixed size value type container
 * @tparam T value type
 * @tparam DIM dimension of vector
 * @tparam Derived used for CRTP
 */
template <typename T, unsigned DIM, typename Derived>
class VectorT {
 protected:
  typedef std::array<T, DIM> container;
  container _values;

 public:
  typedef T value_type;

  /* origin vector */
  static const Derived Origin;

  /**
   * @brief return dimension of this vector
   */
  static constexpr unsigned dimension() noexcept { return DIM; }

  /**
   * @brief alias of dimension
   */
  static constexpr unsigned size() noexcept { return dimension(); }

  /**
   * @brief default constructor
   */
  constexpr VectorT() : _values{} {}

  /**
   * @brief copy constructor
   */
  VectorT(const VectorT& other) = default;

  /**
   * @brief move constructor
   */
  VectorT(VectorT&& other) = default;

  /**
   * @brief destructor
   */
  ~VectorT() = default;

  /**
   * @brief assign operator
   */
  Derived& operator=(const VectorT& other) {
    _values = other._values;
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief move assign operator
   */
  Derived& operator=(VectorT&& other) {
    _values = std::move(other._values);
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief set all values to v
   */
  template <unsigned D = DIM, typename std::enable_if<(D > 1), int>::type = 0>
  explicit constexpr VectorT(const T& v) {
    fill(v);
  }

  /**
   * @brief construct using DIM values
   */
  template <typename... TT,
            typename std::enable_if<(sizeof...(TT) == DIM), int>::type = 0>
  explicit constexpr VectorT(const TT&... vs)
      : _values{{util_cast<TT, T>(vs)...}} {}

  /**
   * @brief assign using DIM values
   */
  template <typename... TT,
            typename std::enable_if<(sizeof...(TT) == DIM), int>::type = 0>
  constexpr Derived& assign(const TT&... vs) {
    _values = {{util_cast<TT, T>(vs)...}};
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief construct using built-in arrays
   */
  template <typename TT>
  explicit constexpr VectorT(const TT (&vs)[DIM]) {
    for (unsigned i = 0; i < DIM; ++i) _values[i] = util_cast<TT, T>(vs[i]);
  }

  /**
   * @brief construct using std array
   */
  template <typename TT>
  explicit constexpr VectorT(const std::array<TT, DIM>& vs) {
    for (unsigned i = 0; i < DIM; ++i) _values[i] = util_cast<TT, T>(vs[i]);
  }

  /**
   * @brief assign & cast operator
   * @tparam TT another number type
   * @tparam DIM2 another dimension
   * @tparam Derived used for CRTP
   * @note this will default construct any values that cannot be filled
   *       (e.g. vec3->vec4) or leave out the last values when size of
   *       vector is shrinked(e.g. {1,2,3}->{1,2})
   */
  template <typename TT, unsigned DIM2, typename Derived2>
  Derived& operator=(const VectorT<TT, DIM2, Derived2>& other) {
    for (unsigned i = 0; i < std::min(DIM, DIM2); ++i)
      _values[i] = util_cast<TT, T>(other[i]);
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief copy & cast constructor
   * @tparam TT another number type
   * @tparam DIM2 another dimension
   * @tparam Derived used for CRTP
   */
  template <typename TT, unsigned DIM2, typename Derived2>
  explicit constexpr VectorT(const VectorT<TT, DIM2, Derived2>& other)
      : VectorT() {
    // in some machine, default construct may not initialize values to 0, so we
    // call default construct first
    operator=(other);
  }

  /**
   * @brief get the writable ith value
   */
  T& operator[](unsigned i) noexcept {
    assert(i < DIM && "index out of range");
    return _values[i];
  }

  /**
   * @brief get the const ith value
   */
  const T& operator[](unsigned i) const noexcept {
    assert(i < DIM && "index out of range");
    return _values[i];
  }

  /**
   * @brief set all values to v
   */
  constexpr Derived& fill(const T& v) {
    std::fill(_values.begin(), _values.end(), v);
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief self-addition
   */
  template <typename TT, typename Derived2>
  constexpr Derived& operator+=(const VectorT<TT, DIM, Derived2>& other) {
    for (unsigned i = 0; i < DIM; ++i) _values[i] += util_cast<TT, T>(other[i]);
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief add two vector
   */
  template <typename TT, typename Derived2>
  constexpr Derived operator+(const VectorT<TT, DIM, Derived2>& other) const {
    Derived result(static_cast<const Derived&>(*this));
    result += other;
    return result;
  }

  /**
   * @brief self-subtract
   */
  template <typename TT, typename Derived2>
  constexpr Derived& operator-=(const VectorT<TT, DIM, Derived2>& other) {
    for (unsigned i = 0; i < DIM; ++i) _values[i] -= util_cast<TT, T>(other[i]);
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief subtract two vector
   */
  template <typename TT, typename Derived2>
  constexpr Derived operator-(const VectorT<TT, DIM, Derived2>& other) const {
    Derived result(static_cast<const Derived&>(*this));
    result -= other;
    return result;
  }

  /**
   * @brief negative
   */
  constexpr Derived operator-() const {
    Derived result(static_cast<const Derived&>(*this));
    for (unsigned i = 0; i < DIM; ++i) result[i] = -_values[i];
    return result;
  }

  /**
   * @brief scalar product
   */
  template <typename TT, typename Derived2>
  constexpr T operator*(const VectorT<TT, DIM, Derived2>& other) const {
    T result(0);
    for (unsigned i = 0; i < DIM; ++i)
      result += (_values[i] * util_cast<TT, T>(other[i]));
    return result;
  }

  /**
   * @brief scalar product
   */
  template <typename TT, typename Derived2>
  constexpr T dot(const VectorT<TT, DIM, Derived2>& other) const {
    return *this * other;
  }

  /**
   * @brief self-scale by multiply
   * @note we not use T& to prevent user from writing something like v*=v[0]
   */
  constexpr Derived& operator*=(const T scale) {
    for (unsigned i = 0; i < DIM; ++i) _values[i] *= scale;
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief do scale by multiply
   */
  constexpr Derived operator*(const T& scale) const {
    Derived result(static_cast<const Derived&>(*this));
    result *= scale;
    return result;
  }

  /**
   * @brief self-scale by divide
   * @note we not use T& to prevent user from writing something like v/=v[0]
   */
  constexpr Derived& operator/=(const T scale) {
    assert(scale != T(0));
    for (unsigned i = 0; i < DIM; ++i) _values[i] /= scale;
    return static_cast<Derived&>(*this);
  }

  /**
   * @brief do scale by divide
   */
  constexpr Derived operator/(const T& scale) const {
    Derived result(static_cast<const Derived&>(*this));
    result /= scale;
    return result;
  }

  constexpr bool operator==(const VectorT& other) const {
    for (unsigned i = 0; i < DIM; ++i)
      if (_values[i] != other[i]) return false;
    return true;
  }

  constexpr bool operator!=(const VectorT& other) const {
    return !(*this == other);
  }

  constexpr bool operator<(const VectorT& other) const {
    for (unsigned i = 0; i < DIM; ++i)
      if (_values[i] != other._values[i]) return _values[i] < other._values[i];
    return false;
  }

  /**
   * @brief access to scalar array
   */
  constexpr T* data() noexcept { return _values.data(); }

  /**
   * @brief access to const scalar array
   */
  constexpr const T* data() const noexcept { return _values.data(); }

  /**
   * @brief return the index of first maximal component
   */
  constexpr unsigned max() const {
    auto max_iter = std::max_element(_values.cbegin(), _values.cend());
    return max_iter - _values.begin();
  }

  /**
   * @brief return the index of first minimal component
   */
  constexpr unsigned min() const {
    auto min_iter = std::min_element(_values.cbegin(), _values.cend());
    return min_iter - _values.begin();
  }

  /**
   * @brief return the index of first maximal absolute component
   */
  constexpr unsigned max_abs() const {
    auto max_iter = std::max_element(
        _values.cbegin(), _values.cend(),
        [](const T& a, const T& b) { return abs(a) < abs(b); });
    return max_iter - _values.begin();
  }

  /**
   * @brief return the index of first minimal absolute component
   */
  constexpr unsigned min_abs() const {
    auto min_iter = std::min_element(
        _values.cbegin(), _values.cend(),
        [](const T& a, const T& b) { return abs(a) < abs(b); });
    return min_iter - _values.begin();
  }

  /**
   * @brief calculate square of L2-norm
   */
  constexpr T norm_square() const { return (*this) * (*this); }

  /**
   * @brief calculate square of L2-norm
   */
  constexpr T length_square() const { return norm_square(); }

  friend std::ostream& operator<<(std::ostream& os, const VectorT& vec) {
    os << "[" << vec[0];
    for (unsigned i = 1; i < vec.dimension(); ++i) {
      os << "," << vec[i];
    }
    os << "]";
    return os;
  }
};

template <typename T, unsigned DIM, typename Derived>
const Derived VectorT<T, DIM, Derived>::Origin = Derived(T(0));

/**
 * @brief simple fixed size value type container easy for use
 * @tparam T number type
 * @tparam DIM dimension
 */
template <typename T, unsigned DIM>
class VecTBase final : public VectorT<T, DIM, VecTBase<T, DIM>> {
 public:
  /**
   * @brief float type
   */
  typedef T FT;

 public:
  using VectorT<T, DIM, VecTBase<T, DIM>>::VectorT;
  using VectorT<T, DIM, VecTBase<T, DIM>>::operator=;
};

/* specialized versions */
typedef VecTBase<int, 1> Vec1i;
typedef VecTBase<float, 1> Vec1f;
typedef VecTBase<double, 1> Vec1d;

typedef VecTBase<int, 2> Vec2i;
typedef VecTBase<float, 2> Vec2f;
typedef VecTBase<double, 2> Vec2d;

typedef VecTBase<int, 3> Vec3i;
typedef VecTBase<float, 3> Vec3f;
typedef VecTBase<double, 3> Vec3d;

#ifdef USE_GMP
typedef VecTBase<mpq_class, 1> Vec1r;
typedef VecTBase<mpq_class, 2> Vec2r;
typedef VecTBase<mpq_class, 3> Vec3r;
#endif

/**
 * @brief simple fixed size value type container easy for use
 * @tparam T number type
 * @tparam DIM dimension
 */
template <typename T, unsigned DIM>
using VecXT = VecTBase<T, DIM>;

}  // namespace CMTL

#endif  // CMTL_VECTOR_T_H