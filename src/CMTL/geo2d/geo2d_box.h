#ifndef __geo2d_box_h__
#define __geo2d_box_h__

#include "geo2d_point.h"

namespace CMTL{
namespace geo2d{

/**
 * @brief 2 dimension axis-aligned box
 * @tparam T number type of point coordinate 
 */
template<typename T>
class Box
{
    public:
        typedef T NT;

    public:
        Box() = default;

        /**
         * @brief construct from two points
         * @param lb left bottom point
         * @param rt right top point
         */
        Box(const Point<T>& lb, const Point<T>& rt)
            : _left_bottom(lb), _right_top(rt)
        {
            // check
            if(_left_bottom.x() > _right_top.x())
                std::swap(_left_bottom.x(), _right_top.x());
            if(_left_bottom.y() > _right_top.y())
                std::swap(_left_bottom.y(), _right_top.y());
        }

        ~Box() = default;

    public:
        /**
         * @brief get the writable left x coordinate
         */
        T& left()
        {
            return _left_bottom.x();
        }

        /**
         * @brief get the const left x coordinate
         */
        const T& left() const
        {
            return _left_bottom.x();
        }

        /**
         * @brief get the writable right x coordinate
         */
        T& right()
        {
            return _right_top.x();
        }

        /**
         * @brief get the const right x coordinate
         */
        const T& right() const
        {
            return _right_top.x();
        }

        /**
         * @brief get the writable bottom y coordinate
         */
        T& bottom()
        {
            return _left_bottom.y();
        }

        /**
         * @brief get the const bottom y coordinate
         */
        const T& bottom() const
        {
            return _left_bottom.y();
        }

        /**
         * @brief get the writable top y coordinate
         */
        T& top()
        {
            return _right_top.y();
        }

        /**
         * @brief get the const top y coordinate
         */
        const T& top() const
        {
            return _right_top.y();
        }

        /**
         * @brief get the writable left bottom point
         */
        Point<T>& left_bottom()
        {
            return _left_bottom;
        }

        /**
         * @brief get the const left bottom point
         */
        const Point<T>& left_bottom() const
        {
            return _left_bottom;
        }

        /**
         * @brief get the writable right top point
         */
        Point<T>& right_top()
        {
            return _right_top;
        }

        /**
         * @brief get the const right top point
         */
        const Point<T>& right_top() const
        {
            return _right_top;
        }

        /**
         * @brief get the left top point
         */
        Point<T> left_top() const
        {
            return Point<T>(left(), top());
        }

        /**
         * @brief get the right bottom point
         */
        Point<T> right_bottom() const
        {
            return Point<T>(right(), bottom());
        }

        /**
         * @brief get the length along x-axis
         */
        T length() const
        {
            return right() - left();
        }

        /**
         * @brief get the width along y-axis
         */
        T width() const
        {
            return top() - bottom();
        }

        /**
         * @brief return the area of the box
         */
        T area() const
        {
            return length() * width();
        }

    private:
        Point<T> _left_bottom;

        Point<T> _right_top;
};

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_box_h__