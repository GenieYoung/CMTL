#ifndef __geo2d_point_h__
#define __geo2d_point_h__

#include <iostream>
#include <iomanip>
#include <assert.h>

namespace CMTL  {
namespace geo2d {

template<typename T>
class Point
{
    public:
        typedef T _value_type;

    public:
        /**
         * @brief constructor.
        */
        Point(const T& x = 0, const T& y = 0) : _x(x), _y(y) {}

        /**
         * @brief copy constructor
        */
        Point(const Point& p)
        {
            _x = p._x;
            _y = p._y;
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
         * @brief get the writable ith coordinate.
        */
        T& operator[](unsigned int i)
        {
            if(i == 0)  return _x;
            if(i == 1)  return _y;
            assert(false);
        }

        /**
         * @brief get the const ith coordinate.
        */
        const T& operator[](unsigned int i) const
        {
            if(i == 0)  return _x;
            if(i == 1)  return _y;
            assert(false);
        }

    public:
        /**
         * @brief add two point.
        */
        Point operator+(const Point& p) const
        {
            return Point(_x + p._x, _y + p._y);
        }

        /**
         * @brief self-addition.
        */
        const Point& operator+=(const Point& p)
        {
            _x += p._x;
            _y += p._y;
            return *this;
        }

        /**
         * @brief subtract two point.
        */
        Point operator-(const Point& p) const
        {
            return Point(_x - p._x, _y - p._y);
        }

        /**
         * @brief self-subtract.
        */
        const Point& operator-=(const Point& p)
        {
            _x -= p._x;
            _y -= p._y;
            return *this;
        }

        /**
         * @brief do scale by multiply.
        */
        Point operator*(T scale) const
        {
            return Point(_x * scale, _y * scale);
        }

        /**
         * @brief self-scale by multiply.
        */
        const Point& operator*=(T scale)
        {
            _x *= scale;
            _y *= scale;
            return *this;
        }

        /**
         * @brief do scale by divide.
        */
        Point operator/(T scale) const
        {
            assert(scale != 0);
            return Point(_x / scale, _y / scale);
        }

        /**
         * @brief self-scale by divide.
        */
        const Point& operator/=(T scale)
        {
            assert(scale != 0);
            _x /= scale;
            _y /= scale;
            return *this;
        }

        /**
         * @brief dot product.
        */
        T operator*(const Point& p) const
        {
            return _x * p._x + _y * p._y;
        }

        /**
         * @brief cross product.
        */
        T operator%(const Point& p) const
        {
            return _x * p._y - _y * p._x;
        }

    public:
        /**
         * @brief formatted print.
        */
        friend std::ostream& operator<<(std::ostream& os, const Point& p)
        {
            os << "[" << p._x << ", " << p._y << "]";
            return os;
        }


    private:
        T _x, _y;
};

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_point_h__