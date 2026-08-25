#ifndef CMTL_GEO3D_BOX_H
#define CMTL_GEO3D_BOX_H

#include "point.h"

namespace CMTL {
namespace geo3d {

/**
 * @brief 3 dimension axis-aligned box
 * @tparam T number type of point coordinate
 */
template <typename T>
class Box {
 public:
  /**
   * @brief float type
   */
  typedef T FT;

 public:
  Box() = default;

  /**
   * @brief construct from two points
   * @param p0 first corner point
   * @param p1 second corner point
   */
  Box(const Point<T>& p0, const Point<T>& p1) : _min(p0), _max(p1) {
    normalize();
  }

  /**
   * @brief construct from six boundary coordinates
   * @param xmin_ minimum x coordinate
   * @param ymin_ minimum y coordinate
   * @param zmin_ minimum z coordinate
   * @param xmax_ maximum x coordinate
   * @param ymax_ maximum y coordinate
   * @param zmax_ maximum z coordinate
   */
  Box(const T& xmin_, const T& ymin_, const T& zmin_, const T& xmax_,
      const T& ymax_, const T& zmax_)
      : _min(xmin_, ymin_, zmin_), _max(xmax_, ymax_, zmax_) {
    normalize();
  }

  /**
   * @brief normalize the box, make sure xmin <= xmax, ymin <= ymax and zmin <=
   * zmax
   */
  void normalize() {
    if (xmin() > xmax()) std::swap(xmin(), xmax());
    if (ymin() > ymax()) std::swap(ymin(), ymax());
    if (zmin() > zmax()) std::swap(zmin(), zmax());
  }

  ~Box() = default;

 public:
  /**
   * @brief get the minimum corner point
   */
  const Point<T>& min() const { return _min; }

  /**
   * @brief get the maximum corner point
   */
  const Point<T>& max() const { return _max; }

  /**
   * @brief get the writable minimum x coordinate
   */
  T& xmin() { return _min.x(); }

  /**
   * @brief get the const minimum x coordinate
   */
  const T& xmin() const { return _min.x(); }

  /**
   * @brief get the writable maximum x coordinate
   */
  T& xmax() { return _max.x(); }

  /**
   * @brief get the const maximum x coordinate
   */
  const T& xmax() const { return _max.x(); }

  /**
   * @brief get the writable minimum y coordinate
   */
  T& ymin() { return _min.y(); }

  /**
   * @brief get the const minimum y coordinate
   */
  const T& ymin() const { return _min.y(); }

  /**
   * @brief get the writable maximum y coordinate
   */
  T& ymax() { return _max.y(); }

  /**
   * @brief get the const maximum y coordinate
   */
  const T& ymax() const { return _max.y(); }

  /**
   * @brief get the writable minimum z coordinate
   */
  T& zmin() { return _min.z(); }

  /**
   * @brief get the const minimum z coordinate
   */
  const T& zmin() const { return _min.z(); }

  /**
   * @brief get the writable maximum z coordinate
   */
  T& zmax() { return _max.z(); }

  /**
   * @brief get the const maximum z coordinate
   */
  const T& zmax() const { return _max.z(); }

  /**
   * @brief get the length along x-axis
   */
  T x_span() const { return xmax() - xmin(); }

  /**
   * @brief get the length along y-axis
   */
  T y_span() const { return ymax() - ymin(); }

  /**
   * @brief get the length along z-axis
   */
  T z_span() const { return zmax() - zmin(); }

  /**
   * @brief return the volume of the box
   */
  T volume() const { return x_span() * y_span() * z_span(); }

 private:
  Point<T> _min;
  Point<T> _max;
};

}  // namespace geo3d
}  // namespace CMTL

#endif  // CMTL_GEO3D_BOX_H