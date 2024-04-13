#ifndef __topologic_halfedge_h__
#define __topologic_halfedge_h__

#include <vector>

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
        bool invalidate()
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
    HalfedgeHandle _halfedge_handle;
};

/**
 * @brief half edge item
 */
class HalfedgeItem
{
    FaceHandle _face_handle;
    VertexHandle _vertex_handle;
    HalfedgeHandle _next_halfedge_handle;
};

/**
 * @brief edge item
 */
class EdgeItem
{
    HalfedgeHandle _halfedge_handles[2];
};

/**
 * @brief face item
 */
class FaceItem
{
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
 * @brief A graph describe the topological relationship of the halfedge data struct
 */
class TopoGraph
{
    private:
        static const VertexHandle InvalidVertexHandle;     
        static const HalfedgeHandle InvalidHalfedgeHandle;
        static const EdgeHandle InvalidEdgeHandle;
        static const FaceHandle InvalidFaceHandle;
        
    private:
        std::vector<VertexItem> _vertices;
        std::vector<EdgeItem> _edges;
        std::vector<FaceItem> _faces;
};

const VertexHandle    TopoGraph::InvalidVertexHandle;
const HalfedgeHandle  TopoGraph::InvalidHalfedgeHandle;
const EdgeHandle      TopoGraph::InvalidEdgeHandle;
const FaceHandle      TopoGraph::InvalidFaceHandle;

}   // namespace topologic
}   // namespace geometry
}   // namespace CMTL

#endif // __topologic_halfedge_h__