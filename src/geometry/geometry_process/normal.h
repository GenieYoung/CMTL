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
    for(unsigned i=0, j=1, k=2; i<poly.size(); ++i, ++j, ++k, j%=poly.size(), k%=poly.size())
    {
        const Point& pi = poly[i];
        const Point& pj = poly[j];
        const Point& pk = poly[k];
        n[0] = (pj[1]-pi[1])*(pk[2]-pj[2])-(pj[2]-pi[2])*(pk[1]-pj[1]);
        n[1] = (pj[2]-pi[2])*(pk[0]-pj[0])-(pj[0]-pi[0])*(pk[2]-pj[2]);
        n[2] = (pj[0]-pi[0])*(pk[1]-pj[1])-(pj[1]-pi[1])*(pk[0]-pj[0]);
        if(n[0]!=0 || n[1]!=0 || n[2]!=0)
            return;
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