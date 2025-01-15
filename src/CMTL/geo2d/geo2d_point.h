#ifndef __geo2d_point_h__
#define __geo2d_point_h__

#include "../common/vectorT.h"

#include <iostream>
#include <iomanip>
#include <assert.h>

namespace CMTL{

/**
 * @brief 2d geometry
 */
namespace geo2d{

/**
 * @brief 2 dimension point or vector.
 * @tparam T number type of coordinate
*/
template<typename T>
class Point : public VectorT<T, 2, Point<T>>
{
    public:
        /**
         * @brief float type
         */
        typedef T FT;

    public:
        using VectorT<T, 2, Point>::VectorT;
        using VectorT<T, 2, Point>::operator=;

        /**
         * @brief construct a 2d point with two coordinates
         */
        Point(const T& x = 0, const T& y = 0) : VectorT<T, 2, Point>(x, y) 
        {
        }

        ~Point() = default;

    public:
        /** 
         * @brief get the writable x coordinate
         */
        T& x()  
        {
            return this->operator[](0);
        }

        /** 
         * @brief get the const x coordinate. 
         */
        const T& x() const 
        {
            return this->operator[](0);
        }
        
        /** 
         * @brief get the writable y coordinate. 
         */
        T& y() 
        {
            return this->operator[](1); 
        }

        /** 
         * @brief get the const y coordinate. 
         */
        const T& y() const 
        {
            return this->operator[](1); 
        }

    public:
        /** 
         * @brief do cross product with another point 
         */
        T operator%(const Point& p) const
        {
            return x() * p.y() - y() * p.x();
        }

        /** 
         * @brief do cross product with another point 
         */
        T cross(const Point& p) const
        {
            return (*this) % p;
        }
};

/**
 * @brief convert a point into another number type
 * @tparam T_IN input point number type
 * @tparam T_OUT output point number type
 * @return point after number type conversion
 * @note we can simpliy use the assign&cast operator in vectorT
 */
template<typename T_IN, typename T_OUT>
Point<T_OUT> point_cast(const Point<T_IN>& p)
{
    return Point<T_OUT>(util_cast<T_IN, T_OUT>(p[0]),
                        util_cast<T_IN, T_OUT>(p[1]));
}

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_point_h__