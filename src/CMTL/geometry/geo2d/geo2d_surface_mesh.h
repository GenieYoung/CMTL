#ifndef __geo2d_surface_mesh_h__
#define __geo2d_surface_mesh_h__

#include "../topology/halfedge.h"
#include "../../common/attributes.h"
#include "geo2d_point.h"

namespace CMTL{
namespace geometry{
namespace geo2d{

/**
 * @brief surface mesh traits, user specified traits should inherit this class and override these members.
 * @tparam T point coordinate type
 */
template<typename T>
struct SurfaceMeshTraits : public halfedge::DefaultTraits
{
    typedef geo2d::Point<T> Point;
    /* attributes attach to a vertex */
    typedef Attributes VertexAttribute;
    /* attributes attach to a halfedge */
    typedef Attributes HalfedgeAttribute;
    /* attributes attach to an edge */
    typedef Attributes EdgeAttribute;
    /* attributes attach to a face */
    typedef Attributes FaceAttribute;
};

/**
 * @brief a halfedge data structure used to represent a polyhedral surface
 * @tparam T point coordinate type
 */
template<typename T>
class SurfaceMesh : public halfedge::Graph<SurfaceMeshTraits<T>>
{
    public:
        /* alias */
        typedef T                                       NT;
        typedef SurfaceMeshTraits<T>                    Traits;
        
        typedef halfedge::HalfedgeItem                  HalfedgeItem;
        typedef halfedge::EdgeItem                      EdgeItem;
        typedef halfedge::FaceItem                      FaceItem;

        typedef halfedge::VertexHandle                  VertexHandle;
        typedef halfedge::HalfedgeHandle                HalfedgeHandle;
        typedef halfedge::EdgeHandle                    EdgeHandle;
        typedef halfedge::FaceHandle                    FaceHandle;

        typedef halfedge::GraphVertexHandle             MeshVertexHandle;
        typedef halfedge::GraphHalfedgeHandle           MeshHalfedgeHandle;
        typedef halfedge::GraphEdgeHandle               MeshEdgeHandle;
        typedef halfedge::GraphFaceHandle               MeshFaceHandle;

        typedef typename Traits::Point                  Point;
        typedef typename Traits::VertexAttribute        VertexAttribute;
        typedef typename Traits::HalfedgeAttribute      HalfedgeAttribute;
        typedef typename Traits::EdgeAttribute          EdgeAttribute;
        typedef typename Traits::FaceAttribute          FaceAttribute;

        typedef halfedge::VertexIter                    VertexIter;
        typedef halfedge::HalfedgeIter                  HalfedgeIter;
        typedef halfedge::EdgeIter                      EdgeIter;
        typedef halfedge::FaceIter                      FaceIter;
        typedef halfedge::ConstVertexIter               ConstVertexIter;
        typedef halfedge::ConstHalfedgeIter             ConstHalfedgeIter;
        typedef halfedge::ConstEdgeIter                 ConstEdgeIter;
        typedef halfedge::ConstFaceIter                 ConstFaceIter;

        typedef halfedge::VertexVertexIter              VertexVertexIter;
        typedef halfedge::VertexVertexCCWIter           VertexVertexCCWIter;
        typedef halfedge::VertexVertexCWIter            VertexVertexCWIter;
        typedef halfedge::ConstVertexVertexIter         ConstVertexVertexIter;
        typedef halfedge::ConstVertexVertexCCWIter      ConstVertexVertexCCWIter;
        typedef halfedge::ConstVertexVertexCWIter       ConstVertexVertexCWIter;

        typedef halfedge::VertexOHalfedgeIter           VertexOHalfedgeIter;
        typedef halfedge::VertexOHalfedgeCCWIter        VertexOHalfedgeCCWIter;
        typedef halfedge::VertexOHalfedgeCWIter         VertexOHalfedgeCWIter;
        typedef halfedge::ConstVertexOHalfedgeIter      ConstVertexOHalfedgeIter;
        typedef halfedge::ConstVertexOHalfedgeCCWIter   ConstVertexOHalfedgeCCWIter;
        typedef halfedge::ConstVertexOHalfedgeCWIter    ConstVertexOHalfedgeCWIter;

        typedef halfedge::VertexEdgeIter                VertexEdgeIter;
        typedef halfedge::VertexEdgeCCWIter             VertexEdgeCCWIter;
        typedef halfedge::VertexEdgeCWIter              VertexEdgeCWIter;
        typedef halfedge::ConstVertexEdgeIter           ConstVertexEdgeIter;
        typedef halfedge::ConstVertexEdgeCCWIter        ConstVertexEdgeCCWIter;
        typedef halfedge::ConstVertexEdgeCWIter         ConstVertexEdgeCWIter;

        typedef halfedge::VertexFaceIter                VertexFaceIter;
        typedef halfedge::VertexFaceCCWIter             VertexFaceCCWIter;
        typedef halfedge::VertexFaceCWIter              VertexFaceCWIter;
        typedef halfedge::ConstVertexFaceIter           ConstVertexFaceIter;
        typedef halfedge::ConstVertexFaceCCWIter        ConstVertexFaceCCWIter;
        typedef halfedge::ConstVertexFaceCWIter         ConstVertexFaceCWIter;

        typedef halfedge::FaceHalfedgeIter              FaceHalfedgeIter;
        typedef halfedge::FaceHalfedgeCCWIter           FaceHalfedgeCCWIter;
        typedef halfedge::FaceHalfedgeCWIter            FaceHalfedgeCWIter;
        typedef halfedge::ConstFaceHalfedgeIter         ConstFaceHalfedgeIter;
        typedef halfedge::ConstFaceHalfedgeCCWIter      ConstFaceHalfedgeCCWIter;
        typedef halfedge::ConstFaceHalfedgeCWIter       ConstFaceHalfedgeCWIter;

    public:
        /* constructor */
        SurfaceMesh() = default;

        /* deconstructor */
        ~SurfaceMesh() = default;

    public:
        /* check whether the mesh is a triangle mesh */
        bool is_triangle_mesh() const
        {
            return this->has_constant_face_degree(3);
        }
    
    public:
        /**
         * @brief split an edge on point p, split the adjacent faces when split_face is true
         * @note split_face only works if all the adjacent faces have degree 3
         */
        void split(EdgeHandle eh, const Point& p, bool split_face = true)
        {
            
        }
};
    
}   // namespace geo2d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo2d_surface_mesh_h__