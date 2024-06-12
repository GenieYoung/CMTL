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

        typedef typename halfedge::Graph<Traits>::VertexEdgeIter                VertexEdgeIter;
        typedef typename halfedge::Graph<Traits>::VertexEdgeCCWIter             VertexEdgeCCWIter;
        typedef typename halfedge::Graph<Traits>::VertexEdgeCWIter              VertexEdgeCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexEdgeIter           ConstVertexEdgeIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexEdgeCCWIter        ConstVertexEdgeCCWIter;
        typedef typename halfedge::Graph<Traits>::ConstVertexEdgeCWIter         ConstVertexEdgeCWIter;

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

    public:
        Point normal(FaceHandle fh) const
        {
            /* Newells algorithm */
            T x = T(0), y = T(0), z = T(0);
            auto first_v = this->fv_begin(fh);
            auto second_v = this->fv_begin(fh);
            ++second_v;
            assert(first_v != second_v);
            for(; first_v != this->fv_end(fh); ++first_v, ++second_v)
            {
                x += ((this->point(*first_v).z() + this->point(*second_v).z())*(this->point(*first_v).y() - this->point(*second_v).y()));
                y += ((this->point(*first_v).x() + this->point(*second_v).x())*(this->point(*first_v).z() - this->point(*second_v).z()));
                z += ((this->point(*first_v).y() + this->point(*second_v).y())*(this->point(*first_v).x() - this->point(*second_v).x()));
            }
            return Point(x, y, z);
        }

        bool is_triangle_mesh() const
        {
            for(auto f_it = this->faces_begin(); f_it != this->faces_end(); ++f_it)
            {
                unsigned count = 0;
                for(auto fv_it = this->fv_begin(*f_it); fv_it != this->fv_end(*f_it); ++fv_it)
                {
                    if(count++ > 3)
                        return false;
                }
            }
            return true;
        }
};
    
}   // namespace geo3d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo3d_surface_mesh_h__