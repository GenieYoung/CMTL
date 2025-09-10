#ifndef __geo3d_point_h__
#define __geo3d_point_h__

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
class Point : public VectorT<T, 3, Point<T>> {
 public:
  /**
   * @brief float type
   */
  typedef T FT;

 public:
  using VectorT<T, 3, Point>::VectorT;
  using VectorT<T, 3, Point>::operator=;

  /**
   * @brief construct a 3d point with three coordinates
   */
  Point(const T& x = 0, const T& y = 0, const T& z = 0)
      : VectorT<T, 3, Point>(x, y, z) {}

  ~Point() = default;

 public:
  /**
   * @brief get the writable x coordinate
   */
  T& x() { return this->operator[](0); }

  /**
   * @brief get the const x coordinate
   */
  const T& x() const { return this->operator[](0); }

  /**
   * @brief get the writable y coordinate
   */
  T& y() { return this->operator[](1); }

  /**
   * @brief get the const y coordinate
   */
  const T& y() const { return this->operator[](1); }

  /**
   * @brief get the writable z coordinate
   */
  T& z() { return this->operator[](2); }

  /**
   * @brief get the const z coordinate
   */
  const T& z() const { return this->operator[](2); }

 public:
  /**
   * @brief do cross product with another point
   */
  Point operator%(const Point& p) const {
    return Point(y() * p.z() - z() * p.y(), z() * p.x() - x() * p.z(),
                 x() * p.y() - y() * p.x());
  }

  /**
   * @brief do cross product with another point
   */
  Point cross(const Point& p) const { return (*this) % p; }
};

}  // namespace geo3d
}  // namespace CMTL

#endif  // __geo3d_point_h__