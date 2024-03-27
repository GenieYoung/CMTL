#ifndef __geometry_process_area__
#define __geometry_process_area__

#include "geo2d/geo2d_polygon.h"

namespace CMTL  {
namespace geometry_process  {

/**
 * @brief calculate polygon area from iterator range from point container.
 * @tparam ForwardIterator point container's iterator, the point must has operator[] method to get coordinate
 * @tparam NT type of point coordinate 
 * @param result the polygon area
 */
template<typename ForwardIterator, class NumberType>
void area(ForwardIterator first, ForwardIterator last, NumberType& result)
{
    /* use the Shoelace formula */
    result = NumberType(0);
    if(first == last)
        return;
    ForwardIterator second = first; ++second;
    if(second == first)
        return;
    while(first != last)
    {
        result += (first->operator[](0) * second->operator[](1) - second->operator[](0) * first->operator[](1));
        ++first;
        second == last ? (second = first) : ++second;
    }
    result /= 2;
}

/**
 * @brief calculate the area of a simple polygon.
 * @tparam T value type of point coordinate 
 * @return the polygon area.
 */
template<typename T>
T area(const geo2d::Polygon<T>& polygon)
{
    /* use the Shoelace formula */
    return polygon.area();
}


}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_area__