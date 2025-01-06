#ifndef __geometry_process_box_line_intersect__
#define __geometry_process_box_line_intersect__

#include "../geo2d/geo2d_segment.h"
#include "../geo2d/geo2d_box.h"

namespace CMTL{
namespace geometry_process{

/**
 * @brief do intersect between a box and a segment
 * @tparam T number type
 * @param t0 first intersect parameter on segment
 * @param t1 second intersect parameter on segment
 * @return true if intersect, otherwise false
 */
template<typename T>
bool intersect(const geo2d::Box<T>& box, 
               const geo2d::Segment<T>& segment,
               T& t0,
               T& t1)
{
    // https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorith
    const geo2d::Point<T>& p0 = segment.first();
    geo2d::Point<T> dir = segment.direction();

    assert(dir != geo2d::Point<T>::Origin);

    T p1 = -dir.x(), p2 = dir.x(), p3 = -dir.y(), p4 = dir.y();
    T q1 = p0.x()-box.left(), q2 = box.right()-p0.x(), q3 = p0.y()-box.bottom(), q4 = box.top()-p0.y();

    if(p1 == 0 && (q1 < 0 || q2 < 0))
        return false;
    if(p3 == 0 && (q3 < 0 || q4 < 0))
        return false;

    t0 = T(0);
    t1 = T(1);

    if(p1 != 0)
    {
        T q1_p1 = q1/p1;
        T q2_p2 = q2/p2;
        if(p1 > 0)
        {
            if(q1_p1 < t0 || q2_p2 > t1)
                return false;
            if(q1_p1 < t1)
                t1 = q1_p1;
            if(q2_p2 > t0)
                t0 = q2_p2;
        }
        else
        {
            if(q1_p1 > t1 || q2_p2 < t0)
                return false;
            if(q1_p1 > t0)
                t0 = q1_p1;
            if(q2_p2 < t1)
                t1 = q2_p2;
        }
    }

    if(p3 != 0)
    {
        T q3_p3 = q3/p3;
        T q4_p4 = q4/p4;
        if(p3 > 0)
        {
            if(q3_p3 < t0 || q4_p4 > t1)
                return false;
            if(q3_p3 < t1)
                t1 = q3_p3;
            if(q4_p4 > t0)
                t0 = q4_p4;
        }
        else
        {
            if(q3_p3 > t1 || q4_p4 < t0)
                return false;
            if(q3_p3 > t0)
                t0 = q3_p3;
            if(q4_p4 < t1)
                t1 = q4_p4;
        }
    }

    return true;
}

/**
 * @brief do intersect between a box and a segment
 * @tparam T number type
 * @param t0 first intersect parameter on segment
 * @param t1 second intersect parameter on segment
 * @return true if intersect, otherwise false
 */
template<typename T>
bool intersect(const geo2d::Segment<T>& segment,
               const geo2d::Box<T>& box, 
               T& t0,
               T& t1)
{
    return intersect(box, segment, t0, t1);
}

/**
 * @brief do intersect between a box and a infinite  line
 * @tparam T number type
 * @param t0 first intersect parameter on line 
 * @param t1 second intersect parameter on line
 * @return true if intersect, otherwise false
 */
template<typename T>
bool intersect(const geo2d::Box<T>& box, 
               const geo2d::Line<T>& line,
               T& t0,
               T& t1)
{
    // https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorith
    const geo2d::Point<T>& p0 = line.origin();
    const geo2d::Point<T>& dir = line.direction();

    assert(dir != geo2d::Point<T>::Origin);

    T p1 = -dir.x(), p2 = dir.x(), p3 = -dir.y(), p4 = dir.y();
    T q1 = p0.x()-box.left(), q2 = box.right()-p0.x(), q3 = p0.y()-box.bottom(), q4 = box.top()-p0.y();

    if(p1 == 0 && (q1 < 0 || q2 < 0))
        return false;
    if(p3 == 0 && (q3 < 0 || q4 < 0))
        return false;

    T negcase[2], poscase[2];
    unsigned negind = 0, posind = 0;

    if(p1 != 0)
    {
        T q1_p1 = q1/p1;
        T q2_p2 = q2/p2;
        if(p1 > 0)
        {
            poscase[posind++] = q1_p1;
            negcase[negind++] = q2_p2;
        }
        else
        {
            negcase[negind++] = q1_p1;
            poscase[posind++] = q2_p2;
        }
    }

    if(p3 != 0)
    {
        T q3_p3 = q3/p3;
        T q4_p4 = q4/p4;
        if(p3 > 0)
        {
            poscase[posind++] = q3_p3;
            negcase[negind++] = q4_p4;
        }
        else
        {
            negcase[negind++] = q3_p3;
            poscase[posind++] = q4_p4;
        }
    }

    assert(negind != 0 && posind != 0);

    if(negind == 1)
        t0 = negcase[0];
    else
        t0 = (negcase[0] > negcase[1] ? negcase[0] : negcase[1]);
    if(posind == 1)
        t1 = poscase[0];
    else
        t1 = (poscase[0] > poscase[1] ? poscase[1] : poscase[0]);

    if(t0 > t1)
        return false;

    return true;
}

/**
 * @brief do intersect between a box and a infinite  line
 * @tparam T number type
 * @param t0 first intersect parameter on line
 * @param t1 second intersect parameter on line
 * @return true if intersect, otherwise false
 */
template<typename T>
bool intersect(const geo2d::Line<T>& line,
               const geo2d::Box<T>& box, 
               T& t0,
               T& t1)
{
    return intersect(box, line, t0, t1);
}

/**
 * @brief do intersect between a box and a ray
 * @tparam T number type
 * @param t0 first intersect parameter on ray
 * @param t1 second intersect parameter on ray
 * @return true if intersect, otherwise false
 */
template<typename T>
bool intersect(const geo2d::Box<T>& box, 
               const geo2d::Ray<T>& ray,
               T& t0,
               T& t1)
{
    // https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorith
    const geo2d::Point<T>& p0 = ray.origin();
    const geo2d::Point<T>& dir = ray.direction();

    assert(dir != geo2d::Point<T>::Origin);

    T p1 = -dir.x(), p2 = dir.x(), p3 = -dir.y(), p4 = dir.y();
    T q1 = p0.x()-box.left(), q2 = box.right()-p0.x(), q3 = p0.y()-box.bottom(), q4 = box.top()-p0.y();

    if(p1 == 0 && (q1 < 0 || q2 < 0))
        return false;
    if(p3 == 0 && (q3 < 0 || q4 < 0))
        return false;

    t0 = T(0);
    T poscase[2];
    unsigned posind = 0;

    if(p1 != 0)
    {
        T q1_p1 = q1/p1;
        T q2_p2 = q2/p2;
        if(p1 > 0)
        {
            if(q1_p1 < t0)
                return false;
            poscase[posind++] = q1_p1;
            if(q2_p2 > t0)
                t0 = q2_p2;
        }
        else
        {
            if(q2_p2 < t0)
                return false;
            poscase[posind++] = q2_p2;
            if(q1_p1 > t0)
                t0 = q1_p1;
        }
    }

    if(p3 != 0)
    {
        T q3_p3 = q3/p3;
        T q4_p4 = q4/p4;
        if(p3 > 0)
        {
            if(q3_p3 < t0)
                return false;
            poscase[posind++] = q3_p3;
            if(q4_p4 > t0)
                t0 = q4_p4;
        }
        else
        {
            if(q4_p4 < t0)
                return false;
            poscase[posind++] = q4_p4;
            if(q3_p3 > t0)
                t0 = q3_p3;
        }
    }

    assert(posind != 0);

    if(posind == 1)
        t1 = poscase[0];
    else
        t1 = (poscase[0] > poscase[1] ? poscase[1] : poscase[0]);

    if(t0 > t1)
        return false;

    return true;
}

/**
 * @brief do intersect between a box and a ray
 * @tparam T number type
 * @param t0 first intersect parameter on ray
 * @param t1 second intersect parameter on ray
 * @return true if intersect, otherwise false
 */
template<typename T>
bool intersect(const geo2d::Ray<T>& ray,
               const geo2d::Box<T>& box, 
               T& t0,
               T& t1)
{
    return intersect(box, ray, t0, t1);
}

}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_box_line_intersect__