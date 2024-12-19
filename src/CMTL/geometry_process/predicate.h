#ifndef __geometry_process_predicate__
#define __geometry_process_predicate__

#include <array>
#include "../common/orientation.h"
#include "../common/number_utils.h"

namespace CMTL{

namespace geometry_process{

/**
 * @brief 2d orientation test, non-robust if point type is not exact.
 * @return return positive if the point pa, pb, and pc occur in counterclockwise order;
 *         negative if they occur in clockwise order; and on if they are collinear.
 * @note the point must have operator[] method to get coordinate
 */
template<typename Point>
ORIENTATION orient_2d(const Point& pa, const Point& pb, const Point& pc)
{
    auto flag = (pa[0] - pc[0]) * (pb[1] - pc[1]) - (pa[1] - pc[1]) * (pb[0] - pc[0]);
    if(is_greater(flag, decltype(flag)(0)))    
        return ORIENTATION::POSITIVE;
    else if(is_less(flag, decltype(flag)(0)))   
        return ORIENTATION::NEGATIVE;
    return ORIENTATION::ON;
}

/**
 * @brief 3d orientation test
 * @return return positive if the point pd lies above the plane passing through pa, pb, and pc,
 *         "above" is defined so that pa, pb, and pc appear in counterclockwise order when viewed from above the plane,
 *         return on if the points are coplanar, otherwise return negative.
 * @note the point must have value_type to represent number type and have operator[] method to get coordinate,
 *       non-robust if point type is not exact
 */
template<typename Point>
ORIENTATION orient_3d(const Point& pa, const Point& pb, const Point& pc, const Point& pd)
{
    typename Point::value_type adx = pd[0] - pa[0], ady = pd[1] - pa[1], adz = pd[2] - pa[2],
                               abx = pb[0] - pa[0], aby = pb[1] - pa[1], abz = pb[2] - pa[2],
                               acx = pc[0] - pa[0], acy = pc[1] - pa[1], acz = pc[2] - pa[2];
    typename Point::value_type flag = adx * (aby * acz - abz * acy) +
                                      ady * (abz * acx - abx * acz) +
                                      adz * (abx * acy - aby * acx);
    if(is_greater(flag, typename Point::value_type(0)))
        return ORIENTATION::POSITIVE;
    else if(is_less(flag, typename Point::value_type(0)))
        return ORIENTATION::NEGATIVE;
    return ORIENTATION::ON;
}

/**
 * @brief check whether two 2d triangle [pa, pb, pc] and [pb, pa, pd] is locally delaunay.
 * @tparam Point 2d point
 * @return true if locally delaunay, otherwise false
 * @note point must have value_type to represent number type and have operator[] method to get coordinate
 */
template<typename Point>
bool is_locally_delaunay(const Point& pa, const Point& pb, const Point& pc, const Point& pd)
{
    std::array<typename Point::value_type, 3> pa_ = {pa[0], pa[1], pa[0]*pa[0] + pa[1]*pa[1]};
    std::array<typename Point::value_type, 3> pb_ = {pb[0], pb[1], pb[0]*pb[0] + pb[1]*pb[1]};
    std::array<typename Point::value_type, 3> pc_ = {pc[0], pc[1], pc[0]*pc[0] + pc[1]*pc[1]};
    std::array<typename Point::value_type, 3> pd_ = {pd[0], pd[1], pd[0]*pd[0] + pd[1]*pd[1]};
    ORIENTATION flag = orient_3d(pa_, pb_, pc_, pd_);
    return flag == ORIENTATION::POSITIVE || flag == ORIENTATION::ON;
}

}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_predicate__