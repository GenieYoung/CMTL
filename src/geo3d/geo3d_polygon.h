#ifndef __geo3d_polygon_h__
#define __geo3d_polygon_h__

#include "geo3d_point.h"
#include <vector>

namespace CMTL  {
namespace geo3d {

/**
 * @brief 3 dimension closed simple polygon
 * @tparam T value type of point coordinate 
 * @note end point not same as first point.
*/
template<typename T>
class Polygon
{
    public:
        typedef T _value_type;

    public:
        /**
         * @brief default constructor
        */
        Polygon()
        {
        }

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
                _vertices.emplace_back(first->operator[](0), first->operator[](1), first->operator[](2));
                ++first;
            }
        }

        /**
         * @brief construct from a point list
        */
        Polygon(const std::vector<Point<T>>& vertices)
        {
            _vertices.assign(vertices.begin(), vertices.end());
        }

        /**
         * @brief copy constructor
         */
        Polygon(const Polygon& poly)
        {
            _vertices.assign(poly._vertices.begin(), poly._vertices.end());
        }

        /**
         * @brief deconstructor
         */
        ~Polygon()
        {
        }

    public:
        /**
         * @brief return the number of points
         */
        size_t size() const
        {
            return _vertices.size();
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
            assert(i < _vertices.size());
            return _vertices[i];
        }

        /**
         * @brief get the const ith point with range check
         */
        const Point<T>& at(unsigned int i) const
        {
            assert(i < _vertices.size());
            return _vertices[i];
        }

    public:
        /**
         * @brief get the square area of the polygon
         */
        T area2() const;

        /**
         * @brief get the normal without normalized
         */
        Point<T> normal() const;

    public:
        /**
         * @brief formatted print.
        */
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
T Polygon<T>::area2() const
{
    /* https://math.stackexchange.com/questions/3207981/how-do-you-calculate-the-area-of-a-2d-polygon-in-3d */
    if(_vertices.size() <= 2 )
        return 0;
    Point<T> p;
    for(size_t i = 1, j = 2; i < _vertices.size()-1; ++i, ++j, j%=_vertices.size())
    {
        p += ((_vertices[i]-_vertices[0]) % (_vertices[j]-_vertices[0]));
    }
    return p.size2() / T(4);
}

template<typename T>
Point<T> Polygon<T>::normal() const
{
    if(_vertices.size() <= 2 )
        return Point<T>();
    #if 0
        /* Newells algorithm */
        T x, y, z;
        for(unsigned i = 0, j = 1; i < _vertices.size(); ++i, ++j, j%=_vertices.size())
        {
            x += ((_vertices[i].z() + _vertices[j].z())*(_vertices[i].y() - _vertices[j].y()));
            y += ((_vertices[i].x() + _vertices[j].x())*(_vertices[i].z() - _vertices[j].z()));
            z += ((_vertices[i].y() + _vertices[j].y())*(_vertices[i].x() - _vertices[j].x()));
        }
        return Point<T>(x, y, z);
    #else
        for(unsigned i=0, j=1, k=2; i<_vertices.size(); ++i, ++j, ++k, j%=_vertices.size(), k%=_vertices.size())
        {
            const Point<T>& pi = _vertices[i];
            const Point<T>& pj = _vertices[j];
            const Point<T>& pk = _vertices[k];
            Point<T> n = (pj-pi) % (pk-pj);
            if(n != Point<T>())
                return n;
        }
    #endif
    return Point<T>();
}

}   // namespace geo3d
}   // namespace CMTL

#endif // __geo3d_polygon_h__