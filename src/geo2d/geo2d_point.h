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
         * @brief get the ith coordinate.
        */
        T& operator[](unsigned int i)
        {
            if(i == 0)  return _x;
            if(i == 1)  return _y;
            assert(false);
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