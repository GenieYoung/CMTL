#ifndef __geo3d_plane_h__
#define __geo3d_plane_h__

#include "../geo2d/geo2d_point.h"
#include "../common/orientation.h"
#include "geo3d_point.h"

namespace CMTL  {
namespace geo3d {

/**
 * @brief 3 dimension infinite plane
 * @tparam T number type of point coordinate 
 * @note suggest use exact number type to avoid numerical error
*/
template<typename T>
class Plane
{
    public:
        /**
         * @brief float type
         */
        typedef T FT;

    public:
        /**
         * @brief construct plane from a point on plane and plane normal
         * @param p point on plane
         * @param n plane normal
         */
        Plane(const Point<T>& p, const Point<T>& n) : _origin(p), _normal(n)
        {
            // we make the maximum absolute value of normal to be 1
            unsigned max_abs_id = _normal.max_abs();
            const T& max_abs = _normal[max_abs_id];
            assert(max_abs != 0 && "the normal of plane should not be zero vector.");
            _params[0] = _normal[0] / max_abs;
            _params[1] = _normal[1] / max_abs;
            _params[2] = _normal[2] / max_abs;
            _params[3] = -(_params[0]*_origin[0] + _params[1]*_origin[1] + _params[2]*_origin[2]);
            _params[4] = (max_abs > 0 ? T(1) : T(-1));

            // build the coordinate plane which has the most similar normal, used for projecting between 2d and 3d
            if(max_abs_id == 0)
                _project_cood = {1, 2, 0};
            else if(max_abs_id == 1)
                _project_cood = {0, 2, 1};
            else
                _project_cood = {0, 1, 2};
            _project_normal[max_abs_id] = T(1);
        }

        /**
         * @brief construct plane from three points on plane
         */
        Plane(const Point<T>& p0, const Point<T>& p1, const Point<T>& p2) : Plane(p0, (p1 - p0) % (p2 - p0))
        {
        }

        ~Plane() = default;

    public:
        /**
         * @brief get the plane normal
         */
        const Point<T>& normal() const
        {
            return _normal;
        }


        /**
         * @brief project a plane point to a local 2d coordinate system, 
         *        the 2d coordinate system is a plane parallel with xy/xz/yz coordinate plane, decide by _project_normal
         */
        geo2d::Point<T> project_2d(const Point<T>& p) const
        {
            return geo2d::Point<T>(p[_project_cood[0]], p[_project_cood[1]]);
        }

        /**
         * @brief project a 2d point on the local coordinate system to origin coordinate system
         */
        Point<T> project_3d(const geo2d::Point<T>& p) const
        {
            Point<T> p_;
            p_[_project_cood[0]] = p.x();
            p_[_project_cood[1]] = p.y();
            p_[_project_cood[2]] = 0;
            T t = (_origin - p_) * this->_normal / (this->_normal * _project_normal);
            return p_ + _project_normal * t;
        }

        /**
         * @brief check a point orientation with the plane
         * @return return ORIENTATION::ABOVE if point above plane, ORIENTATION::BELOW if point on the opposite, 
         *         otherwise return ORIENTATION::ON
         */
        ORIENTATION orient(const geo3d::Point<T>& p) const
        {
            T ori = (p - _origin) * _normal;
            if(is_greater(ori, T(0)))
                return ORIENTATION::ABOVE;
            else if(is_less(ori, T(0)))
                return ORIENTATION::BELOW;
            else
                return ORIENTATION::ON;
        }

        /**
         * @brief check whether two planes are equal
         * @param consider_orientation if true, same plane with different orientation will be considered as different
         */
        bool is_equal(const Plane& other, bool consider_orientation = false) const
        {
            if(consider_orientation)
                return _params == other._params;
            else
                return std::equal(_params.begin(), _params.end() - 1, other._params.begin());
        }

        /**
         * @brief less comparator, used for sorting
         * @note same plane with different orientation will be considered as same
         */
        bool operator<(const Plane& other) const
        {
            return std::lexicographical_compare(_params.begin(), _params.end() - 1, 
                    other._params.begin(), other._params.end() - 1);
        }

        /**
         * @brief less comparator, used for sorting, same plane with different orientation will be considered as different
         */
        static bool less_cmp_with_orientation(const Plane& p1, const Plane& p2)
        {
            return p1._params < p2._params;
        }

    public:
        /* a point on the plane */
        Point<T> _origin;

        /* plane normal */
        Point<T> _normal;

        /* normalized parameters of plane function, the last parameter indicates whether the plane is reversed */
        std::array<T, 5> _params;

        /* auxiliary vector used for tranform from 2d coordinate system and 3d coordinate system */
        std::array<unsigned, 3> _project_cood;

        /* the normal of project coordinate plane, used for projecting between 2d and 3d */
        Point<T> _project_normal;
};

}   // namespace geo3d
}   // namespace CMTL

#endif // __geo3d_plane_h__