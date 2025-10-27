#ifndef __algorithm_triangulation_storage_h__
#define __algorithm_triangulation_storage_h__

#include "../../geo2d/point.h"
#include "triangulation_storage_fwd.h"

namespace CMTL {
namespace algorithm {
namespace Internal {

template <class T>
class TriangulationStorage {
 public:
  TriangulationStorage();
  virtual ~TriangulationStorage();

  typedef geo2d::Point<T> Point;

  template <typename TT>
  friend void io::write_obj(const TriangulationStorage<TT>& triangulation,
                            const std::string& file);

 public:
  void clean();

 protected:
  static constexpr int UNUSEDVERTEX = -1;
  static constexpr int INPUTVERTEX = 0;
  static constexpr int INFVERTEX = 1;

  //                 v2
  //                 /\
  //             E2 /  \ E1
  //               /    \
  //              /______\
  //            v0   E0   v1
  static constexpr unsigned char _vo[3] = {0, 1, 2};
  static constexpr unsigned char _vd[3] = {1, 2, 0};
  static constexpr unsigned char _va[3] = {2, 0, 1};
  static constexpr unsigned char _edge_next_tbl[3] = {1, 2, 0};
  static constexpr unsigned char _edge_prev_tbl[3] = {2, 0, 1};

 protected:
  struct Vertex;
  struct Triangle;

  struct TriEdge {
    Triangle* tri;
    unsigned char ori;

    TriEdge(Triangle* t = nullptr, unsigned char o = 0);

    void set(Vertex* v0, Vertex* v1, Vertex* v2);
    void link(const TriEdge& other);

    Vertex* org() const;
    Vertex* dest() const;
    Vertex* apex() const;
    TriEdge next() const;
    TriEdge prev() const;
    TriEdge sym() const;
  };

  struct Vertex {
    Point crd;
    TriEdge adj;
    int idx;
    char type;
  };

  struct Triangle {
    Vertex* vrt[3];
    TriEdge nei[3];

    Triangle();
    void init();

    int flags;
    int mark;
    T area;
    bool is_dummy() const;
    void set_dummy();
    void clear_dummy();
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
  TriEdge _recenttri;

  int _unused_vrts;
  int _dummy_tris;
};

template <typename T>
TriangulationStorage<T>::TriangulationStorage() {
  _infvrt = new Vertex;
  _infvrt->type = INFVERTEX;
  _infvrt->idx = -1;

  _unused_vrts = 0;
  _dummy_tris = 0;
}

template <typename T>
TriangulationStorage<T>::~TriangulationStorage() {
  clean();
}

template <typename T>
void TriangulationStorage<T>::clean() {
  if (_infvrt) delete _infvrt;
  for (unsigned i = 0; i < _vertices.size(); ++i) {
    if (_vertices[i]) delete _vertices[i];
  }
  for (unsigned i = 0; i < _triangles.size(); ++i) {
    if (_triangles[i]) delete _triangles[i];
  }
}

// TriEdge

template <typename T>
TriangulationStorage<T>::TriEdge::TriEdge(Triangle* t, unsigned char o)
    : tri(t), ori(o) {}

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
typename TriangulationStorage<T>::Vertex*
TriangulationStorage<T>::TriEdge::org() const {
  return tri->vrt[_vo[ori]];
}

template <typename T>
typename TriangulationStorage<T>::Vertex*
TriangulationStorage<T>::TriEdge::dest() const {
  return tri->vrt[_vd[ori]];
}

template <typename T>
typename TriangulationStorage<T>::Vertex*
TriangulationStorage<T>::TriEdge::apex() const {
  return tri->vrt[_va[ori]];
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

template <typename T>
typename TriangulationStorage<T>::TriEdge
TriangulationStorage<T>::TriEdge::sym() const {
  return tri->nei[ori];
}

// Triangle

template <typename T>
TriangulationStorage<T>::Triangle::Triangle() {
  init();
}

template <typename T>
void TriangulationStorage<T>::Triangle::init() {
  vrt[0] = vrt[1] = vrt[2] = nullptr;
  nei[0].tri = nei[1].tri = nei[2].tri = nullptr;
  nei[0].ori = nei[1].ori = nei[2].ori = 0;
  flags = mark = 0;
  area = T(0);
}

template <typename T>
bool TriangulationStorage<T>::Triangle::is_dummy() const {
  return flags & 1;
}

template <typename T>
void TriangulationStorage<T>::Triangle::set_dummy() {
  flags |= 1;
}

template <typename T>
void TriangulationStorage<T>::Triangle::clear_dummy() {
  flags &= ~1;
}

}  // namespace Internal
}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_triangulation_storage_h__