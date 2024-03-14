#ifndef __geo2d_polygon_h__
#define __geo2d_polygon_h__

#include "geo2d_point.h"
#include <vector>

namespace CMTL  {
namespace geo2d {

/**
 * @brief 2 dimension closed polygon in counterclockwise order.
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