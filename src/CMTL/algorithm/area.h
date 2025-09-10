#ifndef __algorithm_area__
#define __algorithm_area__

#include "../geo2d/polygon.h"
#include "../geo2d/triangle.h"

namespace CMTL{
namespace algorithm{

/**
 * @brief calculate the area of a triangle.
 * @tparam T value type of point coordinate 
 * @return the triangle area.
 */
template<typename T>
T area(const geo2d::Triangle<T>& triangle)
{
    return triangle.area();
}

/**
 * @brief calculate the area of a simple polygon.
 * @tparam T value type of point coordinate 
 * @return the polygon area.
 */
template<typename T>
T area(const geo2d::Polygon<T>& polygon)
{
    return polygon.area();
}

/**
 * @brief calculate triangle area bounded by three points
 * @tparam Point point type
 * @note the point must has operator[] method to get coordinate
*/
template<typename Point, typename NumberType>
void area_2d(const Point& p1, const Point& p2, const Point& p3, NumberType& result)
{
    result = ((p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0])) / NumberType(2);
}

/**
 * @brief calculate polygon area.
 * @tparam Polygon polygon type
 * @tparam NumberType type of point coordinate 
 * @param result the polygon area
 * @note  polygon struct should have [] operator to get the point and the size() method to get the length;
 *        the point struct should have [] opeartor to get the coordinate.
 */
template<typename Polygon, typename NumberType>
void area_2d(const Polygon& poly, NumberType& result)
{
    /* use the Shoelace formula */
    result = NumberType(0);
    for(size_t i = 0, j = 1; i < poly.size(); ++i, ++j, j%=poly.size())
    {
        result += ( poly[i][0] * poly[j][1] - poly[j][0] * poly[i][1]);
    }
    result /= NumberType(2);
}

/**
 * @brief calculate polygon area from iterator range from point container.
 * @tparam ForwardIterator point container's iterator
 * @tparam NumberType type of point coordinate 
 * @param result the polygon area
 * @note the point must has operator[] method to get coordinate
 */
template<typename ForwardIterator, typename NumberType>
void area_2d(ForwardIterator begin, ForwardIterator end, NumberType& result)
{
    /* use the Shoelace formula */
    result = NumberType(0);
    if(begin == end)
        return;
    ForwardIterator first = begin;
    ForwardIterator second = first; ++second;
    if(second == end)
        return;
    while(first != end)
    {
        result += (first->operator[](0) * second->operator[](1) - second->operator[](0) * first->operator[](1));
        ++first;
        ++second;
        if(second == end)
            second = begin;
    }
    result /= NumberType(2);
}

}   // namespace algorithm
}   // namespace CMTL

#endif  // __algorithm_area__