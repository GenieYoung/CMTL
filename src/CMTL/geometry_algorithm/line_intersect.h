#ifndef __geometry_algorithm_line_intersect__
#define __geometry_algorithm_line_intersect__

#include "../geo2d/geo2d_segment.h"
#include "predicate.h"

namespace CMTL{
namespace geometry_algorithm{

/**
 * @brief fast check whether two segments intersect
 * @tparam T float type
 * @param open if true, the segments are open
 * @return true if intersect, otherwise false 
 */
template<typename T>
bool intersect(const geo2d::Segment<T>& seg1, const geo2d::Segment<T>& seg2, bool open = false)
{
    int o1 = static_cast<int>(orient_2d(seg1.first(), seg1.second(), seg2.first()));
    int o2 = static_cast<int>(orient_2d(seg1.first(), seg1.second(), seg2.second()));

    // seg2 lies strictly on one side of seg1
    if(o1 * o2 > 0)
        return false; 
    
    int o3 = static_cast<int>(orient_2d(seg2.first(), seg2.second(), seg1.first()));
    int o4 = static_cast<int>(orient_2d(seg2.first(), seg2.second(), seg1.second()));

    // seg1 lies strictly on one side of seg2
    if(o3 * o4 > 0)
        return false;

    // intersect at inner point
    if(o1*o2 < 0 && o3*o4 < 0)
        return true;

    // intersect at one segment's endpoint
    if(o1 || o2 || o3 || o4)
        return !open;
    
    // coliinear
    T t11, t12, t21, t22;
    T xdiff = absolute(T(seg1.second().x() - seg1.first().x()));
    T ydiff = absolute(T(seg1.second().y() - seg1.first().y()));
    if(xdiff > ydiff)
    {
        t11 = seg1.first().x();
        t12 = seg1.second().x();
        t21 = seg2.first().x();
        t22 = seg2.second().x();
    }
    else
    {
        t11 = seg1.first().y();
        t12 = seg1.second().y();
        t21 = seg2.first().y();
        t22 = seg2.second().y();        
    }
    if(t11 > t12)
        std::swap(t11, t12);
    if(t21 > t22)
        std::swap(t21, t22);
    if(t11 < t21)
        std::swap(t11, t21);
    if(t12 > t22)
        std::swap(t12, t22);
    if(t11 < t12 || (t11 == t12 && !open))
        return true;
    
    return false;
}

}   // namespace geometry_algorithm
}   // namespace CMTL

#endif  // __geometry_algorithm_line_intersect__