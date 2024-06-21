#ifndef __geo3d_point_h__
#define __geo3d_point_h__

#include "common/number_utils.h"

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
class Point
{
    public:
        /**
         * @brief number type
         */
        typedef T NT;

        /**
         * @brief origin point
         */
        static Point<T> Origin;

    public:
        /**
         * @brief constructor.
        */
        Point(const T& x = 0, const T& y = 0, const T& z = 0) : _x(x), _y(y), _z(z) {}

        /**
         * @brief copy constructor
        */
        Point(const Point& p)
        {
            _x = p._x;
            _y = p._y;
            _z = p._z;
        }

        /**
         * @brief deconstructor
         */
        ~Point()
        {
        }

    public:
        /**
         * @brief get the writable x coordinate.
        */
        T& x()  { return _x; }

        /**
         * @brief get the const x coordinate.
        */
        const T& x() const { return _x; }
        
        /**
         * @brief get the writable y coordinate.
        */
        T& y() { return _y; }

        /**
         * @brief get the const y coordinate.
        */
        const T& y() const { return _y; }

        /**
         * @brief get the writable z coordinate.
        */
        T& z() { return _z; }

        /**
         * @brief get the const y coordinate.
        */
        const T& z() const { return _z; }

        /**
         * @brief get the writable ith coordinate.
        */
        T& operator[](unsigned int i)
        {
            if(i == 0)  return _x;
            if(i == 1)  return _y;
            if(i == 2)  return _z;
            assert(false);
        }

        /**
         * @brief get the const ith coordinate.
        */
        const T& operator[](unsigned int i) const
        {
            if(i == 0)  return _x;
            if(i == 1)  return _y;
            if(i == 2)  return _z;
            assert(false);
        }

    public:
        /**
         * @brief add two point.
        */
        Point operator+(const Point& p) const
        {
            return Point(_x + p._x, _y + p._y, _z + p._z);
        }

        /**
         * @brief self-addition.
        */
        const Point& operator+=(const Point& p)
        {
            _x += p._x;
            _y += p._y;
            _z += p._z;
            return *this;
        }

        /**
         * @brief subtract two point.
        */
        Point operator-(const Point& p) const
        {
            return Point(_x - p._x, _y - p._y, _z - p._z);
        }

        /**
         * @brief self-subtract.
        */
        const Point& operator-=(const Point& p)
        {
            _x -= p._x;
            _y -= p._y;
            _z -= p._z;
            return *this;
        }

        /**
         * @brief do scale by multiply.
        */
        Point operator*(T scale) const
        {
            return Point(_x * scale, _y * scale, _z * scale);
        }

        /**
         * @brief self-scale by multiply.
        */
        const Point& operator*=(T scale)
        {
            _x *= scale;
            _y *= scale;
            _z *= scale;
            return *this;
        }

        /**
         * @brief do scale by divide.
        */
        Point operator/(T scale) const
        {
            assert(scale != 0);
            return Point(_x / scale, _y / scale, _z / scale);
        }

        /**
         * @brief self-scale by divide.
        */
        const Point& operator/=(T scale)
        {
            assert(scale != 0);
            _x /= scale;
            _y /= scale;
            _z /= scale;
            return *this;
        }

        /**
         * @brief dot product.
        */
        T operator*(const Point& p) const
        {
            return _x * p._x + _y * p._y + _z * p._z;
        }

        /**
         * @brief dot product.
        */
        T dot(const Point& p) const
        {
            return _x * p._x + _y * p._y + _z * p._z;
        }

        /**
         * @brief cross product.
        */
        Point operator%(const Point& p) const
        {
            return Point(_y*p._z-_z*p._y, _z*p._x-_x*p._z, _x*p._y-_y*p._x);
        }

        /**
         * @brief cross product.
        */
        Point cross(const Point& p) const
        {
            return Point(_y*p._z-_z*p._y, _z*p.x-_x*p._z, _x*p._y-_y*p._x);
        }

        /**
         * @brief the square length of the point
         */
        T length_square() const
        {
            return (*this) * (*this);
        }

        /**
         * @brief check whether this point parallel with other point
         */
        bool parallel_with(const Point& p) const
        {
            return ((*this) % p) == Origin;
        }

        /**
         * @brief less comparator, used for sort.
        */
        bool operator<(const Point& p) const
        {
            if(_x != p._x)  return _x < p._x;
            if(_y != p._y)  return _y < p._y;
            if(_z != p._z)  return _z < p._z;
            return false;
        }

        /**
         * @brief comparator
         */
        bool operator==(const Point& p) const
        {
            return _x == p._x && _y == p._y && _z == p._z;
        }

        /**
         * @brief comparator
         */
        bool operator!=(const Point& p) const
        {
            return !(*this == p);
        }

    public:
        /**
         * @brief formatted print.
        */
        friend std::ostream& operator<<(std::ostream& os, const Point& p)
        {
            os << "[" << to_double(p._x) << ", " << to_double(p._y) << ", " << to_double(p._z) << "]";
            return os;
        }


    private:
        T _x, _y, _z;
};

template<typename T>
Point<T> Point<T>::Origin = Point<T>();

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