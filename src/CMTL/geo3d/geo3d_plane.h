#ifndef __geo3d_plane_h__
#define __geo3d_plane_h__

#include "../geo2d/geo2d_point.h"
#include "geo3d_point.h"
#include "../common/orientation.h"

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
        typedef T NT;

    public:
        /**
         * @brief construct plane from a point on plane and plane normal
         * @param p point on plane
         * @param n plane normal
         */
        Plane(const Point<T>& p, const Point<T>& n) : _origin(p), _normal(n)
        {
            std::pair<unsigned, T> max_abs = _normal.max_abs();
            unsigned max_abs_id = max_abs.first;
            T max_abs_v = _normal[max_abs_id];
            assert(max_abs_v != 0);
            _params[0] = _normal[0] / max_abs_v;
            _params[1] = _normal[1] / max_abs_v;
            _params[2] = _normal[2] / max_abs_v;
            _params[max_abs_id] = T(1); // avoid numerical error
            _params[3] = -(_params[0]*_origin[0] + _params[1]*_origin[1] + _params[2]*_origin[2]);
            unsigned idx = 0;
            for(unsigned i = 0; i < 3; ++i)
            {
                if(i != max_abs_id)
                    _project_cood[idx++] = i;
            }
            _project_cood[idx] = max_abs_id;
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

    private:
        /* a point on the plane */
        Point<T> _origin;

        /* plane normal */
        Point<T> _normal;

        /* parameters of plane function */
        T _params[4];

        /* vector used for tranform from 2d coordinate system and 3d coordinate system */
        unsigned char _project_cood[3];

        /* the normal of local 2d coordinate system */
        Point<T> _project_normal;
};

}   // namespace geo3d
}   // namespace CMTL

#endif // __geo3d_plane_h__