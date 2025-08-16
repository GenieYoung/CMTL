#ifndef __geometry_algorithm_box_line_intersect__
#define __geometry_algorithm_box_line_intersect__

#include "../../geo2d/geo2d_segment.h"
#include "../../geo2d/geo2d_box.h"

namespace CMTL{
namespace geometry_algorithm{

template<typename T>
bool intersect(const geo2d::Box<T>& box, 
               const geo2d::Point<T>& ori,
               const geo2d::Point<T>& dir,
               T*& t0,
               T*& t1)
{
    // https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorith

    assert(dir != geo2d::Point<T>::Origin);

    T p1 = -dir.x(), p2 = dir.x(), p3 = -dir.y(), p4 = dir.y();
    T q1 = ori.x()-box.left(), q2 = box.right()-ori.x(), q3 = ori.y()-box.bottom(), q4 = box.top()-ori.y();

    if(p1 == 0 && (q1 < 0 || q2 < 0))
        return false;
    if(p3 == 0 && (q3 < 0 || q4 < 0))
        return false;

    if(p1 != 0)
    {
        T q1_p1 = q1/p1;
        T q2_p2 = q2/p2;
        if(p1 > 0)
        {
            if((t0 && q1_p1 < *t0) || (t1 && q2_p2 > *t1))
                return false;

            if(t1 && q1_p1 < *t1)
                *t1 = q1_p1;
            else if(!t1)
                t1 = new T(q1_p1);

            if(t0 && q2_p2 > *t0)
                *t0 = q2_p2;
            else if(!t0)
                t0 = new T(q2_p2);
        }
        else
        {
            if((t0 && q2_p2 < *t0) || (t1 && q1_p1 > *t1))
                return false;

            if(t1 && q2_p2 < *t1)
                *t1 = q2_p2;
            else if(!t1)
                t1 = new T(q2_p2);

            if(t0 && q1_p1 > *t0)
                *t0 = q1_p1;
            else if(!t0)
                t0 = new T(q1_p1);
        }
    }

    if(p3 != 0)
    {
        T q3_p3 = q3/p3;
        T q4_p4 = q4/p4;
        if(p3 > 0)
        {
            if((t0 && q3_p3 < *t0) || (t1 && q4_p4 > *t1))
                return false;

            if(t1 && q3_p3 < *t1)
                *t1 = q3_p3;
            else if(!t1)
                t1 = new T(q3_p3);

            if(t0 && q4_p4 > *t0)
                *t0 = q4_p4;
            else if(!t0)
                t0 = new T(q4_p4);
        }
        else
        {
            if((t0 && q4_p4 < *t0) || (t1 && q3_p3 > *t1))
                return false;

            if(t1 && q4_p4 < *t1)
                *t1 = q4_p4;
            else if(!t1)
                t1 = new T(q4_p4);

            if(t0 && q3_p3 > *t0)
                *t0 = q3_p3;
            else if(!t0)
                t0 = new T(q3_p3);
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
bool intersect(const geo2d::Box<T>& box, 
               const geo2d::Segment<T>& segment,
               T& t0,
               T& t1)
{
    T* t_min = new T(0);
    T* t_max = new T(1);
    bool result = intersect(box, segment.first(), segment.direction(), t_min, t_max);
    if(result)
    {
        t0 = *t_min;
        t1 = *t_max;
    }
    delete t_min;
    delete t_max;
    return result;
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
    T* t_min = nullptr;
    T* t_max = nullptr;
    bool result = intersect(box, line.origin(), line.direction(), t_min, t_max);
    if(t_min)
    {
        t0 = *t_min;
        delete t_min;
    }
    if(t_max)
    {
        t1 = *t_max;
        delete t_max;
    }
    return result;
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
    T* t_min = new T(0);
    T* t_max = nullptr;
    bool result = intersect(box, ray.origin(), ray.direction(), t_min, t_max);
    if(t_min)
    {
        t0 = *t_min;
        delete t_min;
    }
    if(t_max)
    {
        t1 = *t_max;
        delete t_max;
    }
    return result;
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

}   // namespace geometry_algorithm
}   // namespace CMTL

#endif  // __geometry_algorithm_box_line_intersect__