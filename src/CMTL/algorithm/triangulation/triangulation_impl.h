#ifndef __algorithm_triangulation_impl_h__
#define __algorithm_triangulation_impl_h__

#include "../../geo2d/pslg.h"
#include "../predicate.h"
#include "triangulation_storage.h"

#include <vector>

#define TRIANGULATION_QUIT_ON_BUG 0
#define TRIANGULATION_QUIT_ON_INPUT_ERROR 1

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
  enum InsertVertexResult { DUPLICATEVERTEX };
  enum LocateResult { INTRIANGLE, ONEDGE, ONVERTEX, OUTSIDE };

 public:
  InsertVertexResult insert_vertex(Vertex* newvertex, TriEdge& searchtri);

 private:
  int incremental_delaunay();
  Triangle* first_tri();
  Triangle* first_tri(Vertex* v0, Vertex* v1, Vertex* v2);
  LocateResult locate(Vertex* v, TriEdge& searchtri);
  LocateResult preciselocate(Vertex* v, TriEdge& searchtri);

 private:
  ORIENTATION orient2d(Vertex* v0, Vertex* v1, Vertex* v2) const;
  T square_length(Vertex* v0, Vertex* v1) const;
  bool is_same(Vertex* v0, Vertex* v2) const;

 private:
  void quit(int status) const;

 private:
  T xmin, xmax, ymin, ymax;
  TriEdge recenttri;
};

template <typename T>
Triangulation<T>::Triangulation(const geo2d::PSLG<T>& input)
    : Internal::TriangulationStorage<T>() {
  if (input._points.size() < 3) {
    std::cerr << "Error : Input must have at least three input vertices.\n";
    quit(TRIANGULATION_QUIT_ON_INPUT_ERROR);
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
Triangulation<T>::~Triangulation() {}

template <typename T>
typename Triangulation<T>::InsertVertexResult Triangulation<T>::insert_vertex(
    Vertex* newvertex, TriEdge& searchtri) {
  LocateResult locateresult;

  if (searchtri.tri->is_dummy()) {
    locateresult = locate(newvertex, searchtri);
  } else {
    locateresult = preciselocate(newvertex, searchtri);
  }

  return DUPLICATEVERTEX;
}

template <typename T>
typename Triangulation<T>::LocateResult Triangulation<T>::locate(
    Vertex* v, TriEdge& searchtri) {
  if (searchtri.tri->is_dummy()) {
    for (searchtri.ori = 0; searchtri.ori < 3; ++searchtri.ori) {
      if (searchtri.apex() == this->_infvrt) break;
    }
    if (searchtri.ori == 3) {
      quit(TRIANGULATION_QUIT_ON_BUG);
    }
    searchtri = searchtri.sym();
  }

  if (is_same(searchtri.org(), v)) return ONVERTEX;

  if (recenttri.tri != nullptr) {
    if (is_same(recenttri.org(), v)) {
      searchtri = recenttri;
      return ONVERTEX;
    }
    if (square_length(recenttri.org(), v) < square_length(searchtri.org(), v)) {
      searchtri = this->recenttri;
    }
  }

  for (searchtri.ori = 0; searchtri.ori < 3; ++searchtri.ori) {
    if (orient2d(searchtri.org(), searchtri.dest(), v) == ORIENTATION::POSITIVE)
      break;
  }
  if (searchtri.ori == 3) {
    quit(TRIANGULATION_QUIT_ON_BUG);
  }

  return preciselocate(v, searchtri);
}

template <typename T>
typename Triangulation<T>::LocateResult Triangulation<T>::preciselocate(
    Vertex* v, TriEdge& searchtri) {
  if (searchtri.tri == nullptr || searchtri.tri->is_dummy()) {
    quit(TRIANGULATION_QUIT_ON_BUG);
  }

  do {
    Vertex* org = searchtri.org();
    Vertex* dest = searchtri.dest();
    Vertex* apex = searchtri.apex();
    ORIENTATION ori1 = orient2d(dest, apex, v);
    ORIENTATION ori2 = orient2d(apex, org, v);
    if (ori1 == ORIENTATION::POSITIVE) {
      if (ori2 == ORIENTATION::POSITIVE) {
        break;
      } else if (ori2 == ORIENTATION::NEGATIVE) {
        searchtri.ori = this->_edge_prev_tbl[searchtri.ori];
      } else {
        searchtri.ori = this->_edge_prev_tbl[searchtri.ori];
        return ONEDGE;
      }
    } else if (ori1 == ORIENTATION::NEGATIVE) {
      if (ori2 == ORIENTATION::POSITIVE) {
        searchtri.ori = this->_edge_next_tbl[searchtri.ori];
      } else if (ori2 == ORIENTATION::NEGATIVE) {
        if ((apex->crd[0] - v->crd[0]) * (dest->crd[0] - v->crd[0]) +
                (apex->crd[1] - v->crd[1]) * (dest->crd[1] - v->crd[1]) >
            0) {
          searchtri.ori = this->_edge_prev_tbl[searchtri.ori];
        } else {
          searchtri.ori = this->_edge_next_tbl[searchtri.ori];
        }
      } else {
        searchtri.ori = this->_edge_next_tbl[searchtri.ori];
      }
    } else {
      if (ori2 == ORIENTATION::POSITIVE) {
        searchtri.ori = this->_edge_next_tbl[searchtri.ori];
        return ONEDGE;
      } else if (ori2 == ORIENTATION::NEGATIVE) {
        searchtri.ori = this->_edge_prev_tbl[searchtri.ori];
      } else {
        searchtri.ori = this->_edge_prev_tbl[searchtri.ori];
        return ONVERTEX;
      }
    }
    searchtri = searchtri.sym();
  } while (!searchtri.tri->is_dummy());

  if (searchtri.tri->is_dummy()) {
    return OUTSIDE;
  }

  return INTRIANGLE;
}

template <typename T>
int Triangulation<T>::incremental_delaunay() {
  Triangle* firstT = first_tri();

  TriEdge starttri;
  for (unsigned i = 2; i < this->_vertices.size(); ++i) {
    if (this->_vertices[i] == firstT->vrt[2]) continue;
    starttri = this->_infvrt->adj;
    if (insert_vertex(this->_vertices[i], starttri) == DUPLICATEVERTEX) {
    }
  }

  return 1;
}

template <typename T>
typename Triangulation<T>::Triangle* Triangulation<T>::first_tri() {
  unsigned i = 2;
  ORIENTATION ori;
  for (; i < this->_vertices.size(); ++i) {
    ori = orient2d(this->_vertices[0], this->_vertices[1], this->_vertices[i]);
    if (ori != ORIENTATION::ON) break;
  }
  if (i == this->_vertices.size()) {
    std::cerr << "Error: Input vertices are collinear.\n";
    quit(TRIANGULATION_QUIT_ON_INPUT_ERROR);
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

  for (unsigned i = 1; i < 3; ++i) {
    te[i].tri->set_dummy();
  }

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
ORIENTATION Triangulation<T>::orient2d(Vertex* v0, Vertex* v1,
                                       Vertex* v2) const {
  return orient_2d(v0->crd, v1->crd, v2->crd);
}

template <typename T>
T Triangulation<T>::square_length(Vertex* v0, Vertex* v1) const {
  return (v0->crd[0] - v1->crd[0]) * (v0->crd[0] - v1->crd[0]) +
         (v0->crd[1] - v1->crd[1]) * (v0->crd[1] - v1->crd[1]);
}

template <typename T>
bool Triangulation<T>::is_same(Vertex* v0, Vertex* v2) const {
  return (v0->crd[0] == v2->crd[0]) && (v0->crd[1] == v2->crd[1]);
}

template <typename T>
void Triangulation<T>::quit(int status) const {
  throw status;
}

}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_triangulation_impl_h__