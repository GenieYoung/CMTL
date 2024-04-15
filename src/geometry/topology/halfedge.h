#ifndef __topologic_halfedge_h__
#define __topologic_halfedge_h__

#include <vector>
#include <cassert>

namespace CMTL{
namespace geometry{
namespace halfedge{

/**
 * @brief base struct for element handle types
 */
class ElemHandle
{
    public:
        explicit ElemHandle(int idx = -1) : _idx(idx)
        {
        }

        /**
         * @brief get the index of this handle
         */
        int idx() const
        {
            return _idx;
        }

        /**
         * @brief check whether the handle is valid
         */
        bool is_valid() const
        {
            return _idx >= 0;
        }

        /**
         * @brief make the handle invalid
         */
        void invalidate()
        {
            _idx = -1;
        }

        bool operator==(const ElemHandle& other) const
        {
            return _idx == other._idx;
        }

        bool operator!=(const ElemHandle& other) const
        {
            return _idx != other._idx;
        }
        
        bool operator<(const ElemHandle& other) const
        {
            return _idx < other._idx;
        }

    private:
        int _idx;
};

/**
 * @brief handle for a vertex
 */
class VertexHandle : public ElemHandle
{
    public:
        explicit VertexHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/**
 * @brief handle for a half edge
 */
class HalfedgeHandle : public ElemHandle
{
    public:
        explicit HalfedgeHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/**
 * @brief handle for an edge
 */
class EdgeHandle : public ElemHandle
{
    public:
        explicit EdgeHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/**
 * @brief handle for a face
 */
class FaceHandle : public ElemHandle
{
    public:
        explicit FaceHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/**
 * @brief vertex item
 */
class VertexItem 
{
    template<class Traits>
    friend class TopoGraphBase;
    HalfedgeHandle _halfedge_handle;
};

/**
 * @brief half edge item
 */
class HalfedgeItem
{
    template<class Traits>
    friend class TopoGraphBase;
    FaceHandle _face_handle;
    VertexHandle _vertex_handle;
    HalfedgeHandle _next_halfedge_handle;
};

/**
 * @brief edge item
 */
class EdgeItem
{
    template<class Traits>
    friend class TopoGraphBase;
    HalfedgeItem _halfedge_handles[2];
};

/**
 * @brief face item
 */
class FaceItem
{
    template<class Traits>
    friend class TopoGraphBase;
    HalfedgeHandle _halfedge_handle;
};

class TopoGraph;

/**
 * @brief elem handle connect to the topology graph, allow access to the graph
 */
class GraphElemHandle
{
    public:
        explicit GraphElemHandle(const TopoGraph* graph) : _graph(graph)
        {
        }

        const TopoGraph* graph() const
        {
            return _graph;
        }

    private:
        const TopoGraph* _graph;
};

/**
 * @brief vertex handle connect to a topology graph
 */
class GraphVertexHandle : public GraphElemHandle, VertexHandle
{
    public:
        explicit GraphVertexHandle(int idx = -1, const TopoGraph* graph = nullptr)
            : GraphElemHandle(graph), VertexHandle(idx)
        {
        }
};

/**
 * @brief edge handle connect to a topology graph
 */
class GraphEdgeHandle : public GraphElemHandle, EdgeHandle
{
    public:
        explicit GraphEdgeHandle(int idx = -1, const TopoGraph* graph = nullptr)
            : GraphElemHandle(graph), EdgeHandle(idx)
        {
        }
};

/**
 * @brief half edge handle connect to a topology graph
 */
class GraphHalfedgeHandle : public GraphElemHandle, HalfedgeHandle
{
    public:
        explicit GraphHalfedgeHandle(int idx = -1, const TopoGraph* graph = nullptr)
            : GraphElemHandle(graph), HalfedgeHandle(idx)
        {
        }
};

/**
 * @brief face handle connect to a topology graph
 */
class GraphFaceHandle : public GraphElemHandle, FaceHandle
{
    public:
        explicit GraphFaceHandle(int idx = -1, const TopoGraph* graph = nullptr)
            : GraphElemHandle(graph), FaceHandle(idx)
        {
        }
};

/**
 * @brief base class for all traits, usr traits should be derived from this class and override these traits
 */
struct DefaultTraits
{
    typedef int PointAttribute;
    typedef int HalfedgeAttribute;
    typedef int EdgeAttribute;
    typedef int FaceAttribute;
};

/**
 * @brief base struct that store the mesh item arrays.
 */
template<class Traits = DefaultTraits>
class TopoGraphBase
{
    public:
        typedef typename Traits::PointAttribute       PointAttribute;
        typedef typename Traits::HalfedgeAttribute    HalfedgeAttribute;
        typedef typename Traits::EdgeAttribute        EdgeAttribute;
        typedef typename Traits::FaceAttribute        FaceAttribute;

    public:
        TopoGraphBase() 
        {
        };

        virtual ~TopoGraphBase()
        {
        }

    public:
        /**
         * @brief get the number of vertices
         */
        unsigned n_vertices() const
        {
            return _vertices.size();
        }

        /**
         * @brief get the number of edges
         */
        unsigned n_edges() const
        {
            return _edges.size();
        }

        /**
         * @brief get the number of vertices
         */
        unsigned n_halfedges() const
        {
            return _edges.size() * 2;
        }

        /**
         * @brief get the number of faces
         */
        unsigned n_faces() const
        {
            return _faces.size();
        }

        /**
         * @brief use vertex handle to get the vertex item
         */
        VertexItem& vertex(VertexHandle vh)
        {
            assert(vh.is_valid());
            return _vertices[vh.idx()];
        }

        /**
         * @brief use vertex handle to get the vertex item
         */
        const VertexItem& vertex(VertexHandle vh) const
        {
            assert(vh.is_valid());
            return _vertices[vh.idx()];
        }

        /**
         * @brief use halfedge handle to get the halfedge item
         */
        HalfedgeItem& halfedge(HalfedgeHandle heh)
        {
            assert(heh.is_valid());
            return _edges[heh.idx() >> 1]._halfedge_handles[heh.idx() & 1];
        }

        /**
         * @brief use halfedge handle to get the halfedge item
         */
        const HalfedgeItem& halfedge(HalfedgeHandle heh) const
        {
            assert(heh.is_valid());
            return _edges[heh.idx() >> 1]._halfedge_handles[heh.idx() & 1];
        }

        /**
         * @brief use edge handle to get the edge item
         */
        EdgeItem& edge(EdgeHandle eh)
        {
            assert(eh.is_valid());
            return _edges[eh.idx()];
        }

        /**
         * @brief use edge handle to get the edge item
         */
        const EdgeItem& edge(EdgeHandle eh) const
        {
            assert(eh.is_valid());
            return _edges[eh.idx()];
        }
        
        /**
         * @brief use face handle to get the face item
         */
        FaceItem& face(FaceHandle fh)
        {
            assert(fh.is_valid());
            return _faces[fh.idx()];
        }

        /**
         * @brief use face handle to get the face item
         */
        const FaceItem& face(FaceHandle fh) const
        {
            assert(fh.is_valid());
            return _faces[fh.idx()];
        }

        /**
         * @brief get the writable vertex attribute
        */
        PointAttribute& vertex_attribute(VertexHandle vh)
        {
            assert(vh.is_valid() && vh.idx() < n_vertices());
            if(vh.idx() >= _vertex_attr.size())
                _vertex_attr.resize(vh.idx() + 1);
            return _vertex_attr[vh.idx()];
        }

        /**
         * @brief get a const vertex attribute
        */
        const PointAttribute& vertex_attribute(VertexHandle vh) const
        {
            assert(vh.is_valid() && vh.idx() < _vertex_attr.size());
            return _vertex_attr[vh.idx()];
        }

        /**
         * @brief get the writable halfedge attribute
        */
        HalfedgeAttribute& halfedge_attribute(HalfedgeHandle heh)
        {
            assert(heh.is_valid() && heh.idx() < n_halfedges());
            if(heh.idx() >= _halfedge_attr.size())
                _halfedge_attr.resize(heh.idx() + 1);
            return _halfedge_attr[heh.idx()];
        }

        /**
         * @brief get a const halfedge attribute
        */
        const HalfedgeAttribute& halfedge_attribute(HalfedgeHandle heh) const
        {
            assert(heh.is_valid() && heh.idx() < _halfedge_attr.size());
            return _halfedge_attr[heh.idx()];
        }

        /**
         * @brief get the writable edge attribute
        */
        EdgeAttribute& edge_attribute(EdgeHandle eh)
        {
            assert(eh.is_valid() && eh.idx() < n_edges());
            if(eh.idx() >= _edge_attr.size())
                _edge_attr.resize(eh.idx() + 1);
            return _edge_attr[eh.idx()];
        }

        /**
         * @brief get a const edge attribute
        */
        const EdgeAttribute& edge_attribute(EdgeHandle eh) const
        {
            assert(eh.is_valid() && eh.idx() < _edge_attr.size());
            return _edge_attr[eh.idx()];
        }

        /**
         * @brief get the writable face attribute
        */
        FaceAttribute& face_attribute(FaceHandle fh)
        {
            assert(fh.is_valid() && fh.idx() < n_edges());
            if(fh.idx() >= _face_attr.size())
                _face_attr.resize(fh.idx() + 1);
            return _edge_attr[fh.idx()];
        }

        /**
         * @brief get a const edge attribute
        */
        const FaceAttribute& face_attribute(FaceHandle fh) const
        {
            assert(fh.is_valid() && fh.idx() < _face_attr.size());
            return _edge_attr[fh.idx()];
        }

        /**
         * @brief get i'th vertex handle
         */
        VertexHandle vertex_handle(unsigned i) const
        {
            return (i<n_vertices() ? VertexHandle(i) : VertexHandle());
        }

        /**
         * @brief get i'th halfedge handle
         */
        HalfedgeHandle halfedge_handle(unsigned i) const
        {
            return (i<n_halfedges() ? HalfedgeHandle(i) : HalfedgeHandle());
        }

        /**
         * @brief 
         */
        HalfedgeHandle halfedge_handle(VertexHandle vh)
        {
            return vertex(vh)._halfedge_handle;
        }

        /**
         * @brief get halfedge handle with edge handle and a side
         */
        HalfedgeHandle halfedge_handle(EdgeHandle eh, unsigned i) const
        {
            assert(i <= 1);
            return (eh.idx()<n_edges() ? HalfedgeHandle((eh.idx() << 1) + i) : HalfedgeHandle());
        }

        /**
         * @brief get halfedge handle of a face
         */
        HalfedgeHandle halfedge_handle(FaceHandle fh) const
        {
            return (fh.idx()<n_faces() ? face(fh)._halfedge_handle : HalfedgeHandle());
        }

        /**
         * @brief get i'th edge handle
         */
        EdgeHandle edge_handle(unsigned i) const
        {
            return (i<n_edges() ? EdgeHandle(i) : EdgeHandle());
        }

        /**
         * @brief get i'th face handle
         */
        FaceHandle face_handle(unsigned i) const
        {
            return (i<n_faces() ? FaceHandle(i) : FaceHandle());
        }

        /**
         * @brief check if the vertex is a boundary vertex
         */
        bool is_boundary(VertexHandle vh)
        {
            // HalfedgeHandle heh(halfedge_handle(vh));
            return true;
        }

    public:
        /**
         * @brief add a new vertex
         */
        VertexHandle new_vertex()
        {
            _vertices.push_back(VertexItem());
            return vertex_handle(_vertices.size() - 1);
        }

        /**
         * @brief add a new edge
         */
        HalfedgeHandle new_edge(VertexHandle start, VertexHandle end)
        {
            _edges.push_back(EdgeItem());
            EdgeHandle eh(_edges.size() - 1);
            HalfedgeHandle he0 = halfedge_handle(eh, 0);
            HalfedgeHandle he1 = halfedge_handle(eh, 1);
            halfedge(he0)._vertex_handle = start;
            halfedge(he1)._vertex_handle = end;
        }
        
    private:
        std::vector<VertexItem> _vertices;
        std::vector<EdgeItem>   _edges;
        std::vector<FaceItem>   _faces;

    private:
        std::vector<PointAttribute>    _vertex_attr;
        std::vector<HalfedgeAttribute> _halfedge_attr;
        std::vector<EdgeAttribute>     _edge_attr;
        std::vector<FaceAttribute>     _face_attr;
};

/**
 * @brief A graph describe the topological relationship of the halfedge data struct
 */
class TopoGraph
{
    private:
        static const VertexHandle InvalidVertexHandle;     
        static const HalfedgeHandle InvalidHalfedgeHandle;
        static const EdgeHandle InvalidEdgeHandle;
        static const FaceHandle InvalidFaceHandle;
};

const VertexHandle    TopoGraph::InvalidVertexHandle;
const HalfedgeHandle  TopoGraph::InvalidHalfedgeHandle;
const EdgeHandle      TopoGraph::InvalidEdgeHandle;
const FaceHandle      TopoGraph::InvalidFaceHandle;

}   // namespace topologic
}   // namespace geometry
}   // namespace CMTL

#endif // __topologic_halfedge_h__