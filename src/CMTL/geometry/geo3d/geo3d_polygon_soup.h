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
        /**
         * @brief number type
         */
        typedef T NT;

    public:
        /**
         * @brief default constructor
        */
        PolygonSoup()
        {
        }

        /**
         * @brief construct from point container and face container.
         * @tparam PointRange point container
         * @tparam FaceRange face container
         * @note point container must have iterator method and operator[] method to get coordinate, face container must have iterator method.
        */
        template<class PointRange, class FaceRange>
        PolygonSoup(const PointRange& points, const FaceRange& faces)
        {
            for(auto v_it = points.begin(); v_it != points.end(); ++v_it)
            {
                _vertices.emplace_back((*v_it)[0], (*v_it)[1], (*v_it)[2]);
            }
            for(auto f_it = faces.begin(); f_it != faces.end(); ++f_it)
            {
                _faces.emplace_back(f_it->begin(), f_it->end());
            }
        }

        /**
         * @brief copy constructor
         */
        PolygonSoup(const PolygonSoup& other)
        {
            _vertices.assign(other._vertices.begin(), other._vertices.end());
            _faces.assign(other._faces.begin(), other._faces.end());
        }

        /**
         * @brief deconstructor
         */
        ~PolygonSoup()
        {
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
         * @brief return the number of polygons
         */
        size_t n_faces() const
        {
            return _faces.size();
        }

        /**
         * @brief get the ith point
         */
        Point<T>& point(unsigned i)
        {
            return _vertices[i];
        }

        /**
         * @brief get the const ith point
         */
        const Point<T>& point(unsigned i) const
        {
            return _vertices[i];
        }

    private:
        std::vector<Point<T>> _vertices;

        std::vector<std::vector<unsigned>> _faces;
};


/* Implementation */


}   // namespace geo3d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo3d_polygon_soup_h__