#ifndef __geo2d_polygon_h__
#define __geo2d_polygon_h__

#include "geo2d_point.h"
#include <vector>

namespace CMTL  {
namespace geo2d {

/**
 * @brief 2 dimension closed simple polygon in counterclockwise order.
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
         * @brief construct from iterator range.
         * @tparam InputIterator Container iterator.
        */
        template<class InputIterator,  class = std::enable_if_t<
                    std::is_base_of< std::input_iterator_tag,
                    typename std::iterator_traits<InputIterator>::iterator_category>{}>>
        Polygon(InputIterator first, InputIterator second)
        {
            while(first != second)
            {
                _vertices.push_back(*(first++));
            }
        }

        /**
         * @brief construct from a point list
        */
        Polygon(const std::vector<Point<T>>& vertices)
        {
            _vertices.assign(vertices.begin(), vertices.end());
        }

    public:
        /**
         * @brief return the number of points
         */
        size_t n_points() const
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
         * @brief formatted print.
        */
        friend std::ostream& operator<<(std::ostream& os, const Polygon& poly)
        {
            for(const Point<T>& p : poly._vertices)
            {
                os << p << " ";
            }
            return os;
        }

    private:
        std::vector<Point<T>> _vertices;
};

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_polygon_h__