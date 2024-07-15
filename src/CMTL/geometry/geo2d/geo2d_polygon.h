#ifndef __geo2d_polygon_h__
#define __geo2d_polygon_h__

#include "geo2d_point.h"
#include <vector>

namespace CMTL{
namespace geometry{
namespace geo2d{

/**
 * @brief 2 dimension closed simple polygon
 * @tparam T value type of point coordinate 
 * @note end point not same as first point.
*/
template<typename T>
class Polygon
{
    public:
        /* number type */
        typedef T NT;

    public:
        /* default constructor */
        Polygon() = default;

        /**
         * @brief construct from iterator range of points list.
         * @tparam InputIterator Container iterator.
         * @note the point must have operator[] method to get coordinate
        */
        template<class ForwardIterator>
        Polygon(ForwardIterator first, ForwardIterator second)
        {
            while(first != second)
            {
                _vertices.emplace_back(first->operator[](0), first->operator[](1));
                ++first;
            }
        }

        /* construct from a point list */
        Polygon(const std::vector<Point<T>>& vertices)
        {
            _vertices.assign(vertices.begin(), vertices.end());
        }
        
        /* copy constructor */
        Polygon(const Polygon& poly)
        {
            _vertices.assign(poly._vertices.begin(), poly._vertices.end());
        }

        /* deconstructor */
        ~Polygon() = default;

    public:
        /* return the number of points */
        size_t size() const
        {
            return _vertices.size();
        }

        /* get the writable ith point */
        Point<T>& operator[](unsigned int i)
        {
            return _vertices[i];
        }

        /* get the const ith point */
        const Point<T>& operator[](unsigned int i) const
        {
            return _vertices[i];
        }

        /* get the writable ith point with range check */
        Point<T>& at(unsigned int i)
        {
            assert(i < _vertices.size());
            return _vertices[i];
        }

        /* get the const ith point with range check */
        const Point<T>& at(unsigned int i) const
        {
            assert(i < _vertices.size());
            return _vertices[i];
        }

    public:
        /* get the area of the polygon */
        T area() const;

    public:
        /* formatted print. */
        friend std::ostream& operator<<(std::ostream& os, const Polygon& poly)
        {
            os << "{ ";
            for(const Point<T>& p : poly._vertices)
            {
                os << p << " ";
            }
            os << "}";
            return os;
        }

    private:
        std::vector<Point<T>> _vertices;
};


/* Implementation */

template<typename T>
T Polygon<T>::area() const
{
    /* use the Shoelace formula */
    T result = T(0);
    for(size_t i = 0, j = 1; i < _vertices.size(); ++i, ++j, j%=_vertices.size())
    {
        result += ( _vertices[i].x() * _vertices[j].y() - _vertices[j].x() * _vertices[i].y());
    }
    return result / 2;
}

}   // namespace geo2d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo2d_polygon_h__