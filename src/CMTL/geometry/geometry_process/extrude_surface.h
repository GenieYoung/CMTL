#ifndef __geometry_process_extrude_surface__
#define __geometry_process_extrude_surface__

#include "geo3d/geo3d_surface_mesh.h"
#include "geo3d/geo3d_polygon_soup.h"

namespace CMTL{
namespace geometry{
namespace geometry_process{

template<typename T>
void extrude_surface(const geo3d::SurfaceMesh<T>& sm, 
                     const typename geo3d::SurfaceMesh<T>::NT& shift, 
                     geo3d::SurfaceMesh<T>& result)
{
    result.clear();
}

}   // namespace geometry_process
}   // namespace geometry
}   // namespace CMTL

#endif  // __geometry_process_extrude_surface__