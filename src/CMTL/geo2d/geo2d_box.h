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
            : _left(lb.x()), _right(rt.x()), _bottom(lb.y()), _top(rt.y())
        {
            // check
            if(_left > _right)
                std::swap(_left, _right);
            if(_bottom > _top)
                std::swap(_bottom, _top);
        }

        /**
         * @brief construct from four boundary coordinates
         * @param left left x coordinate
         * @param right right x coordinate
         * @param bottom bottom y coordinate
         * @param top top y coordinate
         */
        Box(const T& left, const T& right, const T& bottom, const T& top)
            : _left(left), _right(right), _bottom(bottom), _top(top)
        {
            // check
            if(_left > _right)
                std::swap(_left, _right);
            if(_bottom > _top)
                std::swap(_bottom, _top);
        }

        ~Box() = default;

    public:
        /**
         * @brief get the writable left x coordinate
         */
        T& left()
        {
            return _left;
        }

        /**
         * @brief get the const left x coordinate
         */
        const T& left() const
        {
            return _left;
        }

        /**
         * @brief get the writable right x coordinate
         */
        T& right()
        {
            return _right;
        }

        /**
         * @brief get the const right x coordinate
         */
        const T& right() const
        {
            return _right;
        }

        /**
         * @brief get the writable bottom y coordinate
         */
        T& bottom()
        {
            return _bottom;
        }

        /**
         * @brief get the const bottom y coordinate
         */
        const T& bottom() const
        {
            return _bottom;
        }

        /**
         * @brief get the writable top y coordinate
         */
        T& top()
        {
            return _top;
        }

        /**
         * @brief get the const top y coordinate
         */
        const T& top() const
        {
            return _top;
        }

        /**
         * @brief get the writable left bottom point
         */
        Point<T> left_bottom()
        {
            return Point<T>(left(), bottom());
        }

        /**
         * @brief get the writable right top point
         */
        Point<T> right_top()
        {
            return Point<T>(right(), top());
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
        T _left, _right, _bottom, _top;
};

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_box_h__