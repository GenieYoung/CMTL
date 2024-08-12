#ifndef __geometry_process_lawson_flip__
#define __geometry_process_lawson_flip__

#include "geo2d/geo2d_surface_mesh.h"
#include "io/surface_mesh/write_obj.h"
#include "predicate.h"

namespace CMTL{
namespace geometry{
namespace geometry_process{

/**
 * @brief remove locally non-delaunay edges in surface mesh
 * @param sm surface mesh need flip
 */
template<typename T>
void lawson_flip(geo2d::SurfaceMesh<T>& sm)
{
    unsigned count = 0;
    for(auto eit = sm.edges_begin(); eit != sm.edges_end(); ++eit)
    {
        if(sm.is_boundary(*eit))
            continue;
        auto h0 = eit->halfedge(0);
        auto h1 = eit->halfedge(1);
        auto v0 = h0.from_vertex();
        auto v1 = h0.to_vertex();
        auto va = h0.next().to_vertex();
        auto vb = h1.next().to_vertex();
        if(!is_locally_delaunay(sm.point(va), sm.point(v0), sm.point(v1), sm.point(vb)) && sm.is_flip_ok(*eit))
        {
            sm.flip(*eit);
            io::write_obj(sm, std::string("sm_") + std::to_string(count++) + ".obj");
        }
    }
}

}   // namespace geometry_process
}   // namespace geometry
}   // namespace CMTL

#endif  // __geometry_process_lawson_flip__
