#ifndef __geo2d_triangle_h__
#define __geo2d_triangle_h__

#include "geo2d_point.h"
#include <array>

namespace CMTL{
namespace geo2d{

/**
 * @brief 2 dimension triangle.
 * @tparam T number type of point coordinate 
 */
template<typename T>
class Triangle
{
    public:
        typedef T NT;

    public:
        Triangle() = default;

        /**
         * @brief construct from three points
         * @note the point must have operator[] to get coordinate
         */
        template<typename PointType>
        Triangle(const PointType& p0, const PointType& p1, const PointType& p2)
        {
            _vertices[0][0] = p0[0]; _vertices[0][1] = p0[1];
            _vertices[1][0] = p1[0]; _vertices[1][1] = p1[1];
            _vertices[2][0] = p2[0]; _vertices[2][1] = p2[1];
        }

        ~Triangle() = default;

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

    public:
        /**
         * @brief get the area of the triangle
         */
        T area() const;

    public:
        friend std::ostream& operator<<(std::ostream& os, const Triangle& tri)
        {
            os << tri[0] << " " << tri[1] << " " << tri[2];
            return os;
        }

    private:
        std::array<Point<T>, 3> _vertices;
};

/* Implementation */

template<typename T>
T Triangle<T>::area() const
{
    return (_vertices[1] - _vertices[0])%(_vertices[2] - _vertices[0]) / T(2);
}

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_triangle_h__