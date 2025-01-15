#ifndef __geo2d_segment_h__
#define __geo2d_segment_h__

#include "geo2d_point.h"

namespace CMTL{
namespace geo2d{

/**
 * @brief 2 dimension segment
 * @tparam T number type of point coordinate 
 */
template<typename T>
class Segment
{
    public:
        /**
         * @brief float type
         */
        typedef T FT;

    public:
        Segment() = default;

        /**
         * @brief construct from two point
         * @param p0 first point
         * @param p1 second point
         */
        Segment(const Point<T>& p0, const Point<T>& p1)
            : _first(p0), _second(p1)
        {
        }

        ~Segment() = default;

    public:
        /**
         * @brief get the writable first point
         */
        Point<T>& first()
        {
            return _first;
        }

        /**
         * @brief get the const first point
         */
        const Point<T>& first() const
        {
            return _first;
        }

        /**
         * @brief get the writable second point
         */
        Point<T>& second()
        {
            return _second;
        }

        /**
         * @brief get the const second point
         */
        const Point<T>& second() const
        {
            return _second;
        }

        /**
         * @brief return the direction of the segment
         */
        Point<T> direction() const
        {
            return _second - _first;
        }

        /**
         * @brief get the point with specific parameter
         */
        Point<T> operator()(const T& t) const
        {
            assert(t >= T(0) && t <= T(1));
            return _first * (T(1) - t) + _second * t;
        }

    private:
        Point<T> _first, _second;
};

/**
 * @brief 2 dimension infinite line
 * @tparam T number type of point coordinate 
 */
template<typename T>
class Line
{
    public:
        /**
         * @brief float type
         */
        typedef T FT;

    public:
        Line() = default;

        /**
         * @brief construct from an origin point and a direction
         * @param ori origin point
         * @param direction line direction
         */
        Line(const Point<T>& ori, const Point<T>& direction)
            : _origin(ori), _direction(direction)
        {
        }

        ~Line() = default;

    public:
        /**
         * @brief get the writable origin point
         */
        Point<T>& origin()
        {
            return _origin;
        }

        /**
         * @brief get the const origin point
         */
        const Point<T>& origin() const
        {
            return _origin;
        }

        /**
         * @brief get the writable direction
         */
        Point<T>& direction()
        {
            return _direction;
        }

        /**
         * @brief get the const direction
         */
        const Point<T>& direction() const
        {
            return _direction;
        }

        /**
         * @brief get the point with specific parameter
         */
        virtual Point<T> operator()(const T& t) const
        {
            return _origin + _direction * t;
        }

    protected:
        Point<T> _origin;

        Point<T> _direction;
};

/**
 * @brief 2 dimension ray
 * @tparam T number type of point coordinate 
 */
template<typename T>
class Ray : public Line<T>
{
    public:
        Ray() : Line<T>()
        {
        }
        
        /**
         * @brief construct from an origin point and a direction
         * @param ori origin point
         * @param direction line direction
         */
        Ray(const Point<T>& ori, const Point<T>& direction)
            : Line<T>(ori, direction)
        {
        }

        ~Ray() = default;

    public:
        /**
         * @brief get the point with specific parameter
         */
        virtual Point<T> operator()(const T& t) const override
        {
            assert(t >= T(0));
            return this->_origin + this->_direction * t;
        }
};

}   // namespace geo2d
}   // namespace CMTL

#endif // __geo2d_segment_h__