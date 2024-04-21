#ifndef __topologic_halfedge_h__
#define __topologic_halfedge_h__

#include <vector>
#include <cassert>
#include <iostream>

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
    friend class TopoGraphBase;
    HalfedgeHandle _halfedge_handle;
};

/**
 * @brief half edge item
 */
class HalfedgeItem
{
    friend class TopoGraphBase;
    FaceHandle _face_handle;
    VertexHandle _vertex_handle;
    HalfedgeHandle _prev_halfedge_handle;
    HalfedgeHandle _next_halfedge_handle;
};

/**
 * @brief edge item
 */
class EdgeItem
{
    friend class TopoGraphBase;
    HalfedgeItem _halfedges[2];
};

/**
 * @brief face item
 */
class FaceItem
{
    friend class TopoGraphBase;
    HalfedgeHandle _halfedge_handle;
};


class TopoGraphBase;

/**
 * @brief elem handle connect to the topology graph, allow access to the graph
 */
class GraphElemHandle
{
    public:
        explicit GraphElemHandle(const TopoGraphBase* graph) : _graph(graph)
        {
        }

        const TopoGraphBase* graph() const
        {
            return _graph;
        }

    private:
        const TopoGraphBase* _graph;
};

/**
 * @brief vertex handle connect to a topology graph
 */
class GraphVertexHandle : public GraphElemHandle, VertexHandle
{
    public:
        explicit GraphVertexHandle(int idx = -1, const TopoGraphBase* graph = nullptr)
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
        explicit GraphEdgeHandle(int idx = -1, const TopoGraphBase* graph = nullptr)
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
        explicit GraphHalfedgeHandle(int idx = -1, const TopoGraphBase* graph = nullptr)
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
        explicit GraphFaceHandle(int idx = -1, const TopoGraphBase* graph = nullptr)
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
 * @brief base struct that store the mesh handle connectivity information.
 */
class TopoGraphBase
{
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
            return _edges[heh.idx() >> 1]._halfedges[heh.idx() & 1];
        }

        /**
         * @brief use halfedge handle to get the halfedge item
         */
        const HalfedgeItem& halfedge(HalfedgeHandle heh) const
        {
            assert(heh.is_valid());
            return _edges[heh.idx() >> 1]._halfedges[heh.idx() & 1];
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

        HalfedgeHandle opposite_halfedge_handle(HalfedgeHandle heh) const
        {
            return(heh.idx()<n_halfedges() ? HalfedgeHandle(heh.idx() ^ 1) : HalfedgeHandle());
        }

        HalfedgeHandle prev_halfedge_handle(HalfedgeHandle heh) const
        {
            return(heh.idx()<n_halfedges() ? halfedge(heh)._prev_halfedge_handle : HalfedgeHandle());
        }

        HalfedgeHandle next_halfedge_handle(HalfedgeHandle heh) const
        {
            return(heh.idx()<n_halfedges() ? halfedge(heh)._next_halfedge_handle : HalfedgeHandle());
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
         * @brief get face handle the halfedge handle lies on
         */
        FaceHandle face_handle(HalfedgeHandle heh) const
        {
            return (heh.idx()<n_halfedges() ? halfedge(heh)._face_handle : FaceHandle());
        }


        /**
         * @brief check if the vertex is a boundary vertex
         */
        bool is_boundary(VertexHandle vh)
        {
            HalfedgeHandle heh(halfedge_handle(vh));
            return !(heh.is_valid() && face_handle(heh).is_valid());
        }

        /**
         * @brief check if a halfedge is a boundary vertex
         */
        bool is_boundary(HalfedgeHandle heh)
        {
            return !face_handle(heh).is_valid();
        }

    public:
        /**
         * @brief add a new vertex
         */
        VertexHandle new_vertex()
        {
            _vertices.push_back(VertexItem());
            return VertexHandle(_vertices.size() - 1);
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
            halfedge(he0)._vertex_handle = end;
            halfedge(he1)._vertex_handle = start;
            return he0;
        }

        /**
         * @brief add a new face
         */
        FaceHandle new_face()
        {
            _faces.push_back(FaceItem());
            return FaceHandle(_faces.size() - 1);
        }

        HalfedgeHandle find_halfedge(VertexHandle start, VertexHandle end)
        {
            return HalfedgeHandle();
        }
        
    private:
        std::vector<VertexItem> _vertices;
        std::vector<EdgeItem>   _edges;
        std::vector<FaceItem>   _faces;
};

/**
 * @brief A graph describe the topological relationship and mesh items of the halfedge data struct
 */
template<class Traits = DefaultTraits>
class TopoGraph : public TopoGraphBase
{
    public:
        typedef typename Traits::PointAttribute       PointAttribute;
        typedef typename Traits::HalfedgeAttribute    HalfedgeAttribute;
        typedef typename Traits::EdgeAttribute        EdgeAttribute;
        typedef typename Traits::FaceAttribute        FaceAttribute;
        
    public:
        GraphVertexHandle add_vertex(const PointAttribute& p_attr)
        {
            VertexHandle vh = new_vertex();
            vertex_attribute(vh) = p_attr;
            return GraphVertexHandle(vh.idx(), this);
        }

        GraphFaceHandle add_face(const std::vector<VertexHandle>& vhs)
        {
            unsigned n = vhs.size();
            assert(n > 2);

            if(_tmp_edge_storage.size() < n)
            {
                _tmp_edge_storage.resize(n);
            }
             
            for(unsigned i = 0, j = 1; i < n; ++i, ++j, j%=n)
            {
                if(!is_boundary(vhs[i]))
                {
                    std::cerr << "Warning : Complex vertex" << std::endl;
                    return GraphFaceHandle(-1, this);
                }
                _tmp_edge_storage[i].halfedge_handle = find_halfedge(vhs[i], vhs[j]);
                _tmp_edge_storage[i].is_new = !_tmp_edge_storage[i].halfedge_handle.is_valid();
                if(!_tmp_edge_storage[i].is_new && !is_boundary(_tmp_edge_storage[i].halfedge_handle))
                {
                    std::cerr << "Warning : Complex edge" << std::endl;
                    return GraphFaceHandle(-1, this);
                }
            }

            for(unsigned i = 0, j = 1; i < n; ++i, ++j, j%=n)
            {
                if(_tmp_edge_storage[i].is_new)
                    _tmp_edge_storage[i].halfedge_handle = new_edge(vhs[i], vhs[j]);
            }

            FaceHandle fh(new_face());
            face(fh)._halfedge_handle = _tmp_edge_storage[n-1].halfedge_handle;

            for(unsigned i = 0, j = 1; i < n; ++i, ++j, j%=n)
            {
                VertexHandle vh = vhs[j];
                HalfedgeHandle inner_prev_he = _tmp_edge_storage[i].halfedge_handle;
                HalfedgeHandle inner_next_he = _tmp_edge_storage[j].halfedge_handle;
                assert(inner_prev_he.is_valid());
                assert(inner_next_he.is_valid());

                unsigned flag = 0;
                if(_tmp_edge_storage[i].is_new) flag |= 1;
                if(_tmp_edge_storage[j].is_new) flag |= 2;

                if(flag)
                {
                    HalfedgeHandle outer_prev_he = opposite_halfedge_handle(inner_next_he);
                    HalfedgeHandle outer_next_he = opposite_halfedge_handle(inner_prev_he);
                    assert(outer_prev_he.is_valid());
                    assert(outer_next_he.is_valid());
                    switch(flag)
                    {
                        case 1:
                            HalfedgeHandle boundary_prev_he = prev_halfedge_handle(inner_next_he);
                            assert(boundary_prev_he.is_valid());
                            vertex(vh)._halfedge_handle = outer_next_he;
                            break;
                        case 2:
                            HalfedgeHandle boundary_next_he = prev_halfedge_handle(inner_prev_he);
                            assert(boundary_next_he.is_valid());
                            vertex(vh)._halfedge_handle = boundary_next_he;
                            break;
                        case 3:
                            if(!halfedge_handle(vh).is_valid())
                            {
                                vertex(vh)._halfedge_handle = outer_next_he;
                            }
                            else
                            {
                                HalfedgeHandle boundary_next_he = halfedge_handle(vh);
                                HalfedgeHandle boundary_prev_he = prev_halfedge_handle(boundary_next_he);
                                assert(boundary_next_he.is_valid());
                                assert(boundary_prev_he.is_valid());
                            }
                            break;
                    }
                }
                else
                {
                    _tmp_edge_storage[j].need_adjust = (halfedge_handle(vh) == inner_next_he);
                }

                halfedge(_tmp_edge_storage[i].halfedge_handle)._face_handle = fh;
            }
        }

    public:
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

    private:
        struct AddFaceEdgeStorage
        {
            HalfedgeHandle halfedge_handle;
            bool is_new;
            bool need_adjust;
        };
        std::vector<AddFaceEdgeStorage> _tmp_edge_storage;

    private:
        std::vector<PointAttribute>    _vertex_attr;
        std::vector<HalfedgeAttribute> _halfedge_attr;
        std::vector<EdgeAttribute>     _edge_attr;
        std::vector<FaceAttribute>     _face_attr;
};

/**
 * @brief A graph describe the topological relationship of the halfedge data struct
 */
// class TopoGraph
// {
//     private:
//         static const VertexHandle InvalidVertexHandle;     
//         static const HalfedgeHandle InvalidHalfedgeHandle;
//         static const EdgeHandle InvalidEdgeHandle;
//         static const FaceHandle InvalidFaceHandle;
// };

// const VertexHandle    TopoGraph::InvalidVertexHandle;
// const HalfedgeHandle  TopoGraph::InvalidHalfedgeHandle;
// const EdgeHandle      TopoGraph::InvalidEdgeHandle;
// const FaceHandle      TopoGraph::InvalidFaceHandle;

}   // namespace topologic
}   // namespace geometry
}   // namespace CMTL

#endif // __topologic_halfedge_h__