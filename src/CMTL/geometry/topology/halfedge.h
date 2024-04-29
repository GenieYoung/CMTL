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
        /* constructor */
        explicit ElemHandle(int idx = -1) : _idx(idx)
        {
        }

        /* get the index of this handle */
        int idx() const
        {
            return _idx;
        }

        /* check whether the handle is valid */
        bool is_valid() const
        {
            return _idx >= 0;
        }

        /* make the handle invalid */
        void invalidate()
        {
            _idx = -1;
        }

        /* comparator */
        bool operator==(const ElemHandle& other) const
        {
            return _idx == other._idx;
        }

        /* comparator */
        bool operator!=(const ElemHandle& other) const
        {
            return _idx != other._idx;
        }

        /* comparator, used for sort */
        bool operator<(const ElemHandle& other) const
        {
            return _idx < other._idx;
        }

        /* increase the index */
        void forward()
        {
            ++_idx;
        }

        /* decrease the index */
        void backward()
        {
            --_idx;
        }

    private:
        /* the handle index */
        int _idx;
};

/* handle for a vertex */
class VertexHandle : public ElemHandle
{
    public:
        explicit VertexHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/* handle for a half edge */
class HalfedgeHandle : public ElemHandle
{
    public:
        explicit HalfedgeHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/* handle for an edge */
class EdgeHandle : public ElemHandle
{
    public:
        explicit EdgeHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/* handle for a face */
class FaceHandle : public ElemHandle
{
    public:
        explicit FaceHandle(int idx = -1) : ElemHandle(idx)
        {
        }
};

/**
 * @brief vertex item
 * @param _halfedge_handle an outgoing halfedge
 */
class VertexItem 
{
    friend class GraphTopology;
    HalfedgeHandle _halfedge_handle;
};

/**
 * @brief half edge item
 * @param _face_handle face contain this halfedge
 * @param _vertex_handle target vertex
 * @param _prev_halfedge_handle previous halfedge
 * @param _next_halfedge_handle next halfedge
 */
class HalfedgeItem
{
    friend class GraphTopology;
    FaceHandle _face_handle;
    VertexHandle _vertex_handle;
    HalfedgeHandle _prev_halfedge_handle;
    HalfedgeHandle _next_halfedge_handle;
};

/**
 * @brief edge item
 * @param _halfedges two side halfedges
 */
class EdgeItem
{
    friend class GraphTopology;
    HalfedgeItem _halfedges[2];
};

/**
 * @brief face item
 * @param _halfedge_handle a halfedge in this face
 */
class FaceItem
{
    friend class GraphTopology;
    HalfedgeHandle _halfedge_handle;
};


class GraphTopology;

/* elem handle connect to the topology graph, allow access to the graph */
class GraphElemHandle
{
    public:
        explicit GraphElemHandle(const GraphTopology* graph) : _graph(graph)
        {
        }

        const GraphTopology* graph() const
        {
            return _graph;
        }

    private:
        const GraphTopology* _graph;
};

/* vertex handle connect to a topology graph */
class GraphVertexHandle : public GraphElemHandle, public VertexHandle
{
    public:
        explicit GraphVertexHandle(int idx = -1, const GraphTopology* graph = nullptr)
            : GraphElemHandle(graph), VertexHandle(idx)
        {
        }
};

/* edge handle connect to a topology graph */
class GraphEdgeHandle : public GraphElemHandle, public EdgeHandle
{
    public:
        explicit GraphEdgeHandle(int idx = -1, const GraphTopology* graph = nullptr)
            : GraphElemHandle(graph), EdgeHandle(idx)
        {
        }
};

/* half edge handle connect to a topology graph */
class GraphHalfedgeHandle : public GraphElemHandle, public HalfedgeHandle
{
    public:
        explicit GraphHalfedgeHandle(int idx = -1, const GraphTopology* graph = nullptr)
            : GraphElemHandle(graph), HalfedgeHandle(idx)
        {
        }
};

/* face handle connect to a topology graph */
class GraphFaceHandle : public GraphElemHandle, public FaceHandle
{
    public:
        explicit GraphFaceHandle(int idx = -1, const GraphTopology* graph = nullptr)
            : GraphElemHandle(graph), FaceHandle(idx)
        {
        }
};

template <class Topo, class ElemHandle, class GraphElemHandle>
class IteratorBase
{
    public:
        /* default constructor */
        IteratorBase() : _geh(GraphElemHandle(-1, nullptr))
        {
        }

        /* constructor with mesh and a element handle */
        IteratorBase(const Topo* topo, ElemHandle eh) : _geh(GraphElemHandle(eh.idx(), topo))
        {
        }

        /* dereferencing opeartor */
        const GraphElemHandle& operator*() const
        {
            return _geh;
        }

        /* pointer operator */
        const GraphEdgeHandle* operator->() const
        {
            return &_geh;
        }

        /* are two iterator equal? */
        bool operator==(const IteratorBase& other) const
        {
            return ((_geh.graph() == other._geh.graph()) && (_geh == other._geh));
        }

        /* are two iterator not equal? */
        bool operator!=(const IteratorBase& other) const
        {
            return !operator==(other);
        }

        /* pre-increment operator */
        IteratorBase& operator++()
        {
            _geh.forward();
            return *this;
        }

        /* post-increment operator */
        IteratorBase operator++(int)
        {
            IteratorBase copy(*this);
            ++(*this);
            return copy;
        }

        /* pre-decrement operator */
        IteratorBase& operator--()
        {
            _geh.backward();
            return *this;
        }

        /* post-decrement operator */
        IteratorBase operator--(int)
        {
            IteratorBase copy(*this);
            --(*this);
            return copy;
        }

    private:
        GraphElemHandle _geh;
};

template<typename Topo, bool CCW>
class VertexVertexIterBase
{
    public:
        /* default constructor */
        VertexVertexIterBase() : _topo(0), _cycle_count(0)
        {
        }

        VertexVertexIterBase(const Topo* topo, VertexHandle vh, bool end = false)
                         : _topo(topo), _start(_topo->halfedge_handle(vh)), _heh(_start), _cycle_count(static_cast<int>(end))
        {
            if(CCW)
            {
                _heh = _topo->ccw_rotated_halfedge_handle(_heh);
                _start = _heh;
            }
        }

    public:
        /* pre-increment */
        VertexVertexIterBase& operator++()
        {
            if(CCW)
            {
                _heh = _topo->ccw_rotated_halfedge_handle(_heh);
                if(_heh == _start)  
                    ++_cycle_count;
            }
            else
            {
                _heh = _topo->cw_rotated_halfedge_handle(_heh);
                if(_heh == _start)
                    --_cycle_count;
            }
            return *this;
        }

        /* post-increment */
        VertexVertexIterBase operator++(int)
        {
            VertexVertexIterBase copy(*this);
            ++(*this);
            return copy;
        }

        /* pre-decrement */
        VertexVertexIterBase& operator--()
        {
            if(CCW)
            {
                _heh = _topo->cw_rotated_halfedge_handle(_heh);
                if(_heh == _start)  
                    ++_cycle_count;
            }
            else
            {
                _heh = _topo->ccw_rotated_halfedge_handle(_heh);
                if(_heh == _start)
                    --_cycle_count;
            }
            return *this;
        }

        /* post-decrement */
        VertexVertexIterBase operator--(int)
        {
            VertexVertexIterBase copy(*this);
            --(*this);
            return copy;
        }

        /* dereferencing opeartor */
        GraphVertexHandle operator*() const
        {
            return GraphVertexHandle(_topo->to_vertex_handle(_heh).idx(), _topo);
        }

        /* pointer operator */
        GraphVertexHandle* operator->() const
        {
            _geh =  **this;
            return &_geh;
        }

        bool operator==(const VertexVertexIterBase& other) const
        {
            return _topo == other._topo && _heh == other._heh;
        }

        bool operator!=(const VertexVertexIterBase& other) const
        {
            return !operator==(other);
        }


    public:
        const Topo* _topo;
        HalfedgeHandle _start, _heh;
        int _cycle_count;
        mutable GraphVertexHandle _geh;
};

template<typename Topo, bool CCW>
class VertexOHalfedgeIterBase
{
    public:
        /* default constructor */
        VertexOHalfedgeIterBase() : _topo(0), _cycle_count(0)
        {
        }

        VertexOHalfedgeIterBase(const Topo* topo, VertexHandle vh, bool end = false)
                         : _topo(topo), _start(_topo->halfedge_handle(vh)), _heh(_start), _cycle_count(static_cast<int>(end))
        {
            if(CCW)
            {
                _heh = _topo->ccw_rotated_halfedge_handle(_heh);
                _start = _heh;
            }
        }

    public:
        /* pre-increment */
        VertexOHalfedgeIterBase& operator++()
        {
            if(CCW)
            {
                _heh = _topo->ccw_rotated_halfedge_handle(_heh);
                if(_heh == _start)  
                    ++_cycle_count;
            }
            else
            {
                _heh = _topo->cw_rotated_halfedge_handle(_heh);
                if(_heh == _start)
                    --_cycle_count;
            }
            return *this;
        }

        /* post-increment */
        VertexOHalfedgeIterBase operator++(int)
        {
            VertexOHalfedgeIterBase copy(*this);
            ++(*this);
            return copy;
        }

        /* pre-decrement */
        VertexOHalfedgeIterBase& operator--()
        {
            if(CCW)
            {
                _heh = _topo->cw_rotated_halfedge_handle(_heh);
                if(_heh == _start)  
                    ++_cycle_count;
            }
            else
            {
                _heh = _topo->ccw_rotated_halfedge_handle(_heh);
                if(_heh == _start)
                    --_cycle_count;
            }
            return *this;
        }

        /* post-decrement */
        VertexOHalfedgeIterBase operator--(int)
        {
            VertexOHalfedgeIterBase copy(*this);
            --(*this);
            return copy;
        }

        /* dereferencing opeartor */
        GraphHalfedgeHandle operator*() const
        {
            return GraphHalfedgeHandle(_heh.idx(), _topo);
        }

        /* pointer operator */
        GraphHalfedgeHandle* operator->() const
        {
            _geh =  **this;
            return &_geh;
        }

        bool operator==(const VertexOHalfedgeIterBase& other) const
        {
            return _topo == other._topo && _start == other._start && _heh == other._heh && _cycle_count == other._cycle_count;
        }

        bool operator!=(const VertexOHalfedgeIterBase& other) const
        {
            return !operator==(other);
        }


    public:
        const Topo* _topo;
        HalfedgeHandle _start, _heh;
        int _cycle_count;
        mutable GraphHalfedgeHandle _geh;
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
class GraphTopology
{
    public:
        GraphTopology() 
        {
        };

        virtual ~GraphTopology()
        {
        }

        typedef IteratorBase<GraphTopology, VertexHandle,   GraphVertexHandle>      VertexIter;
        typedef IteratorBase<GraphTopology, HalfedgeHandle, GraphHalfedgeHandle>    HalfedgeIter;
        typedef IteratorBase<GraphTopology, EdgeHandle,     GraphEdgeHandle>        EdgeIter;
        typedef IteratorBase<GraphTopology, FaceHandle,     GraphFaceHandle>        FaceIter;
        
        typedef VertexIter      ConstVertexIter;
        typedef HalfedgeIter    ConstHalfedgeIter;
        typedef EdgeIter        ConstEdgeIter;
        typedef FaceIter        ConstFaceIter;

        typedef VertexVertexIterBase<GraphTopology, true>   VertexVertexIter;
        typedef VertexVertexIterBase<GraphTopology, true>   VertexVertexCCWIter;
        typedef VertexVertexIterBase<GraphTopology, false>  VertexVertexCWIter;
        typedef VertexVertexIter    ConstVertexVertexIter;
        typedef VertexVertexCCWIter ConstVertexVertexCCWIter;
        typedef VertexVertexCWIter  ConstVertexVertexCWIter;

        typedef VertexOHalfedgeIterBase<GraphTopology, true>    VertexOHalfedgeIter;
        typedef VertexOHalfedgeIterBase<GraphTopology, true>    VertexOHalfedgeCCWIter;
        typedef VertexOHalfedgeIterBase<GraphTopology, false>   VertexOHalfedgeCWIter;
        typedef VertexOHalfedgeIter     ConstVertexOHalfedgeIter;
        typedef VertexOHalfedgeCCWIter  ConstVertexOHalfedgeCCWIter;
        typedef VertexOHalfedgeCWIter   ConstVertexOHalfedgeCWIter;

    public:
        /* get the number of vertices */
        unsigned n_vertices() const
        {
            return _vertices.size();
        }

        /* get the number of edges */
        unsigned n_edges() const
        {
            return _edges.size();
        }

        /* get the number of vertices */
        unsigned n_halfedges() const
        {
            return _edges.size() * 2;
        }

        /* get the number of faces */
        unsigned n_faces() const
        {
            return _faces.size();
        }

        /* use vertex handle to get the vertex item */
        VertexItem& vertex(VertexHandle vh)
        {
            assert(vh.is_valid());
            return _vertices[vh.idx()];
        }

        /* use vertex handle to get the vertex item */
        const VertexItem& vertex(VertexHandle vh) const
        {
            assert(vh.is_valid());
            return _vertices[vh.idx()];
        }

        /* use halfedge handle to get the halfedge item */
        HalfedgeItem& halfedge(HalfedgeHandle heh)
        {
            assert(heh.is_valid());
            return _edges[heh.idx() >> 1]._halfedges[heh.idx() & 1];
        }

        /* use halfedge handle to get the halfedge item */
        const HalfedgeItem& halfedge(HalfedgeHandle heh) const
        {
            assert(heh.is_valid());
            return _edges[heh.idx() >> 1]._halfedges[heh.idx() & 1];
        }

        /* use edge handle to get the edge item */
        EdgeItem& edge(EdgeHandle eh)
        {
            assert(eh.is_valid());
            return _edges[eh.idx()];
        }

        /* use edge handle to get the edge item */
        const EdgeItem& edge(EdgeHandle eh) const
        {
            assert(eh.is_valid());
            return _edges[eh.idx()];
        }
        
        /* use face handle to get the face item */
        FaceItem& face(FaceHandle fh)
        {
            assert(fh.is_valid());
            return _faces[fh.idx()];
        }

        /* use face handle to get the face item */
        const FaceItem& face(FaceHandle fh) const
        {
            assert(fh.is_valid());
            return _faces[fh.idx()];
        }

        /* get i'th vertex handle */
        VertexHandle vertex_handle(unsigned i) const
        {
            return (i<n_vertices() ? VertexHandle(i) : VertexHandle());
        }

        /* get the destination of the halfedge */
        VertexHandle to_vertex_handle(HalfedgeHandle heh) const
        {
            return halfedge(heh)._vertex_handle;
        }

        /* get the destination of the halfedge */
        VertexHandle from_vertex_handle(HalfedgeHandle heh) const
        {
            return to_vertex_handle(opposite_halfedge_handle(heh));
        }

        /* get i'th halfedge handle */
        HalfedgeHandle halfedge_handle(unsigned i) const
        {
            return (i<n_halfedges() ? HalfedgeHandle(i) : HalfedgeHandle());
        }

        /* get the handle of a vertex's outgoing halfedge */
        HalfedgeHandle halfedge_handle(VertexHandle vh) const
        {
            return vertex(vh)._halfedge_handle;
        }

        /* get halfedge handle with edge handle and a side */
        HalfedgeHandle halfedge_handle(EdgeHandle eh, unsigned i) const
        {
            assert(i <= 1);
            return (eh.idx()<n_edges() ? HalfedgeHandle((eh.idx() << 1) + i) : HalfedgeHandle());
        }

        /* get halfedge handle of a face */
        HalfedgeHandle halfedge_handle(FaceHandle fh) const
        {
            return (fh.idx()<n_faces() ? face(fh)._halfedge_handle : HalfedgeHandle());
        }

        /* get handle of the opposite halfedge */
        HalfedgeHandle opposite_halfedge_handle(HalfedgeHandle heh) const
        {
            return(heh.idx()<n_halfedges() ? HalfedgeHandle(heh.idx() ^ 1) : HalfedgeHandle());
        }

        /* get handle of the previous halfedge */
        HalfedgeHandle prev_halfedge_handle(HalfedgeHandle heh) const
        {
            return(heh.idx()<n_halfedges() ? halfedge(heh)._prev_halfedge_handle : HalfedgeHandle());
        }

        /* get handle of the next halfedge */
        HalfedgeHandle next_halfedge_handle(HalfedgeHandle heh) const
        {
            return(heh.idx()<n_halfedges() ? halfedge(heh)._next_halfedge_handle : HalfedgeHandle());
        }

        /* get the first halfedge handle in the clock-wise order */
        HalfedgeHandle cw_rotated_halfedge_handle(HalfedgeHandle heh) const
        {
            return next_halfedge_handle(opposite_halfedge_handle(heh));
        }

        /* get the first halfedge handle in the countor-clock-wise order */
        HalfedgeHandle ccw_rotated_halfedge_handle(HalfedgeHandle heh) const
        {
            return opposite_halfedge_handle(prev_halfedge_handle(heh));
        }

        /* get i'th edge handle */
        EdgeHandle edge_handle(unsigned i) const
        {
            return (i<n_edges() ? EdgeHandle(i) : EdgeHandle());
        }

        /* get i'th face handle */
        FaceHandle face_handle(unsigned i) const
        {
            return (i<n_faces() ? FaceHandle(i) : FaceHandle());
        }

        /* get face handle the halfedge lies on */
        FaceHandle face_handle(HalfedgeHandle heh) const
        {
            return (heh.idx()<n_halfedges() ? halfedge(heh)._face_handle : FaceHandle());
        }

        /* check if the vertex is a boundary vertex */
        bool is_boundary(VertexHandle vh)
        {
            HalfedgeHandle heh(halfedge_handle(vh));
            return !(heh.is_valid() && face_handle(heh).is_valid());
        }

        /* check if a halfedge is a boundary vertex */
        bool is_boundary(HalfedgeHandle heh)
        {
            return !face_handle(heh).is_valid();
        }

    public:
        /* begin iterator for vertices */
        VertexIter vertices_begin()
        {
            return VertexIter(this, VertexHandle(0));
        }

        /* const begin iterator for vertices */
        ConstVertexIter vertices_begin() const
        {
            return ConstVertexIter(this, VertexHandle(0));
        }

        /* end iterator for vertices */
        VertexIter vertices_end()
        {
            return VertexIter(this, VertexHandle(int(n_vertices())));
        }

        /* const end iterator for vertices */
        ConstVertexIter vertices_end() const
        {
            return ConstVertexIter(this, VertexHandle(int(n_vertices())));
        }

        /* begin iterator for halfedges */
        HalfedgeIter halfedges_begin()
        {
            return HalfedgeIter(this, HalfedgeHandle(0));
        }

        /* const begin iterator for halfedges */
        ConstHalfedgeIter halfedges_begin() const
        {
            return ConstHalfedgeIter(this, HalfedgeHandle(0));
        }

        /* end iterator for halfedges */
        HalfedgeIter halfedges_end()
        {
            return HalfedgeIter(this, HalfedgeHandle(int(n_halfedges())));
        }

        /* const end iterator for halfedges */
        ConstHalfedgeIter halfedges_end() const
        {
            return ConstHalfedgeIter(this, HalfedgeHandle(int(n_halfedges())));
        }

        /* begin iterator for edges */
        EdgeIter edges_begin()
        {
            return EdgeIter(this, EdgeHandle(0));
        }

        /* const begin iterator for edges */
        ConstEdgeIter edges_begin() const
        {
            return ConstEdgeIter(this, EdgeHandle(0));
        }

        /* end iterator for edges */
        EdgeIter edges_end()
        {
            return EdgeIter(this, EdgeHandle(int(n_edges())));
        }

        /* const end iterator for edges */
        ConstEdgeIter edges_end() const
        {
            return ConstEdgeIter(this, EdgeHandle(int(n_edges())));
        }

        /* begin iterator for faces */
        FaceIter faces_begin()
        {
            return FaceIter(this, FaceHandle(0));
        }

        /* const begin iterator for faces */
        ConstFaceIter faces_begin() const
        {
            return ConstFaceIter(this, FaceHandle(0));
        }

        /* end iterator for faces */
        FaceIter faces_end()
        {
            return FaceIter(this, FaceHandle(int(n_faces())));
        }

        /* const end iterator for faces */
        ConstFaceIter faces_end() const
        {
            return ConstFaceIter(this, FaceHandle(int(n_faces())));
        }

        /* vertex-vertex circulator */
        VertexVertexIter vv_begin(VertexHandle vh)
        {
            return VertexVertexIter(this, vh);
        }

        /* vertex-vertex circulator */
        VertexVertexIter vv_end(VertexHandle vh)
        {
            return VertexVertexIter(this, vh, true);
        }

        /* const vertex-vertex circulator */
        ConstVertexVertexIter vv_begin(VertexHandle vh) const
        {
            return ConstVertexVertexIter(this, vh);
        }

        /* const vertex-vertex circulator */
        ConstVertexVertexIter vv_end(VertexHandle vh) const
        {
            return ConstVertexVertexIter(this, vh, true);
        }

        /* vertex-vertex contour clock wise circulator */
        VertexVertexCCWIter vv_ccwbegin(VertexHandle vh)
        {
            return VertexVertexCCWIter(this, vh);
        }

        /* vertex-vertex contour clock wise circulator */
        VertexVertexCCWIter vv_ccwend(VertexHandle vh)
        {
            return VertexVertexCCWIter(this, vh, true);
        }

        /* const vertex-vertex contour clock wise circulator */
        ConstVertexVertexCCWIter vv_ccwbegin(VertexHandle vh) const
        {
            return ConstVertexVertexCCWIter(this, vh);
        }

        /* const vertex-vertex contour clock wise circulator */
        ConstVertexVertexCCWIter vv_ccwend(VertexHandle vh) const
        {
            return ConstVertexVertexCCWIter(this, vh, true);
        }

        /* vertex-vertex clock wise circulator */
        VertexVertexCWIter vv_cwbegin(VertexHandle vh)
        {
            return VertexVertexCWIter(this, vh);
        }

        /* vertex-vertex clock wise circulator */
        VertexVertexCWIter vv_cwend(VertexHandle vh)
        {
            return VertexVertexCWIter(this, vh, true);
        }

        /* const vertex-vertex clock wise circulator */
        ConstVertexVertexCWIter vv_cwbegin(VertexHandle vh) const
        {
            return ConstVertexVertexCWIter(this, vh);
        }

        /* const vertex-vertex clock wise circulator */
        ConstVertexVertexCWIter vv_cwend(VertexHandle vh) const
        {
            return ConstVertexVertexCWIter(this, vh, true);
        }

        /* vertex - outgoing halfedge circulator */
        VertexOHalfedgeIter voh_begin(VertexHandle vh)
        {
            return VertexOHalfedgeIter(this, vh);
        }

        /* vertex - outgoing halfedge circulator */
        VertexOHalfedgeIter voh_end(VertexHandle vh)
        {
            return VertexOHalfedgeIter(this, vh, true);
        }

        /* const vertex - outgoing halfedge circulator */
        ConstVertexOHalfedgeIter voh_begin(VertexHandle vh) const
        {
            return ConstVertexOHalfedgeIter(this, vh);
        }

        /* const vertex - outgoing halfedge circulator */
        ConstVertexOHalfedgeIter voh_end(VertexHandle vh) const
        {
            return ConstVertexOHalfedgeIter(this, vh, true);
        }

        /* vertex - outgoing halfedge contour clock wise circulator */
        VertexOHalfedgeCCWIter voh_ccwbegin(VertexHandle vh)
        {
            return VertexOHalfedgeCCWIter(this, vh);
        }

        /* vertex - outgoing halfedge contour clock wise circulator */
        VertexOHalfedgeCCWIter voh_ccwend(VertexHandle vh)
        {
            return VertexOHalfedgeCCWIter(this, vh, true);
        }

        /* const vertex - outgoing halfedge contour clock wise circulator */
        ConstVertexOHalfedgeCCWIter voh_ccwbegin(VertexHandle vh) const
        {
            return ConstVertexOHalfedgeCCWIter(this, vh);
        }

        /* const vertex - outgoing halfedge contour clock wise circulator */
        ConstVertexOHalfedgeCCWIter voh_ccwend(VertexHandle vh) const
        {
            return ConstVertexOHalfedgeCCWIter(this, vh, true);
        }

        /* vertex - outgoing halfedge clock wise circulator */
        VertexOHalfedgeCWIter voh_cwbegin(VertexHandle vh)
        {
            return VertexOHalfedgeCWIter(this, vh);
        }

        /* vertex - outgoing halfedge clock wise circulator */
        VertexOHalfedgeCWIter voh_cwend(VertexHandle vh)
        {
            return VertexOHalfedgeCWIter(this, vh, true);
        }

        /* const vertex - outgoing halfedge clock wise circulator */
        ConstVertexOHalfedgeCWIter voh_cwbegin(VertexHandle vh) const
        {
            return ConstVertexOHalfedgeCWIter(this, vh);
        }

        /* const vertex - outgoing halfedge clock wise circulator */
        ConstVertexOHalfedgeCWIter voh_cwend(VertexHandle vh) const
        {
            return ConstVertexOHalfedgeCWIter(this, vh, true);
        }

    public:
        /* add a new vertex */
        VertexHandle new_vertex()
        {
            _vertices.push_back(VertexItem());
            return VertexHandle(_vertices.size() - 1);
        }

        /* add a new edge */
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

        /* add a new face */
        FaceHandle new_face()
        {
            _faces.push_back(FaceItem());
            return FaceHandle(_faces.size() - 1);
        }

        /**
         * @brief find halfedge with corresponding end points
         * @param start end vertex of halfedge 
         * @param end end vertex of halfedge 
         */
        HalfedgeHandle find_halfedge(VertexHandle start, VertexHandle end)
        {
            return HalfedgeHandle();
        }

        /* if the vertex has a boundary outgoing halfedge around it, link the halfedge */
        void adjust_outgoing_halfedge(VertexHandle vh)
        {
            for(auto voh_it = voh_begin(vh); voh_it != voh_end(vh); ++voh_it)
            {
                if(is_boundary(*voh_it))
                {
                    vertex(vh)._halfedge_handle = *voh_it;
                    break;
                }
            }
        }
        
    private:
        /* vertex elements */
        std::vector<VertexItem> _vertices;

        /* edge elements */
        std::vector<EdgeItem>   _edges;

        /* face elements */
        std::vector<FaceItem>   _faces;
};


/**
 * @brief A graph describe the topological relationship and mesh items of the halfedge data struct
 * @tparam Traits element attributes
 */
template<class Traits = DefaultTraits>
class Graph : public GraphTopology
{
    public:
        typedef typename Traits::PointAttribute       PointAttribute;
        typedef typename Traits::HalfedgeAttribute    HalfedgeAttribute;
        typedef typename Traits::EdgeAttribute        EdgeAttribute;
        typedef typename Traits::FaceAttribute        FaceAttribute;
        
    public:
        /**
         * @brief add a vertex into graph and attach an attribute information
         * @return the new vertex handle
         */
        GraphVertexHandle add_vertex(const PointAttribute& p_attr)
        {
            VertexHandle vh = new_vertex();
            vertex_attribute(vh) = p_attr;
            return GraphVertexHandle(vh.idx(), this);
        }

        /**
         * @brief add a face into graph and build connectivity information
         * @return the new face handle 
         */
        GraphFaceHandle add_face(const std::vector<VertexHandle>& vhs)
        {
            unsigned n = vhs.size();
            assert(n > 2);

            if(_tmp_edge_storage.size() < n)
            {
                _tmp_edge_storage.resize(n);
                _he_link_storage.resize(6*n);
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

            unsigned link_count = 0;
            for(unsigned i = 0, j = 1; i < n; ++i, ++j, j%=n)
            {
                if(!_tmp_edge_storage[i].is_new && !_tmp_edge_storage[j].is_new)
                {
                    HalfedgeHandle inner_prev_he = _tmp_edge_storage[i].halfedge_handle;
                    HalfedgeHandle inner_next_he = _tmp_edge_storage[j].halfedge_handle;

                    if(next_halfedge_handle(inner_prev_he) != inner_next_he)
                    {
                        HalfedgeHandle outer_prev_he = opposite_halfedge_handle(inner_next_he);
                        HalfedgeHandle outer_next_he = opposite_halfedge_handle(inner_prev_he);
                        HalfedgeHandle boundary_prev_he = outer_prev_he;
                        do 
                        {
                            boundary_prev_he = opposite_halfedge_handle(next_halfedge_handle(boundary_prev_he));
                        }
                        while(!is_boundary(boundary_prev_he));
                        HalfedgeHandle boundary_next_he = next_halfedge_handle(boundary_prev_he);

                        if(boundary_prev_he == inner_prev_he)
                        {
                            std::cerr << "Warning : relink failed" << std::endl;
                            return GraphFaceHandle(-1, this);
                        }

                        assert(is_boundary(boundary_prev_he));
                        assert(is_boundary(boundary_next_he));

                        HalfedgeHandle patch_start_he = next_halfedge_handle(inner_prev_he);
                        HalfedgeHandle patch_end_he   = next_halfedge_handle(inner_next_he);

                        assert(boundary_prev_he.is_valid());
                        assert(boundary_next_he.is_valid());
                        assert(patch_start_he.is_valid());
                        assert(patch_end_he.is_valid());
                        assert(inner_prev_he.is_valid());
                        assert(inner_next_he.is_valid());

                        _he_link_storage[link_count++] = std::make_pair(boundary_prev_he, patch_start_he);
                        _he_link_storage[link_count++] = std::make_pair(patch_end_he, boundary_next_he);
                        _he_link_storage[link_count++] = std::make_pair(inner_prev_he, inner_next_he);
                    }
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
                            _he_link_storage[link_count++] = std::make_pair(boundary_prev_he, outer_next_he);
                            vertex(vh)._halfedge_handle = outer_next_he;
                            break;
                        case 2:
                            HalfedgeHandle boundary_next_he = prev_halfedge_handle(inner_prev_he);
                            assert(boundary_next_he.is_valid());
                            _he_link_storage[link_count++] = std::make_pair(outer_prev_he, boundary_next_he);
                            vertex(vh)._halfedge_handle = boundary_next_he;
                            break;
                        case 3:
                            if(!halfedge_handle(vh).is_valid())
                            {
                                vertex(vh)._halfedge_handle = outer_next_he;
                                _he_link_storage[link_count++] = std::make_pair(outer_prev_he, outer_next_he);
                            }
                            else
                            {
                                HalfedgeHandle boundary_next_he = halfedge_handle(vh);
                                HalfedgeHandle boundary_prev_he = prev_halfedge_handle(boundary_next_he);
                                assert(boundary_next_he.is_valid());
                                assert(boundary_prev_he.is_valid());
                                _he_link_storage[link_count++] = std::make_pair(boundary_prev_he, outer_next_he);
                                _he_link_storage[link_count++] = std::make_pair(outer_prev_he, boundary_next_he);
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

            for(unsigned i = 0; i < link_count; ++i)
            {
                halfedge(_he_link_storage[i].first)._next_halfedge_handle(_he_link_storage[i].second);
                halfedge(_he_link_storage[i].second)._prev_halfedge_handle(_he_link_storage[i].first);
            }

            for(unsigned i = 0; i < n; ++i)
            {
                if(_tmp_edge_storage[i].need_adjust)
                    adjust_outgoing_halfedge(vhs[i]);
            }

            return GraphFaceHandle(fh.idx(), this);
        }

    public:
        /* get the writable vertex attribute */
        PointAttribute& vertex_attribute(VertexHandle vh)
        {
            assert(vh.is_valid() && vh.idx() < n_vertices());
            if(vh.idx() >= _vertex_attr.size())
                _vertex_attr.resize(vh.idx() + 1);
            return _vertex_attr[vh.idx()];
        }

        /* get a const vertex attribute */
        const PointAttribute& vertex_attribute(VertexHandle vh) const
        {
            assert(vh.is_valid() && vh.idx() < _vertex_attr.size());
            return _vertex_attr[vh.idx()];
        }

        /* get the writable halfedge attribute */
        HalfedgeAttribute& halfedge_attribute(HalfedgeHandle heh)
        {
            assert(heh.is_valid() && heh.idx() < n_halfedges());
            if(heh.idx() >= _halfedge_attr.size())
                _halfedge_attr.resize(heh.idx() + 1);
            return _halfedge_attr[heh.idx()];
        }

        /* get a const halfedge attribute */
        const HalfedgeAttribute& halfedge_attribute(HalfedgeHandle heh) const
        {
            assert(heh.is_valid() && heh.idx() < _halfedge_attr.size());
            return _halfedge_attr[heh.idx()];
        }

        /* get the writable edge attribute */
        EdgeAttribute& edge_attribute(EdgeHandle eh)
        {
            assert(eh.is_valid() && eh.idx() < n_edges());
            if(eh.idx() >= _edge_attr.size())
                _edge_attr.resize(eh.idx() + 1);
            return _edge_attr[eh.idx()];
        }

        /* get a const edge attribute */
        const EdgeAttribute& edge_attribute(EdgeHandle eh) const
        {
            assert(eh.is_valid() && eh.idx() < _edge_attr.size());
            return _edge_attr[eh.idx()];
        }

        /* get the writable face attribute */
        FaceAttribute& face_attribute(FaceHandle fh)
        {
            assert(fh.is_valid() && fh.idx() < n_edges());
            if(fh.idx() >= _face_attr.size())
                _face_attr.resize(fh.idx() + 1);
            return _edge_attr[fh.idx()];
        }

        /* get a const edge attribute */
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
        /* container that store the edge information when add a new face */
        std::vector<AddFaceEdgeStorage> _tmp_edge_storage;
        /* container that store the information used for next halfedge link when add a new face */
        std::vector<std::pair<HalfedgeHandle, HalfedgeHandle> > _he_link_storage;

    private:
        /* attributes binding at vertices */
        std::vector<PointAttribute>    _vertex_attr;

        /* attributes binding at halfedges  */
        std::vector<HalfedgeAttribute> _halfedge_attr;

        /* attributes binding at edges  */
        std::vector<EdgeAttribute>     _edge_attr;

        /* attributes binding at faces  */
        std::vector<FaceAttribute>     _face_attr;
};

}   // namespace topologic
}   // namespace geometry
}   // namespace CMTL

#endif // __topologic_halfedge_h__