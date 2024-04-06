#ifndef __geometry_process_area__
#define __geometry_process_area__

#include "geo2d/geo2d_polygon.h"
#include "geo2d/geo2d_triangle.h"

namespace CMTL  {
namespace geometry_process  {

/**
 * @brief calculate the area of a triangle.
 * @tparam T value type of point coordinate 
 * @return the triangle area.
 */
template<typename T>
T area(const geo2d::Triangle<T>& polygon)
{
    /* use the Shoelace formula */
    return polygon.area();
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

/**
 * @brief calculate triangle area bounded by three points
 * @tparam Point point type
 * @note the point must has operator[] method to get coordinate
*/
template<typename Point, class NumberType>
void area_2d(const Point& p1, const Point&p2, const Point& p3, NumberType& result)
{
    return ((p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0])) / NumberType(2);
}

/**
 * @brief calculate polygon area from iterator range from point container.
 * @tparam ForwardIterator point container's iterator
 * @tparam NT type of point coordinate 
 * @param result the polygon area
 * @note the point must has operator[] method to get coordinate
 */
template<typename ForwardIterator, class NumberType>
void area_2d(ForwardIterator first, ForwardIterator last, NumberType& result)
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

}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_area__