#ifndef __geo2d_point_h__
#define __geo2d_point_h__

#include <iostream>
#include <iomanip>
#include <assert.h>

namespace geo2d
{

template<typename T>
class PointT
{
    public:
        typedef T _value_type;

    public:
        /**
         * @brief constructor.
        */
        PointT(const T& x = 0, const T& y = 0) : _x(x), _y(y) {}

        /**
         * @brief copy constructor
        */
        PointT(const PointT& p)
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
        PointT operator+(const PointT& p) const
        {
            return PointT(_x + p._x, _y + p._y);
        }

        /**
         * @brief self-addition.
        */
        const PointT& operator+=(const PointT& p)
        {
            _x += p._x;
            _y += p._y;
            return *this;
        }

        /**
         * @brief subtract two point.
        */
        PointT operator-(const PointT& p) const
        {
            return PointT(_x - p._x, _y - p._y);
        }

        /**
         * @brief self-subtract.
        */
        const PointT& operator-=(const PointT& p)
        {
            _x -= p._x;
            _y -= p._y;
            return *this;
        }

        /**
         * do scale by multiply.
        */
        PointT operator*(T scale) const
        {
            return PointT(_x * scale, _y * scale);
        }

        /**
         * self-scale by multiply.
        */
        const PointT& operator*=(T scale)
        {
            _x *= scale;
            _y *= scale;
            return *this;
        }

        /**
         * do scale by divide.
        */
        PointT operator/(T scale) const
        {
            assert(scale != 0);
            return PointT(_x / scale, _y / scale);
        }

        /**
         * self-scale by divide.
        */
        const PointT& operator/=(T scale)
        {
            assert(scale != 0);
            _x /= scale;
            _y /= scale;
            return *this;
        }

        /**
         * dot product.
        */
        T operator*(const PointT& p) const
        {
            return _x * p._x + _y * p._y;
        }

        /**
         * cross product.
        */
        T operator%(const PointT& p) const
        {
            return _x * p._y - _y * p._x;
        }

    public:
        friend std::ostream& operator<<(std::ostream& os, const PointT& p)
        {
            os << "[" << p._x << "," << std::setw(8) << p._y << "]";
            return os;
        }


    private:
        T _x;
        T _y;
};

}
#endif // __geo2d_point_h__