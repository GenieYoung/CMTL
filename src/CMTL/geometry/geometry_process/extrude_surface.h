#ifndef __geometry_process_extrude_surface__
#define __geometry_process_extrude_surface__

#include "geo3d/geo3d_surface_mesh.h"
#include "geo3d/geo3d_polygon_soup.h"
#include "normal.h"

namespace CMTL{
namespace geometry{
namespace geometry_process{

namespace internal{

    template<typename T>
    class surface_extrude_modifier
    {
        public:
            surface_extrude_modifier(const geo3d::SurfaceMesh<T>& input_mesh, const T& shift) 
                : _origin_mesh(input_mesh), _shift(shift)
            {
            }

        public:
            bool execute(geo3d::SurfaceMesh<T>& result_mesh)
            {
                result_mesh.clear();
                _fv_upper_bottom_offset.resize(_origin_mesh.n_faces());
                for(auto f_it = _origin_mesh.faces_begin(); f_it != _origin_mesh.faces_end(); ++f_it)
                {
                    geo3d::Point<T> face_normal = normalize_3d(_origin_mesh.normal(*f_it));
                    for(auto fv_it = _origin_mesh.fv_begin(*f_it); fv_it != _origin_mesh.fv_end(*f_it); ++fv_it)
                    {
                        _fv_upper_bottom_offset[f_it->idx()][fv_it->idx()].first = _origin_mesh.point(*fv_it) + face_normal * _shift;
                        _fv_upper_bottom_offset[f_it->idx()][fv_it->idx()].second = _origin_mesh.point(*fv_it) - face_normal * _shift;
                    }
                }
            }

        private:
            std::vector<std::map<unsigned, std::pair<geo3d::Point<T>, geo3d::Point<T>>>> _fv_upper_bottom_offset;
        
        private:
            const geo3d::SurfaceMesh<T>& _origin_mesh;

            T _shift;
    };

}   // namespace internal

template<typename T>
bool extrude_surface(const geo3d::SurfaceMesh<T>& sm, 
                     const typename geo3d::SurfaceMesh<T>::NT& shift, 
                     geo3d::SurfaceMesh<T>& result)
{
    internal::surface_extrude_modifier<T> modifier(sm, shift);
    return modifier.execute(result);
}

}   // namespace geometry_process
}   // namespace geometry
}   // namespace CMTL

#endif  // __geometry_process_extrude_surface__