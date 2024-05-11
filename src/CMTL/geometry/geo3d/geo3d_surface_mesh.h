#ifndef __geo3d_surface_mesh_h__
#define __geo3d_surface_mesh_h__

#include "topology/halfedge.h"
#include "geo3d_point.h"

namespace CMTL{
namespace geometry{
namespace geo3d{

template<typename T>
struct DefaultSurfaceMeshTraits : public halfedge::DefaultTraits
{
    typedef Point<T> PointAttribute;
};

template<typename T, class Traits = DefaultSurfaceMeshTraits<T>>
class SurfaceMesh : public halfedge::Graph<Traits>
{
    public:
        /* alias */
        typedef halfedge::VertexItem                                            VertexItem;
        typedef halfedge::HalfedgeItem                                          HalfedgeItem;
        typedef halfedge::EdgeItem                                              EdgeItem;
        typedef halfedge::FaceItem                                              FaceItem;

        typedef halfedge::VertexHandle                                          VertexHandle;
        typedef halfedge::HalfedgeHandle                                        HalfedgeHandle;
        typedef halfedge::EdgeHandle                                            EdgeHandle;
        typedef halfedge::FaceHandle                                            FaceHandle;

        typedef typename Traits::PointAttribute                                 PointAttribute;
        typedef typename Traits::HalfedgeAttribute                              HalfedgeAttribute;
        typedef typename Traits::EdgeAttribute                                  EdgeAttribute;
        typedef typename Traits::FaceAttribute                                  FaceAttribute;

        typedef typename halfedge::Graph<Traits>::VertexIter                     VertexIter;
        typedef typename halfedge::Graph<Traits>::HalfedgeIter                   HalfedgeIter;
        typedef typename halfedge::Graph<Traits>::EdgeIter                       EdgeIter;
        typedef typename halfedge::Graph<Traits>::FaceIter                       FaceIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexIter                ConstVertexIter;
        typedef typename halfedge::Graph<Traits>::ConstHalfedgeIter              ConstHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::ConstEdgeIter                  ConstEdgeIter;
        typedef typename halfedge::Graph<Traits>::ConstFaceIter                  ConstFaceIter;

        typedef typename halfedge::Graph<Traits>::VertexVertexIter               VertexVertexIter;
        typedef typename halfedge::Graph<Traits>::VertexVertexCCWIter            VertexVertexCCWIter;
        typedef typename halfedge::Graph<Traits>::VertexVertexCWIter             VertexVertexCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexVertexIter          ConstVertexVertexIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexVertexCCWIter       ConstVertexVertexCCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexVertexCWIter        ConstVertexVertexCWIter;

        typedef typename halfedge::Graph<Traits>::VertexOHalfedgeIter            VertexOHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::VertexOHalfedgeCCWIter         VertexOHalfedgeCCWIter;
        typedef typename halfedge::Graph<Traits>::VertexOHalfedgeCWIter          VertexOHalfedgeCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexOHalfedgeIter       ConstVertexOHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexOHalfedgeCCWIter    ConstVertexOHalfedgeCCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexOHalfedgeCWIter     ConstVertexOHalfedgeCWIter;

    public:
        /* constructor */
        SurfaceMesh()
        {
        }

        /* deconstructor */
        ~SurfaceMesh()
        {
        }

};
    

}   // namespace geo3d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo3d_surface_mesh_h__