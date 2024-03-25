#ifndef __geometry_process_triangulate__
#define __geometry_process_triangulate__

#include <vector>
#include <array>

namespace CMTL  {

namespace geo2d {
    template<typename T>
    class Polygon;
}

namespace geometry_process  {

namespace internal  {

    class triangulate_polygon_modifier
    {
        
    };

}   // namespace internal

/**
 * @brief triangulate polygon into several triangles.
 * @return true if the polygon can be trianguled.
 * @note the polygon should be intersect-free.
*/
template<typename T>
bool triangulate(const geo2d::Polygon<T>& polygon, std::vector<std::array<unsigned int, 3>>& triangles)
{
    // TODO
    return true;
}

}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_triangulate__