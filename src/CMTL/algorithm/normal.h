#ifndef __algorithm_normal__
#define __algorithm_normal__

#include "../geo3d/point.h"

namespace CMTL{
namespace algorithm{

/**
 * @brief compute a normal vector of a 3d simple polygon
 * @tparam Point point type
 * @tparam Polygon point container
 * @note the polygon type should have size method and operator[] to get point,
 *       the point type should have operator[] to get coordinate,
 *       the result point must have size more than 3 before call this method.
 */
template<typename Point, typename Polygon>
void normal(const Polygon& poly, Point& n)
{
    assert(poly.size() >= 3);
    // Newells algorithm
    n[0] = 0; n[1] = 0; n[2] = 0;
    for(unsigned i=0, j=1; i<poly.size(); ++i, ++j, j%=poly.size())
    {
        n[0] += ((poly[i].z() + poly[j].z())*(poly[i].y() - poly[j].y()));
        n[1] += ((poly[i].x() + poly[j].x())*(poly[i].z() - poly[j].z()));
        n[2] += ((poly[i].y() + poly[j].y())*(poly[i].x() - poly[j].x()));
    }
}

/**
 * @brief compute a normal vector of a 3d simple triangle
 * @tparam Point point type
 * @note the point type should have operator[] to get coordinate,
 *       and has a fixed size.
 */
template<typename Point>
Point normal(const Point& p0, const Point& p1, const Point& p2)
{
    Point n;
    n[0] = (p1[1]-p0[1])*(p2[2]-p1[2])-(p1[2]-p0[2])*(p2[1]-p1[1]);
    n[1] = (p1[2]-p0[2])*(p2[0]-p1[0])-(p1[0]-p0[0])*(p2[2]-p1[2]);
    n[2] = (p1[0]-p0[0])*(p2[1]-p1[1])-(p1[1]-p0[1])*(p2[0]-p1[0]);
    return n;
}

/**
 * @brief normalize a point
 * @tparam Point point type
 * @param p input point
 * @return  normalized point
 */
template<typename Point>
Point normalize_3d(const Point& p)
{
    return p / square_root(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
}

// /* template specialization */
// template<>
// geo3d::Point<mpq_class> normalize_3d<geo3d::Point<mpq_class>>(const geo3d::Point<mpq_class>& p)
// {
//     return p / square_root(p.length_square());
// }

}   // namespace algorithm
}   // namespace CMTL

#endif  // __algorithm_normal__