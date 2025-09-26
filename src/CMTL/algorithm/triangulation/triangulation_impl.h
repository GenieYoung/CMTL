#ifndef __algorithm_triangulation_impl_h__
#define __algorithm_triangulation_impl_h__

#include "../../geo2d/pslg.h"
#include "../predicate.h"
#include "triangulation_storage.h"

#include <vector>

namespace CMTL {
namespace algorithm {

template <typename T>
class Triangulation : public Internal::TriangulationStorage<T> {
 public:
  Triangulation(const geo2d::PSLG<T>& input);
  virtual ~Triangulation();

  using typename Internal::TriangulationStorage<T>::Vertex;
  using typename Internal::TriangulationStorage<T>::TriEdge;
  using typename Internal::TriangulationStorage<T>::Triangle;

 public:
  enum InsertVertexResult {
    DUPLICATEVERTEX
  };
  enum LocateResult {

  };

 public:
  InsertVertexResult insert_vertex(Vertex* newvertex, TriEdge* searchtri = nullptr);

 private:
  int incremental_delaunay();
  Triangle* first_tri();
  Triangle* first_tri(Vertex* v0, Vertex* v1, Vertex* v2);

 private:
  void throw_error(int status) const;

 private:
  T xmin, xmax, ymin, ymax;
};

template <typename T>
Triangulation<T>::Triangulation(const geo2d::PSLG<T>& input)
    : Internal::TriangulationStorage<T>() {
  if (input._points.size() < 3) {
    std::cerr << "Error : Input must have at least three input vertices.\n";
    throw_error(1);
  }

  for (unsigned i = 0; i < input._points.size(); ++i) {
    Vertex* newvertex = new Vertex;
    newvertex->crd[0] = input._points[i][0];
    newvertex->crd[1] = input._points[i][1];
    newvertex->type = this->INPUTVERTEX;
    this->_vertices.push_back(newvertex);

    if (i == 0) {
      xmin = xmax = newvertex->crd[0];
      ymin = ymax = newvertex->crd[1];
    } else {
      xmin = (newvertex->crd[0] < xmin) ? newvertex->crd[0] : xmin;
      xmax = (newvertex->crd[0] > xmax) ? newvertex->crd[0] : xmax;
      ymin = (newvertex->crd[1] < ymin) ? newvertex->crd[1] : ymin;
      ymax = (newvertex->crd[1] > ymax) ? newvertex->crd[1] : ymax;
    }
  }

  incremental_delaunay();
}

template <typename T>
Triangulation<T>::~Triangulation() {
}

template <typename T>
typename Triangulation<T>::InsertVertexResult Triangulation<T>::insert_vertex(Vertex* newvertex, TriEdge* searchtri)
{
    return DUPLICATEVERTEX;
}

template <typename T>
int Triangulation<T>::incremental_delaunay() {
  Triangle* firstT = first_tri();

  for(unsigned i = 2; i < this->_vertices.size(); ++i) {
    if(this->_vertices[i] == firstT->vrt[2])
        continue;
    insert_vertex(this->_vertices[i]);
  }

  return 1;
}

template <typename T>
typename Triangulation<T>::Triangle* Triangulation<T>::first_tri() {
  unsigned i = 2;
  ORIENTATION ori;
  for (; i < this->_vertices.size(); ++i) {
    ori = orient_2d(this->_vertices[0]->crd, this->_vertices[1]->crd,
                    this->_vertices[i]->crd);
    if (ori != ORIENTATION::ON) break;
  }
  if (i == this->_vertices.size()) {
    std::cerr << "Error: Input vertices are collinear.\n";
    throw_error(1);
  }

  if (ori == ORIENTATION::POSITIVE) {
    return first_tri(this->_vertices[0], this->_vertices[1],
                     this->_vertices[i]);
  } else {
    return first_tri(this->_vertices[0], this->_vertices[i],
                     this->_vertices[1]);
  }

  return nullptr;
}

template <typename T>
typename Triangulation<T>::Triangle* Triangulation<T>::first_tri(Vertex* v0,
                                                                 Vertex* v1,
                                                                 Vertex* v2) {
  this->_triangles.resize(4);

  TriEdge te[4];
  for (unsigned i = 0; i < 4; ++i) {
    this->_triangles[i] = new Triangle();
    te[i].tri = this->_triangles[i];
  }

  te[0].set(v0, v1, v2);
  te[1].set(v1, v0, this->_infvrt);
  te[2].set(v2, v1, this->_infvrt);
  te[3].set(v0, v2, this->_infvrt);

  te[1].link(te[0]);
  te[2].link(te[0].next());
  te[3].link(te[0].prev());
  (te[1].prev()).link(te[2].next());
  (te[2].prev()).link(te[3].next());
  (te[3].prev()).link(te[1].next());

  v0->adj = te[0];
  v1->adj = te[1];
  v2->adj = te[2];
  this->_infvrt->adj = te[1].prev();

  return te[0].tri;
}

template <typename T>
void Triangulation<T>::throw_error(int status) const {
  throw status;
}

}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_triangulation_impl_h__