#ifndef __geo3d_point_h__
#define __geo3d_point_h__

#include "common/vectorT.h"

#include <iostream>
#include <iomanip>
#include <assert.h>

namespace CMTL{
namespace geometry{
namespace geo3d{

/**
 * @brief 3 dimension point or vector.
 * @tparam T value type of coordinate
*/
template<typename T>
class Point : public VectorT<T, 3, Point<T>>
{
    public:
        /* number type */
        typedef T NT;
        typedef typename VectorT<T, 3, Point<T>>::value_type value_type;

    public:
        /* constructor. */
        Point(const T& x = 0, const T& y = 0, const T& z = 0) : VectorT<T, 3, Point>(x, y, z) 
        {
        }

        /* copy constructor */
        Point(const Point& other) = default;

        /* copy & cast constructor */
        template<typename TT>
        explicit Point(const Point<TT>& other) : VectorT<T, 3, Point>(other)
        {
        }

        /* default assign operator */
        Point& operator=(const Point& other) = default;

        /* assign & cast operator */
        template<typename TT>
        Point& operator=(const Point<TT>& other)
        {
            VectorT<T, 3, Point>::operator=(other);
            return *this;
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

        /* get the writable z coordinate. */
        T& z() 
        {
            return this->operator[](2); 
        }

        /* get the const y coordinate. */
        const T& z() const 
        {
            return this->operator[](2); 
        }

    public:
        /* cross product. */
        Point operator%(const Point& p) const
        {
            return Point(y()*p.z()-z()*p.y(), z()*p.x()-x()*p.z(), x()*p.y()-y()*p.z());
        }

        /* cross product. */
        Point cross(const Point& p) const
        {
            return (*this) % p;
        }

        /* check whether this point parallel with other point */
        bool parallel_with(const Point& p) const
        {
            return ((*this) % p) == this->Origin;
        }
};

template<typename T_IN, typename T_OUT>
Point<T_OUT> point_cast(const Point<T_IN>& p)
{
    return Point<T_OUT>(util_cast<T_IN, T_OUT>(p[0]),
                        util_cast<T_IN, T_OUT>(p[1]),
                        util_cast<T_IN, T_OUT>(p[2]));
}

}   // namespace geo3d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo3d_point_h__