#ifndef __geo3d_surface_mesh_h__
#define __geo3d_surface_mesh_h__

#include "topology/halfedge.h"
#include "common/attributes.h"
#include "geo3d_point.h"

namespace CMTL{
namespace geometry{
namespace geo3d{

template<typename T>
struct SurfaceMeshTraits : public halfedge::DefaultTraits
{
    typedef geo3d::Point<T> Point;
    typedef Attributes VertexAttribute;
    typedef Attributes HalfedgeAttribute;
    typedef Attributes EdgeAttribute;
    typedef Attributes FaceAttribute;
};

template<typename T>
class SurfaceMesh : public halfedge::Graph<SurfaceMeshTraits<T>>
{
    public:
        /* alias */
        typedef T                                                               NT;
        typedef SurfaceMeshTraits<T>                                            Traits;
        
        typedef halfedge::VertexItem                                            VertexItem;
        typedef halfedge::HalfedgeItem                                          HalfedgeItem;
        typedef halfedge::EdgeItem                                              EdgeItem;
        typedef halfedge::FaceItem                                              FaceItem;

        typedef halfedge::VertexHandle                                          VertexHandle;
        typedef halfedge::HalfedgeHandle                                        HalfedgeHandle;
        typedef halfedge::EdgeHandle                                            EdgeHandle;
        typedef halfedge::FaceHandle                                            FaceHandle;

        typedef halfedge::GraphVertexHandle                                     Vertex;
        typedef halfedge::GraphHalfedgeHandle                                   Halfedge;
        typedef halfedge::GraphEdgeHandle                                       Edge;
        typedef halfedge::GraphFaceHandle                                       Face;

        typedef typename Traits::Point                                          Point;
        typedef typename Traits::VertexAttribute                                VertexAttribute;
        typedef typename Traits::HalfedgeAttribute                              HalfedgeAttribute;
        typedef typename Traits::EdgeAttribute                                  EdgeAttribute;
        typedef typename Traits::FaceAttribute                                  FaceAttribute;

        typedef typename halfedge::Graph<Traits>::VertexIter                    VertexIter;
        typedef typename halfedge::Graph<Traits>::HalfedgeIter                  HalfedgeIter;
        typedef typename halfedge::Graph<Traits>::EdgeIter                      EdgeIter;
        typedef typename halfedge::Graph<Traits>::FaceIter                      FaceIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexIter               ConstVertexIter;
        typedef typename halfedge::Graph<Traits>::ConstHalfedgeIter             ConstHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::ConstEdgeIter                 ConstEdgeIter;
        typedef typename halfedge::Graph<Traits>::ConstFaceIter                 ConstFaceIter;

        typedef typename halfedge::Graph<Traits>::VertexVertexIter              VertexVertexIter;
        typedef typename halfedge::Graph<Traits>::VertexVertexCCWIter           VertexVertexCCWIter;
        typedef typename halfedge::Graph<Traits>::VertexVertexCWIter            VertexVertexCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexVertexIter         ConstVertexVertexIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexVertexCCWIter      ConstVertexVertexCCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexVertexCWIter       ConstVertexVertexCWIter;

        typedef typename halfedge::Graph<Traits>::VertexOHalfedgeIter           VertexOHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::VertexOHalfedgeCCWIter        VertexOHalfedgeCCWIter;
        typedef typename halfedge::Graph<Traits>::VertexOHalfedgeCWIter         VertexOHalfedgeCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexOHalfedgeIter      ConstVertexOHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexOHalfedgeCCWIter   ConstVertexOHalfedgeCCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexOHalfedgeCWIter    ConstVertexOHalfedgeCWIter;

        typedef typename halfedge::Graph<Traits>::VertexFaceIter                VertexFaceIter;
        typedef typename halfedge::Graph<Traits>::VertexFaceCCWIter             VertexFaceCCWIter;
        typedef typename halfedge::Graph<Traits>::VertexFaceCWIter              VertexFaceCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexFaceIter           ConstVertexFaceIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexFaceCCWIter        ConstVertexFaceCCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexFaceCWIter         ConstVertexFaceCWIter;

        typedef typename halfedge::Graph<Traits>::FaceHalfedgeIter              FaceHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::FaceHalfedgeCCWIter           FaceHalfedgeCCWIter;
        typedef typename halfedge::Graph<Traits>::FaceHalfedgeCWIter            FaceHalfedgeCWIter;
        typedef typename halfedge::Graph<Traits>::ConstFaceHalfedgeIter         ConstFaceHalfedgeIter;
        typedef typename halfedge::Graph<Traits>::ConstFaceHalfedgeCCWIter      ConstFaceHalfedgeCCWIter;
        typedef typename halfedge::Graph<Traits>::ConstFaceHalfedgeCWIter       ConstFaceHalfedgeCWIter;

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