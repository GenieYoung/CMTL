#ifndef __algorithm_triangulation_storage_h__
#define __algorithm_triangulation_storage_h__

namespace CMTL {
namespace algorithm {
namespace Internal {

template <class T>
class TriangulationStorage {
 public:
  TriangulationStorage();
  virtual ~TriangulationStorage();

 protected:
  static constexpr int INPUTVERTEX = 0;
  static constexpr int INFVERTEX = 1;

  static constexpr unsigned char _edge_next_tbl[3] = {1, 2, 0};
  static constexpr unsigned char _edge_prev_tbl[3] = {2, 0, 1};

 protected:
  struct Vertex;
  struct Triangle;

  struct TriEdge {
    Triangle* tri;
    unsigned char ori;

    void set(Vertex* v0, Vertex* v1, Vertex* v2);
    void link(const TriEdge& other);

    TriEdge next() const;
    TriEdge prev() const;
  };

  struct Vertex {
    T crd[2];
    TriEdge adj;
    // int mark;
    char type;
  };

  struct Triangle {
    Vertex* vrt[3];
    TriEdge nei[3];

    Triangle();
  };

  typedef Triangle Segment;

  //   template<typename T>
  //   struct arraypool
  //   {
  //     std::vector<T> items;
  //   };
  template <typename ITEM>
  using arraypool = std::vector<ITEM>;

  arraypool<Vertex*> _vertices;
  arraypool<Triangle*> _triangles;

  Vertex* _infvrt;
  std::vector<Triangle*> _dummytris;
};

template <typename T>
TriangulationStorage<T>::TriangulationStorage() {
  _infvrt = new Vertex;
  _infvrt->type = INFVERTEX;
}

template <typename T>
TriangulationStorage<T>::~TriangulationStorage() {
  delete _infvrt;
  for (unsigned i = 0; i < _vertices.size(); ++i) {
    if (_vertices[i]) delete _vertices[i];
  }
  _vertices.clear();
  for (unsigned i = 0; i < _triangles.size(); ++i) {
    if (_triangles[i]) delete _triangles[i];
  }
  _triangles.clear();
}

// TriEdge

template <typename T>
void TriangulationStorage<T>::TriEdge::set(Vertex* v0, Vertex* v1, Vertex* v2) {
  tri->vrt[0] = v0;
  tri->vrt[1] = v1;
  tri->vrt[2] = v2;
  ori = 0;
}

template <typename T>
void TriangulationStorage<T>::TriEdge::link(const TriEdge& other) {
  tri->nei[ori] = other;
  other.tri->nei[other.ori] = *this;
}

template <typename T>
typename TriangulationStorage<T>::TriEdge
TriangulationStorage<T>::TriEdge::next() const {
  return TriEdge{tri, _edge_next_tbl[ori]};
}

template <typename T>
typename TriangulationStorage<T>::TriEdge
TriangulationStorage<T>::TriEdge::prev() const {
  return TriEdge{tri, _edge_prev_tbl[ori]};
}

// Triangle

template <typename T>
TriangulationStorage<T>::Triangle::Triangle() {
  vrt[0] = vrt[1] = vrt[2] = nullptr;
  nei[0].tri = nei[1].tri = nei[2].tri = nullptr;
  nei[0].ori = nei[1].ori = nei[2].ori = 0;
}

}  // namespace Internal
}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_triangulation_storage_h__