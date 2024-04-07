#ifndef __geo2d_triangle_h__
#define __geo2d_triangle_h__

#include "geo2d_point.h"
#include <array>

namespace CMTL  {
namespace geo2d {

/**
 * @brief 2 dimension triangle.
 * @tparam T value type of point coordinate 
 */
template<typename T>
class Triangle
{
    public:
        typedef T _value_type;

    public:
        /**
         * @brief default constructor
        */
        Triangle()
        {
        }

        /**
         * @brief construct from three points
         */
        Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3)
                : _vertices(p1, p2, p3)
        {
        }

    public:
        /**
         * @brief return the number of points
         */
        size_t size() const
        {
            return 3;
        }

        /**
         * @brief get the writable ith point
         */
        Point<T>& operator[](unsigned int i)
        {
            return _vertices[i];
        }

        /**
         * @brief get the const ith point
         */
        const Point<T>& operator[](unsigned int i) const
        {
            return _vertices[i];
        }

        /**
         * @brief get the writable ith point with range check
         */
        Point<T>& at(unsigned int i)
        {
            assert(i < 3);
            return _vertices[i];
        }

        /**
         * @brief get the const ith point with range check
         */
        const Point<T>& at(unsigned int i) const
        {
            assert(i < 3);
            return _vertices[i];
        }

    public:
        /**
         * @brief get the area of the triangle
         */
        T area() const;

    public:
        /**
         * @brief formatted print.
        */
        friend std::ostream& operator<<(std::ostream& os, const Triangle& tri)
        {
            os << tri[0] << " " << tri[1] << " " << tri[2];
            return os;
        }

    private:
        std::array<Point<T>, 3> _vertices;
};

template<typename T>
T Triangle<T>::area() const
{
    return (_vertices[1] - _vertices[0])%(_vertices[2] - _vertices[0]) / T(2);
}

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_triangle_h__