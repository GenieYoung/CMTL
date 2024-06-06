#ifndef __geometry_process_offset_surface__
#define __geometry_process_offset_surface__

#include "geo3d/geo3d_surface_mesh.h"
#include "geo3d/geo3d_polygon_soup.h"

namespace CMTL{
namespace geometry{
namespace geometry_process{

template<class Traits>
void offset_surface(const geo3d::SurfaceMesh<Traits>& sm, geo3d::SurfaceMesh<Traits>& offset)
{
    offset.clear();
}

}   // namespace geometry_process
}   // namespace geometry
}   // namespace CMTL

#endif  // __geometry_process_offset_surface__