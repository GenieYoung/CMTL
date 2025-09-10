#ifndef __geo3d_surface_mesh_h__
#define __geo3d_surface_mesh_h__

#include "../topology/halfedge.h"
#include "../common/attributes.h"
#include "point.h"

namespace CMTL{
namespace geo3d{

/**
 * @brief surface mesh traits, user specified traits should inherit this class and override these members.
 */
struct SurfaceMeshTraits : public halfedge::DefaultTraits
{
    /* attributes attach to a vertex */
    typedef Attributes<> VertexAttribute;
    /* attributes attach to a halfedge */
    typedef Attributes<> HalfedgeAttribute;
    /* attributes attach to an edge */
    typedef Attributes<> EdgeAttribute;
    /* attributes attach to a face */
    typedef Attributes<> FaceAttribute;
};

/**
 * @brief a halfedge data structure used to represent a polyhedral surface
 * @tparam T point coordinate type
 * @tparam Traits element attributes, user specified traits should inherit SurfaceMeshTraits and override those members.
 */
template<typename T, class Traits = SurfaceMeshTraits>
class SurfaceMesh : public halfedge::Graph<geo3d::Point<T>, Traits>
{
    public:
        /* alias */
        typedef T                                       FT;
        
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

        typedef geo3d::Point<T>                         Point;
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
        SurfaceMesh() = default;

        ~SurfaceMesh() = default;

    public:
        /**
         * @brief check whether the mesh is a triangle mesh
         */
        bool is_triangle_mesh() const
        {
            return this->has_constant_face_degree(3);
        }

        /**
         * @brief calculate face's barycenter
         */
        Point barycenter(FaceHandle fh) const
        {
            Point p;
            unsigned degree = 0;
            for(auto fv = this->fv_begin(fh); fv != this->fv_end(fh); ++fv)
            {
                p += this->point(*fv);
                degree += 1;
            }
            return p / degree;
        }

        /**
         * @brief calculate a face normal without normalized
         */
        Point normal(FaceHandle fh) const
        {
            // Newells algorithm
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
};
    
}   // namespace geo3d
}   // namespace CMTL

#endif // __geo3d_surface_mesh_h__