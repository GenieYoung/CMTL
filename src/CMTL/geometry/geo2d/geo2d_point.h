#ifndef __geo2d_point_h__
#define __geo2d_point_h__

#include "common/number_utils.h"

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
class Point
{
    public:
        /* number type */
        typedef T NT;

        /* origin point */
        static Point<T> Origin;

    public:
        /* constructor */
        Point(const T& x = 0, const T& y = 0) : _x(x), _y(y) {}

        /* copy constructor */
        Point(const Point& p)
        {
            _x = p._x;
            _y = p._y;
        }

        /* deconstructor */
        ~Point()
        {
        }

    public:
        /* get the writable x coordinate. */
        T& x()  
        {
            return _x; 
        }

        /* get the const x coordinate. */
        const T& x() const 
        {
            return _x; 
        }
        
        /* get the writable y coordinate. */
        T& y() 
        {
            return _y; 
        }

        /* get the const y coordinate. */
        const T& y() const 
        {
            return _y; 
        }

        /* get the writable ith coordinate. */
        T& operator[](unsigned int i)
        {
            if(i == 0)  return _x;
            if(i == 1)  return _y;
            assert(false);
        }

        /* get the const ith coordinate. */
        const T& operator[](unsigned int i) const
        {
            if(i == 0)  return _x;
            if(i == 1)  return _y;
            assert(false);
        }

    public:
        /* add two point. */
        Point operator+(const Point& p) const
        {
            return Point(_x + p._x, _y + p._y);
        }

        /* self-addition. */
        const Point& operator+=(const Point& p)
        {
            _x += p._x;
            _y += p._y;
            return *this;
        }

        /* subtract two point. */
        Point operator-(const Point& p) const
        {
            return Point(_x - p._x, _y - p._y);
        }

        /* self-subtract. */
        const Point& operator-=(const Point& p)
        {
            _x -= p._x;
            _y -= p._y;
            return *this;
        }

        /* do scale by multiply. */
        Point operator*(T scale) const
        {
            return Point(_x * scale, _y * scale);
        }

        /* self-scale by multiply. */
        const Point& operator*=(T scale)
        {
            _x *= scale;
            _y *= scale;
            return *this;
        }

        /* do scale by divide. */
        Point operator/(T scale) const
        {
            assert(scale != 0);
            return Point(_x / scale, _y / scale);
        }

        /* self-scale by divide. */
        const Point& operator/=(T scale)
        {
            assert(scale != 0);
            _x /= scale;
            _y /= scale;
            return *this;
        }

        /* dot product. */
        T operator*(const Point& p) const
        {
            return _x * p._x + _y * p._y;
        }

        /* dot product. */
        T dot(const Point& p) const
        {
            return _x * p._x + _y * p._y;
        }

        /* cross product. */
        T operator%(const Point& p) const
        {
            return _x * p._y - _y * p._x;
        }

        /* cross product. */
        T cross(const Point& p) const
        {
            return _x * p._y - _y * p._x;
        }

        /* the square length of the point */
        T length_square() const
        {
            return (*this) * (*this);
        }

        /* less comparator, used for sort. */
        bool operator<(const Point& p) const
        {
            if(_x != p._x)  return _x < p._x;
            if(_y != p._y)  return _y < p._y;
            return false;
        }

        /* comparator */
        bool operator==(const Point& p) const
        {
            return _x == p._x && _y == p._y;
        }

        /* comparator */
        bool operator!=(const Point& p) const
        {
            return !(*this == p);
        }

        /* check whether this point parallel with other point */
        bool parallel_with(const Point& p) const
        {
            return ((*this) % p) == Origin;
        }

    public:
        /* formatted print */
        friend std::ostream& operator<<(std::ostream& os, const Point& p)
        {
            os << "[" << to_double(p._x) << ", " << to_double(p._y) << "]";
            return os;
        }


    private:
        T _x, _y;
};

template<typename T>
Point<T> Point<T>::Origin = Point<T>();

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