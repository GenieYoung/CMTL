#ifndef __algorithm_predicate__
#define __algorithm_predicate__

#include "../common/orientation.h"
#include "../geo2d/triangle.h"
#include "../geo3d/plane.h"

namespace CMTL {
namespace algorithm {

/**
 * @brief 1d orientation test
 * @return return positive if v > 0, negative if v < 0, otherwise return ON
 */
template <typename T>
ORIENTATION orient_1d(const T& v) {
  if (v > T(0))
    return ORIENTATION::POSITIVE;
  else if (v < T(0))
    return ORIENTATION::NEGATIVE;
  return ORIENTATION::ON;
}

/**
 * @brief 2d orientation test, non-robust if point type is not exact.
 * @return return positive if the point pa, pb, and pc occur in counterclockwise
 * order; negative if they occur in clockwise order; and on if they are
 * collinear.
 */
template <typename T>
ORIENTATION orient_2d(const geo2d::Point<T>& pa, const geo2d::Point<T>& pb,
                      const geo2d::Point<T>& pc) {
  T flag = (pb - pa) % (pc - pa);
  return orient_1d(flag);
}

/**
 * @brief 2d orientation test, used for built-in arrays, non-robust if point
 * type is not exact.
 * @return return positive if the point pa, pb, and pc occur in counterclockwise
 * order; negative if they occur in clockwise order; and on if they are
 * collinear.
 */
template <typename T>
ORIENTATION orient_2d(const T (&pa)[2], const T (&pb)[2], const T (&pc)[2]) {
  T flag =
      (pb[0] - pa[0]) * (pc[1] - pa[1]) - (pb[1] - pa[1]) * (pc[0] - pa[0]);
  return orient_1d(flag);
}

/**
 * @brief 3d orientation test
 * @return return positive if the point pd lies below the plane passing through
 * pa, pb, and pc, "below" is defined so that pa, pb, and pc appear in clockwise
 * order when viewed from below, return on if the points are coplanar, otherwise
 * return negative.
 */
template <typename T>
ORIENTATION orient_3d(const geo3d::Point<T>& pa, const geo3d::Point<T>& pb,
                      const geo3d::Point<T>& pc, const geo3d::Point<T>& pd) {
  T adx = pa[0] - pd[0], ady = pa[1] - pd[1], adz = pa[2] - pd[2],
    abx = pa[0] - pb[0], aby = pa[1] - pb[1], abz = pa[2] - pb[2],
    acx = pa[0] - pc[0], acy = pa[1] - pc[1], acz = pa[2] - pc[2];
  T flag = adx * (aby * acz - abz * acy) + ady * (abz * acx - abx * acz) +
           adz * (abx * acy - aby * acx);
  return orient_1d(flag);
}

/**
 * @brief 3d orientation test, used for built-in arrays
 * @return return positive if the point pd lies below the plane passing through
 * pa, pb, and pc, "below" is defined so that pa, pb, and pc appear in clockwise
 * order when viewed from below, return on if the points are coplanar, otherwise
 * return negative.
 */
template <typename T>
ORIENTATION orient_3d(const T (&pa)[3], const T (&pb)[3], const T (&pc)[3],
                      const T (&pd)[3]) {
  T adx = pa[0] - pd[0], ady = pa[1] - pd[1], adz = pa[2] - pd[2],
    abx = pa[0] - pb[0], aby = pa[1] - pb[1], abz = pa[2] - pb[2],
    acx = pa[0] - pc[0], acy = pa[1] - pc[1], acz = pa[2] - pc[2];
  T flag = adx * (aby * acz - abz * acy) + ady * (abz * acx - abx * acz) +
           adz * (abx * acy - aby * acx);
  return orient_1d(flag);
}

/**
 * @brief check a point orientation with the plane
 * @return return negative if point locates in the half-space the normal
 * direction point to, return positive if point on the opposite, otherwise
 * return on
 */
template <typename T>
ORIENTATION orient_3d(const geo3d::Plane<T>& plane, const geo3d::Point<T>& p) {
  return orient_1d((plane.origin() - p) * plane.normal());
}

/**
 * @brief check a point orientation with the plane, used for built-in arrays
 * @return return negative if point locates in the half-space the normal
 * direction point to, return positive if point on the opposite, otherwise
 * return on
 */
template <typename T>
ORIENTATION orient_3d(const geo3d::Plane<T>& plane, const T (&p)[3]) {
  return orient_1d((plane.origin() - p) * plane.normal());
}

/**
 * @brief in circle test, check whether point pd lies in the circle passing
 * through pa, pb, and pc
 * @return inside if pd lies inside the circle, outside if pd lies outside the
 * circle, and on if pd lies on the circle.
 * @note the points pa, pb, pc must be in counterclockwise order, otherwise the
 * sign will be reversed.
 */
template <typename T>
ORIENTATION in_circle(const geo2d::Point<T>& pa, const geo2d::Point<T>& pb,
                      const geo2d::Point<T>& pc, const geo2d::Point<T>& pd) {
  T pa_[3] = {pa[0], pa[1], pa[0] * pa[0] + pa[1] * pa[1]};
  T pb_[3] = {pb[0], pb[1], pb[0] * pb[0] + pb[1] * pb[1]};
  T pc_[3] = {pc[0], pc[1], pc[0] * pc[0] + pc[1] * pc[1]};
  T pd_[3] = {pd[0], pd[1], pd[0] * pd[0] + pd[1] * pd[1]};
  return orient_3d(pa_, pb_, pc_, pd_);
}

/**
 * @brief in circle test, check whether point pd lies in the circle passing
 * through pa, pb, and pc, used for built-in arrays
 * @return positive if pd lies inside the circle, negative if pd lies outside
 * the circle, and on if pd lies on the circle.
 * @note the points pa, pb, pc must be in counterclockwise order, otherwise the
 * sign will be reversed.
 */
template <typename T>
ORIENTATION in_circle(const T (&pa)[2], const T (&pb)[2], const T (&pc)[2],
                      const T (&pd)[2]) {
  T pa_[3] = {pa[0], pa[1], pa[0] * pa[0] + pa[1] * pa[1]};
  T pb_[3] = {pb[0], pb[1], pb[0] * pb[0] + pb[1] * pb[1]};
  T pc_[3] = {pc[0], pc[1], pc[0] * pc[0] + pc[1] * pc[1]};
  T pd_[3] = {pd[0], pd[1], pd[0] * pd[0] + pd[1] * pd[1]};
  return orient_3d(pa_, pb_, pc_, pd_);
}

/**
 * @brief check whether two 2d triangle [pa, pb, pc] and [pb, pa, pd] is locally
 * delaunay.
 * @tparam Point 2d point
 * @param is_strongly if true, delaunay means its closed circumdisk is empty
 * @return true if locally delaunay, otherwise false
 * @note the points pa, pb, pc must be in counterclockwise order
 */
template <typename T>
bool is_locally_delaunay(const geo2d::Point<T>& pa, const geo2d::Point<T>& pb,
                         const geo2d::Point<T>& pc, const geo2d::Point<T>& pd,
                         bool is_strongly = false) {
  ORIENTATION flag = in_circle(pa, pb, pc, pd);
  return flag == ORIENTATION::OUTSIDE ||
         (!is_strongly && flag == ORIENTATION::ON);
}

/**
 * @brief check whether two 2d triangle [pa, pb, pc] and [pb, pa, pd] is locally
 * delaunay, used for built-in arrays
 * @tparam Point 2d point
 * @param is_strongly if true, delaunay means its closed circumdisk is empty
 * @return true if locally delaunay, otherwise false
 * @note the points pa, pb, pc must be in counterclockwise order
 */
template <typename T>
bool is_locally_delaunay(const T (&pa)[2], const T (&pb)[2], const T (&pc)[2],
                         const T (&pd)[2], bool is_strongly = false) {
  ORIENTATION flag = in_circle(pa, pb, pc, pd);
  return flag == ORIENTATION::OUTSIDE ||
         (!is_strongly && flag == ORIENTATION::ON);
}

/**
 * @brief in triangle test, check whether point p lies in the triangle t012
 * @return positive if pd lies inside the triangle, negative if pd lies outside
 * the triangle, and on if pd lies on the boundary.
 * @note the triangle's vertices t0 t1 t2 must be in counterclockwise order,
 * otherwise the sign will be reversed.
 */
template <typename T>
ORIENTATION in_triangle(const geo2d::Point<T>& t0, const geo2d::Point<T>& t1,
                        const geo2d::Point<T>& t2, const geo2d::Point<T>& p) {
  ORIENTATION o1 = orient_2d(t0, t1, p);
  if (o1 == ORIENTATION::OUTSIDE) return ORIENTATION::OUTSIDE;
  ORIENTATION o2 = orient_2d(t1, t2, p);
  if (o2 == ORIENTATION::OUTSIDE) return ORIENTATION::OUTSIDE;
  ORIENTATION o3 = orient_2d(t2, t0, p);
  if (o3 == ORIENTATION::OUTSIDE) return ORIENTATION::OUTSIDE;
  if (o1 == ORIENTATION::INSIDE && o2 == ORIENTATION::INSIDE &&
      o3 == ORIENTATION::INSIDE)
    return ORIENTATION::INSIDE;
  return ORIENTATION::ON;
}

/**
 * @brief in triangle test, check whether point p lies in the triangle t012,
 * used in built-in arrays
 * @return positive if pd lies inside the triangle, negative if pd lies outside
 * the triangle, and on if pd lies on the boundary.
 * @note the triangle's vertices t0 t1 t2 must be in counterclockwise order,
 * otherwise the sign will be reversed.
 */
template <typename T>
ORIENTATION in_triangle(const T (&t0)[2], const T (&t1)[2], const T (&t2)[2],
                        const geo2d::Point<T>& p) {
  ORIENTATION o1 = orient_2d(t0, t1, p);
  if (o1 == ORIENTATION::OUTSIDE) return ORIENTATION::OUTSIDE;
  ORIENTATION o2 = orient_2d(t1, t2, p);
  if (o2 == ORIENTATION::OUTSIDE) return ORIENTATION::OUTSIDE;
  ORIENTATION o3 = orient_2d(t2, t0, p);
  if (o3 == ORIENTATION::OUTSIDE) return ORIENTATION::OUTSIDE;
  if (o1 == ORIENTATION::INSIDE && o2 == ORIENTATION::INSIDE &&
      o3 == ORIENTATION::INSIDE)
    return ORIENTATION::INSIDE;
  return ORIENTATION::ON;
}

/**
 * @brief in triangle test, check whether point p lies in the triangle
 * @return positive if pd lies inside the triangle, negative if pd lies outside
 * the triangle, and on if pd lies on the boundary.
 * @note the triangle's vertices must be in counterclockwise order, otherwise
 * the sign will be reversed.
 */
template <typename T>
ORIENTATION in_triangle(const geo2d::Triangle<T>& tri,
                        const geo2d::Point<T>& p) {
  return in_triangle(tri[0], tri[1], tri[2], p);
}

}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_predicate__