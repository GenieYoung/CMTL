#ifndef __geo3d_polygon_soup_h__
#define __geo3d_polygon_soup_h__

#include "geo3d_point.h"
#include <vector>

namespace CMTL{
namespace geometry{
namespace geo3d{

/**
 * @brief 3 dimension polygon soup
 * @tparam T value type of point coordinate 
*/
template<typename T>
class PolygonSoup
{
    public:
        /* number type */
        typedef T NT;

    public:
        /* default constructor */
        PolygonSoup() = default;

        /**
         * @brief construct from point container and face container.
         * @tparam PointRange point container
         * @tparam PolygonRange polygon container
         * @note point container must have iterator method and operator[] method to get coordinate, face container must have iterator method.
        */
        template<class PointRange, class PolygonRange>
        PolygonSoup(const PointRange& points, const PolygonRange& polygons)
        {
            for(auto v_it = points.begin(); v_it != points.end(); ++v_it)
            {
                _vertices.emplace_back((*v_it)[0], (*v_it)[1], (*v_it)[2]);
            }
            for(auto f_it = polygons.begin(); f_it != polygons.end(); ++f_it)
            {
                _polygons.emplace_back(f_it->begin(), f_it->end());
            }
        }

        /* copy constructor */
        PolygonSoup(const PolygonSoup& other) = default;

        /* deconstructor */
        ~PolygonSoup() = default;

    public:
        /* return the number of points */
        size_t n_points() const
        {
            return _vertices.size();
        }

        /* return the number of polygons */
        size_t n_polygons() const
        {
            return _polygons.size();
        }

        /* get the ith point */
        Point<T>& point(unsigned i)
        {
            return _vertices[i];
        }

        /* get the const ith point */
        const Point<T>& point(unsigned i) const
        {
            return _vertices[i];
        }

    private:
        std::vector<Point<T>> _vertices;

        std::vector<std::vector<unsigned>> _polygons;
};


/* Implementation */


}   // namespace geo3d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo3d_polygon_soup_h__