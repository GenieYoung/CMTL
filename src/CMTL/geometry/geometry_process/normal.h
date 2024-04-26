#ifndef __geometry_process_normal__
#define __geometry_process_normal__

namespace CMTL{
namespace geometry{
namespace geometry_process{

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
    if(poly.size() <= 2)
        return;
    /* Newells algorithm */
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
 *       the result point must have size more than 3 before call this method.
 */
template<typename Point>
void normal(const Point& p0, const Point& p1, const Point& p2, Point& n)
{
    n[0] = (p1[1]-p0[1])*(p2[2]-p1[2])-(p1[2]-p0[2])*(p2[1]-p1[1]);
    n[1] = (p1[2]-p0[2])*(p2[0]-p1[0])-(p1[0]-p0[0])*(p2[2]-p1[2]);
    n[2] = (p1[0]-p0[0])*(p2[1]-p1[1])-(p1[1]-p0[1])*(p2[0]-p1[0]);
}

}   // namespace geometry_process
}   // namespace geometry
}   // namespace CMTL

#endif  // __geometry_process_normal__