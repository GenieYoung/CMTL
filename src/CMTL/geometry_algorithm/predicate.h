#ifndef __geometry_algorithm_predicate__
#define __geometry_algorithm_predicate__

#include "../common/orientation.h"
#include "../geo3d/geo3d_plane.h"

namespace CMTL{

namespace geometry_algorithm{

/**
 * @brief 1d orientation test
 * @return return positive if v > 0, negative if v < 0, otherwise return ON
 */
template<typename T>
ORIENTATION orient_1d(const T& v)
{
    if(v > T(0))
        return ORIENTATION::POSITIVE;
    else if(v < T(0))
        return ORIENTATION::NEGATIVE;
    return ORIENTATION::ON;
}

/**
 * @brief 2d orientation test, non-robust if point type is not exact.
 * @return return positive if the point pa, pb, and pc occur in counterclockwise order;
 *         negative if they occur in clockwise order; and on if they are collinear.
 */
template<typename T>
ORIENTATION orient_2d(const geo2d::Point<T>& pa, const geo2d::Point<T>& pb, const geo2d::Point<T>& pc)
{
    T flag = (pb - pa) % (pc - pa);
    return orient_1d(flag);
}

/**
 * @brief 2d orientation test, used for built-in arrays, non-robust if point type is not exact.
 * @return return positive if the point pa, pb, and pc occur in counterclockwise order;
 *         negative if they occur in clockwise order; and on if they are collinear.
 */
template<typename T>
ORIENTATION orient_2d(const T (&pa)[2], const T (&pb)[2], const T (&pc)[2]) {
    T flag = (pb[0] - pa[0]) * (pc[1] - pa[1]) - (pb[1] - pa[1]) * (pc[0] - pa[0]);
    return orient_1d(flag);
}

/**
 * @brief 3d orientation test
 * @return return positive if the point pd lies above the plane passing through pa, pb, and pc,
 *         "above" is defined so that pa, pb, and pc appear in counterclockwise order when viewed from above the plane,
 *         return on if the points are coplanar, otherwise return negative.
 */
template<typename T>
ORIENTATION orient_3d(const geo3d::Point<T>& pa, const geo3d::Point<T>& pb, const geo3d::Point<T>& pc, const geo3d::Point<T>& pd)
{
    T adx = pd[0] - pa[0], ady = pd[1] - pa[1], adz = pd[2] - pa[2],
      abx = pb[0] - pa[0], aby = pb[1] - pa[1], abz = pb[2] - pa[2],
      acx = pc[0] - pa[0], acy = pc[1] - pa[1], acz = pc[2] - pa[2];
    T flag = adx * (aby * acz - abz * acy) +
             ady * (abz * acx - abx * acz) +
             adz * (abx * acy - aby * acx);
    return orient_1d(flag);
}

/**
 * @brief 3d orientation test, used for built-in arrays
 * @return return positive if the point pd lies above the plane passing through pa, pb, and pc,
 *         "above" is defined so that pa, pb, and pc appear in counterclockwise order when viewed from above the plane,
 *         return on if the points are coplanar, otherwise return negative.
 */
template<typename T>
ORIENTATION orient_3d(const T (&pa)[3], const T (&pb)[3], const T (&pc)[3], const T (&pd)[3])
{
    T adx = pd[0] - pa[0], ady = pd[1] - pa[1], adz = pd[2] - pa[2],
      abx = pb[0] - pa[0], aby = pb[1] - pa[1], abz = pb[2] - pa[2],
      acx = pc[0] - pa[0], acy = pc[1] - pa[1], acz = pc[2] - pa[2];
    T flag = adx * (aby * acz - abz * acy) +
             ady * (abz * acx - abx * acz) +
             adz * (abx * acy - aby * acx);
    return orient_1d(flag);
}

/**
 * @brief check a point orientation with the plane
 * @return return above if point above plane, return below if point on the opposite, otherwise return on
 */
template<typename T>
ORIENTATION orient_3d(const geo3d::Plane<T>& plane, const geo3d::Point<T>& p)
{
    return orient_1d((p - plane.origin()) * plane.normal());
}

/**
 * @brief check a point orientation with the plane, used for built-in arrays
 * @return return above if point above plane, return below if point on the opposite, otherwise return on
 */
template<typename T>
ORIENTATION orient_3d(const geo3d::Plane<T>& plane, const T (&p)[3])
{
    return orient_1d((p - plane.origin()) * plane.normal());
}

/**
 * @brief check whether two 2d triangle [pa, pb, pc] and [pb, pa, pd] is locally delaunay.
 * @tparam Point 2d point
 * @param is_strongly if true, delaunay means its closed circumdisk is empty
 * @return true if locally delaunay, otherwise false
 */
template<typename T>
bool is_locally_delaunay(const geo2d::Point<T>& pa, const geo2d::Point<T>& pb, const geo2d::Point<T>& pc, const geo2d::Point<T>& pd, bool is_strongly = false)
{
    T pa_[3] = {pa[0], pa[1], pa[0]*pa[0] + pa[1]*pa[1]};
    T pb_[3] = {pb[0], pb[1], pb[0]*pb[0] + pb[1]*pb[1]};
    T pc_[3] = {pc[0], pc[1], pc[0]*pc[0] + pc[1]*pc[1]};
    T pd_[3] = {pd[0], pd[1], pd[0]*pd[0] + pd[1]*pd[1]};
    ORIENTATION flag = orient_3d(pa_, pb_, pc_, pd_);
    return flag == ORIENTATION::POSITIVE || (!is_strongly && flag == ORIENTATION::ON);
}

/**
 * @brief check whether two 2d triangle [pa, pb, pc] and [pb, pa, pd] is locally delaunay, used for built-in arrays
 * @tparam Point 2d point
 * @param is_strongly if true, delaunay means its closed circumdisk is empty
 * @return true if locally delaunay, otherwise false
 */
template<typename T>
bool is_locally_delaunay(const T (&pa)[2], const T (&pb)[2], const T (&pc)[2], const T (&pd)[2], bool is_strongly = false)
{
    T pa_[3] = {pa[0], pa[1], pa[0]*pa[0] + pa[1]*pa[1]};
    T pb_[3] = {pb[0], pb[1], pb[0]*pb[0] + pb[1]*pb[1]};
    T pc_[3] = {pc[0], pc[1], pc[0]*pc[0] + pc[1]*pc[1]};
    T pd_[3] = {pd[0], pd[1], pd[0]*pd[0] + pd[1]*pd[1]};
    ORIENTATION flag = orient_3d(pa_, pb_, pc_, pd_);
    return flag == ORIENTATION::POSITIVE || (!is_strongly && flag == ORIENTATION::ON);
}

}   // namespace geometry_algorithm
}   // namespace CMTL

#endif  // __geometry_algorithm_predicate__