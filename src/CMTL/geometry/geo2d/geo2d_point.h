#ifndef __geo2d_point_h__
#define __geo2d_point_h__

#include "common/vectorT.h"

#include <iostream>
#include <iomanip>
#include <assert.h>

namespace CMTL{
namespace geometry{
namespace geo2d{

/**
 * @brief 2 dimension point or vector.
 * @tparam T value type of coordinate
*/
template<typename T>
class Point : public VectorT<T, 2, Point<T>>
{
    public:
        /* number type */
        typedef T NT;
        typedef typename VectorT<T, 2, Point<T>>::value_type value_type;

    public:
        using VectorT<T, 2, Point>::VectorT;
        using VectorT<T, 2, Point>::operator=;

        /* constructor */
        Point(const T& x = 0, const T& y = 0) : VectorT<T, 2, Point>(x, y) 
        {
        }

        /* deconstructor */
        ~Point()
        {
        }

    public:
        /* get the writable x coordinate. */
        T& x()  
        {
            return this->operator[](0);
        }

        /* get the const x coordinate. */
        const T& x() const 
        {
            return this->operator[](0);
        }
        
        /* get the writable y coordinate. */
        T& y() 
        {
            return this->operator[](1); 
        }

        /* get the const y coordinate. */
        const T& y() const 
        {
            return this->operator[](1); 
        }

    public:
        /* cross product. */
        T operator%(const Point& p) const
        {
            return x() * p.y() - y() * p.x();
        }

        /* cross product. */
        T cross(const Point& p) const
        {
            return (*this) % p;
        }

        /* check whether this point parallel with other point */
        bool parallel_with(const Point& p) const
        {
            return ((*this) % p) == T(0);
        }
};

template<typename T_IN, typename T_OUT>
Point<T_OUT> point_cast(const Point<T_IN>& p)
{
    return Point<T_OUT>(util_cast<T_IN, T_OUT>(p[0]),
                        util_cast<T_IN, T_OUT>(p[1]));
}

}   // namespace geo2d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo2d_point_h__