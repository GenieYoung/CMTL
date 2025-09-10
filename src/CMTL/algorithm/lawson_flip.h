#ifndef __algorithm_lawson_flip__
#define __algorithm_lawson_flip__

#include "../geo2d/surface_mesh.h"
#include "predicate.h"
#include <queue>

namespace CMTL{
namespace algorithm{

/**
 * @brief remove locally non-delaunay edges in surface mesh
 * @param sm surface mesh need flip
 * @param constrained_edges fixed edges
 */
template<typename T>
void lawson_flip(geo2d::SurfaceMesh<T>& sm, const std::vector<typename geo2d::SurfaceMesh<T>::EdgeHandle>& constrained_edges = {})
{
    typedef typename geo2d::SurfaceMesh<T>::VertexHandle    VertexHandle;
    typedef typename geo2d::SurfaceMesh<T>::HalfedgeHandle  HalfedgeHandle;
    typedef typename geo2d::SurfaceMesh<T>::EdgeHandle      EdgeHandle;

    std::vector<unsigned> edge_constrained_flag(sm.n_edges(), 0);
    for(unsigned ce = 0; ce < constrained_edges.size(); ++ce)
        edge_constrained_flag[constrained_edges[ce].idx()] = 1;

    auto conditional_push = [&edge_constrained_flag](std::queue<EdgeHandle>& queue, EdgeHandle eh){
        if(edge_constrained_flag[eh.idx()] != 1)
            queue.push(eh);
    };

    std::queue<EdgeHandle> queue;
    for(auto eit = sm.edges_begin(); eit != sm.edges_end(); ++eit)
        conditional_push(queue, *eit);

    while(!queue.empty())
    {
        EdgeHandle eh = queue.front();
        queue.pop();
        if(sm.is_boundary(eh))
            continue;
        HalfedgeHandle h0 = sm.halfedge_handle(eh, 0);
        HalfedgeHandle h1 = sm.halfedge_handle(eh, 1);
        VertexHandle v0 = sm.from_vertex_handle(h0);
        VertexHandle v1 = sm.to_vertex_handle(h0);
        VertexHandle va = sm.to_vertex_handle(sm.next_halfedge_handle(h0));
        VertexHandle vb = sm.to_vertex_handle(sm.next_halfedge_handle(h1));
        if(!is_locally_delaunay(sm.point(va), sm.point(v0), sm.point(v1), sm.point(vb)) && sm.is_flip_ok(eh))
        {
            sm.flip(eh);
            conditional_push(queue, sm.edge_handle(sm.next_halfedge_handle(h0)));
            conditional_push(queue, sm.edge_handle(sm.prev_halfedge_handle(h0)));
            conditional_push(queue, sm.edge_handle(sm.next_halfedge_handle(h1)));
            conditional_push(queue, sm.edge_handle(sm.prev_halfedge_handle(h1)));
        }
    }

#if 0
    // check
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
        assert(!sm.is_flip_ok(*eit) || is_locally_delaunay(sm.point(va), sm.point(v0), sm.point(v1), sm.point(vb)));
    }
#endif
}

}   // namespace algorithm
}   // namespace CMTL

#endif  // __algorithm_lawson_flip__
