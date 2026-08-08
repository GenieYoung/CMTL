#ifndef CMTL_GEO3D_POINT_H
#define CMTL_GEO3D_POINT_H

#include "../common/vectorT.h"

#include <iomanip>
#include <iostream>

#include <assert.h>

namespace CMTL {

/**
 * @brief 3d geometry
 */
namespace geo3d {

/**
 * @brief 3 dimension point or vector.
 * @tparam T number type of coordinate
 */
template <typename T>
class Point final : public VectorT<T, 3, Point<T>> {
 public:
  /**
   * @brief float type
   */
  typedef T FT;

 public:
  using VectorT<T, 3, Point>::VectorT;
  using VectorT<T, 3, Point>::operator=;

 public:
  /**
   * @brief get the writable x coordinate
   */
  T& x() noexcept { return this->operator[](0); }

  /**
   * @brief get the const x coordinate
   */
  const T& x() const noexcept { return this->operator[](0); }

  /**
   * @brief get the writable y coordinate
   */
  T& y() noexcept { return this->operator[](1); }

  /**
   * @brief get the const y coordinate
   */
  const T& y() const noexcept { return this->operator[](1); }

  /**
   * @brief get the writable z coordinate
   */
  T& z() noexcept { return this->operator[](2); }

  /**
   * @brief get the const z coordinate
   */
  const T& z() const noexcept { return this->operator[](2); }

 public:
  /**
   * @brief do cross product with another point
   */
  Point operator%(const Point& p) const noexcept {
    return Point(y() * p.z() - z() * p.y(), z() * p.x() - x() * p.z(),
                 x() * p.y() - y() * p.x());
  }

  /**
   * @brief do cross product with another point
   */
  Point cross(const Point& p) const noexcept { return (*this) % p; }
};

}  // namespace geo3d
}  // namespace CMTL

#endif  // CMTL_GEO3D_POINT_H