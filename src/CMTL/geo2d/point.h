#ifndef CMTL_GEO2D_POINT_H
#define CMTL_GEO2D_POINT_H

#include "../common/vectorT.h"

namespace CMTL {

/**
 * @brief 2d geometry
 */
namespace geo2d {

/**
 * @brief 2 dimension point or vector.
 * @tparam T number type of coordinate
 */
template <typename T>
class Point final : public VectorT<T, 2, Point<T>> {
 public:
  /**
   * @brief float type
   */
  typedef T FT;

 public:
  using VectorT<T, 2, Point>::VectorT;
  using VectorT<T, 2, Point>::operator=;

 public:
  /**
   * @brief get the writable x coordinate
   */
  T& x() noexcept { return this->operator[](0); }

  /**
   * @brief get the const x coordinate.
   */
  const T& x() const noexcept { return this->operator[](0); }

  /**
   * @brief get the writable y coordinate.
   */
  T& y() noexcept { return this->operator[](1); }

  /**
   * @brief get the const y coordinate.
   */
  const T& y() const noexcept { return this->operator[](1); }

 public:
  /**
   * @brief do cross product with another point
   */
  T operator%(const Point& p) const { return x() * p.y() - y() * p.x(); }

  /**
   * @brief do cross product with another point
   */
  T cross(const Point& p) const { return (*this) % p; }
};

}  // namespace geo2d
}  // namespace CMTL

#endif  // CMTL_GEO2D_POINT_H