#ifndef __geometry_process_area__
#define __geometry_process_area__

#include "geo2d/geo2d_polygon.h"

namespace CMTL  {
namespace geometry_process  {

/**
 * @brief calculate the area of a simple polygon.
 * @tparam T value type of point coordinate 
 * @return the polygon area.
 */
template<typename T>
T area(const geo2d::Polygon<T>& polygon)
{
    /* use the Shoelace formula */
    T result = 0;
    for(size_t i = 0, j = 1; i < polygon.n_points(); ++i, ++j, j%=polygon.n_points())
    {
        result += ( polygon[i].x() * polygon[j].y() - polygon[j].x() * polygon[i].y());
    }
    return result / 2;
}


}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_area__