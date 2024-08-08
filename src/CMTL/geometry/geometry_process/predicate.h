#ifndef __geometry_process_predicate__
#define __geometry_process_predicate__

#include "geo2d/geo2d_polygon.h"
#include "geo2d/geo2d_triangle.h"

namespace CMTL{
namespace geometry{
namespace geometry_process{

/**
 * @brief 2d orientation test, non robust if point type is not exact.
 * @return return 1 if the point pa, pb, and pc occur in counterclockwise order;
 *         -1 if they occur in clockwise order; and zero if they are collinear.
 * @note the point must has operator[] method to get coordinate
 */
template<typename Point>
int orient_2d(const Point& pa, const Point& pb, const Point& pc)
{
    auto flag = (pa[0] - pc[0]) * (pb[1] - pc[1]) - (pa[1] - pc[1]) * (pb[0] - pc[0]);
    if(flag > 0)    
        return 1;
    else if(flag < 0)   
        return -1;
    else    
        return 0;
}


}   // namespace geometry_process
}   // namespace geometry
}   // namespace CMTL

#endif  // __geometry_process_predicate__