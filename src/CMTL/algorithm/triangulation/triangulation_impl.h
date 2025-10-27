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
  enum InsertVertexResult { SUCCESSFULVERTEX, DUPLICATEVERTEX };
  enum LocateResult { INTRIANGLE, ONEDGE, ONVERTEX, OUTSIDE };
  enum FlipType { FLIP13 };

 public:
  InsertVertexResult insert_vertex(Vertex* newvertex, TriEdge& searchtri);

 private:
  int incremental_delaunay();
  Triangle* first_tri();
  Triangle* first_tri(Vertex* v0, Vertex* v1, Vertex* v2);
  LocateResult locate(Vertex* v, TriEdge& searchtri);
  LocateResult preciselocate(Vertex* v, TriEdge& searchtri);
  void flip13(Vertex* v, TriEdge& te);
  void flip24(Vertex* v, TriEdge& te);
  void flip22(TriEdge& te);
  void lawson_flip(Vertex* v, TriEdge& start);

 private:
  ORIENTATION orient2d(Vertex* v0, Vertex* v1, Vertex* v2) const;
  bool local_delaunay_check(Vertex* va, Vertex* vb, Vertex* vc, Vertex* vd) const;
  T square_length(Vertex* v0, Vertex* v1) const;
  bool is_same(Vertex* v0, Vertex* v2) const;

 private:
  void quit(int status);

 private:
  T xmin, xmax, ymin, ymax;
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
    newvertex->crd = input._points[i];
    newvertex->idx = i;
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

  if (locateresult == ONVERTEX) {
    this->_recenttri = searchtri;
    return DUPLICATEVERTEX;
  }

  TriEdge lawsonstarttri = searchtri;
  if(locateresult == ONEDGE) {
    flip24(newvertex, lawsonstarttri);
    lawsonstarttri = lawsonstarttri.next();
  }
  else {
    // INTRIANGLE OR OUTSIDE
    flip13(newvertex, lawsonstarttri);
  }

  InsertVertexResult insertresult = SUCCESSFULVERTEX;

  lawson_flip(newvertex, lawsonstarttri);

  searchtri = lawsonstarttri.prev();

  /* Vertex* left = curr.dest();
  Vertex* right = curr.org();
  Vertex* first = right;
  Vertex* top;
  bool do_flip;
  while(true) {
    do_flip = true;

    if(do_flip) {
      TriEdge currsym = curr.sym();
      top = currsym.apex();

      if(left == this->_infvrt) {
        do_flip = (orient2d(newvertex, right, top) == ORIENTATION::POSITIVE);
      } else if(right == this->_infvrt) {
        do_flip = (orient2d(top, left, newvertex) == ORIENTATION::POSITIVE);
      } else if(top == this->_infvrt) {
        do_flip = false;
      } else {
        do_flip = !local_delaunay_check(left, newvertex, right, top);
      }

      if(do_flip) {
        TriEdge nn[4];
        nn[0] = curr.prev().sym(); // [newv, right]
        nn[1] = currsym.next().sym(); // [right, top]
        nn[2] = currsym.prev().sym(); // [top, left]
        nn[3] = curr.next().sym(); // [left, newv]
        curr.set(top, newvertex, right);
        currsym.set(newvertex, top, left);
        if(left == this->_infvrt) {
          curr.tri->clear_dummy();
          this->_dummy_tris--;
        }
        if(right == this->_infvrt) {
          currsym.tri->clear_dummy();
          this->_dummy_tris--;
        }
        curr.link(currsym);
        curr.next().link(nn[0]);
        curr.prev().link(nn[1]);
        currsym.next().link(nn[2]);
        currsym.prev().link(nn[3]);
        newvertex->adj = curr.next();
        right->adj = curr.prev();
        top->adj = currsym.next();
        left->adj = currsym.prev();

        // todo : update attributes
        T area = (curr.tri->area + currsym.tri->area) * T(0.5);
        curr.tri->area = area;
        currsym.tri->area = area;

        curr = curr.prev();
        left = top;
      }
    }

    if(!do_flip) {
      curr = curr.next();
      TriEdge testtri = curr.sym();

      if(left == first) {
        searchtri = curr.next();
        this->_recenttri = curr;
        return insertresult;
      }

      curr = testtri.next();
      right = left;
      left = curr.dest();
    }
  } */
  
  return insertresult;
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

  if (this->_recenttri.tri != nullptr) {
    if (is_same(this->_recenttri.org(), v)) {
      searchtri = this->_recenttri;
      return ONVERTEX;
    }
    if (square_length(this->_recenttri.org(), v) <
        square_length(searchtri.org(), v)) {
      searchtri = this->_recenttri;
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

  while (1) {
    Vertex* org = searchtri.org();
    Vertex* dest = searchtri.dest();
    Vertex* apex = searchtri.apex();
    ORIENTATION ori1 = orient2d(dest, apex, v);
    ORIENTATION ori2 = orient2d(apex, org, v);
    if (ori1 == ORIENTATION::POSITIVE) {
      if (ori2 == ORIENTATION::POSITIVE) {
        return INTRIANGLE;
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
        if ((apex->crd - v->crd) * (dest->crd - v->crd) > 0) {
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

    if (searchtri.tri->is_dummy()) {
      return OUTSIDE;
    }
  }
}

template <typename T>
void Triangulation<T>::flip13(Vertex* v, TriEdge& te) {
  TriEdge tt[3];
  tt[0] = te;

  Vertex* va = te.org();
  Vertex* vb = te.dest();
  Vertex* vc = te.apex();

  int mark = tt[0].tri->mark;
  int area = tt[0].tri->area;

  TriEdge nn[3];
  for (unsigned i = 0; i < 3; ++i) {
    nn[i] = tt[0].sym();
    tt[0].ori = this->_edge_next_tbl[tt[0].ori];
  }

  if(tt[0].tri->is_dummy()) this->_dummy_tris--;

  tt[0].tri->init();
  tt[1] = this->_triangles.emplace_back(new Triangle());
  tt[2] = this->_triangles.emplace_back(new Triangle());

  tt[0].set(va, vb, v);
  tt[1].set(vb, vc, v);
  tt[2].set(vc, va, v);

  // we do such check in case that te is a dummy edge
  for(int i = 0; i < 3; ++i) {
    if (nn[i].tri->is_dummy() && (nn[i].apex() != this->_infvrt)) {
      tt[i].tri->set_dummy(); 
      this->_dummy_tris++;
    }
  }

  for(int i = 0; i < 3; ++i) {
    tt[i].tri->mark = mark;
    tt[i].tri->area = area;
    tt[i].link(nn[i]);
    tt[i].next().link(tt[(i+1)%3].prev());
  }

  va->adj = tt[0];
  vb->adj = tt[1];
  vc->adj = tt[2];
  v->adj = tt[2].prev(); 

  te.ori = 0;
}

template <typename T>
void Triangulation<T>::flip24(Vertex* v, TriEdge& te) {
  TriEdge tt[4];
  tt[0] = te;
  tt[1] = te.sym();

  Vertex* va = tt[0].org();
  Vertex* vb = tt[0].dest();
  Vertex* vc = tt[0].apex();
  Vertex* vd = tt[1].apex();

  int c_mark = tt[0].tri->mark;
  int c_area = tt[0].tri->area;
  int d_mark = tt[1].tri->mark;
  int d_area = tt[1].tri->area;

  TriEdge nn[4];
  nn[0] = tt[0].next().sym(); // [c, b]
  nn[1] = tt[0].prev().sym(); // [a, c]
  nn[2] = tt[1].next().sym(); // [d, a]
  nn[3] = tt[1].prev().sym(); // [b, d]

  if(tt[0].tri->is_dummy()) this->_dummy_tris--;
  if(tt[1].tri->is_dummy()) this->_dummy_tris--;

  tt[0].tri->init();
  tt[1].tri->init();
  tt[2].tri = this->_triangles.emplace_back(new Triangle());
  tt[3].tri = this->_triangles.emplace_back(new Triangle());

  tt[0].set(vb, vc, v);
  tt[1].set(vc, va, v);
  tt[2].set(va, vd, v);
  tt[3].set(vd, vb, v);

  tt[0].tri->mark = tt[1].tri->mark = c_mark;
  tt[0].tri->area = tt[1].tri->area = c_area;
  tt[2].tri->mark = tt[3].tri->mark = d_mark;
  tt[2].tri->area = tt[3].tri->area = d_area;

  // we do such check in case that te is a dummy edge
  for(int i = 0; i < 4; ++i) {
    if (nn[i].tri->is_dummy() && (nn[i].apex() != this->_infvrt)) {
      tt[i].tri->set_dummy(); 
      this->_dummy_tris++;
    }
  }
  
  for(int i = 0; i < 4; ++i) {
    tt[i].link(nn[i]);
    tt[i].next().link(tt[(i+1)%4].prev());
  }

  va->adj = tt[2];
  vb->adj = tt[0];
  vc->adj = tt[1];
  vd->adj = tt[3];
  v->adj = tt[3].prev();

  te.ori = 2;
}

template <typename T>
void Triangulation<T>::flip22(TriEdge& te) {
  TriEdge tt[2];
  tt[0] = te;
  tt[1] = te.sym();

  Vertex* va = tt[0].org();
  Vertex* vb = tt[0].dest();
  Vertex* vc = tt[0].apex();
  Vertex* vd = tt[1].apex();

  int c_mark = tt[0].tri->mark;
  int c_area = tt[0].tri->area;
  int d_mark = tt[1].tri->mark;
  int d_area = tt[1].tri->area;

  TriEdge nn[4];
  nn[0] = tt[0].next().sym(); // [c, b]
  nn[1] = tt[0].prev().sym(); // [a, c]
  nn[2] = tt[1].next().sym(); // [d, a]
  nn[3] = tt[1].prev().sym(); // [d, b]

  if(tt[0].tri->is_dummy()) this->_dummy_tris--;
  if(tt[1].tri->is_dummy()) this->_dummy_tris--;

  tt[0].tri->init();
  tt[1].tri->init();
  tt[0].set(vd, vc, va);
  tt[1].set(vc, vd, vb);

  if(vc == this->_infvrt || vd == this->_infvrt) {
    tt[0].tri->set_dummy();
    tt[1].tri->set_dummy();
    this->_dummy_tris += 2;
  } else if(vb == this->_infvrt) {
    tt[1].tri->set_dummy();
    this->_dummy_tris++;
  } else if(va == this->_infvrt) {
    tt[0].tri->set_dummy();
    this->_dummy_tris++;
  }

  if(c_area < 0 || d_area < 0) {
    tt[0].tri->area = tt[1].tri->area = T(-1);
  }
  tt[0].tri->mark = c_mark;
  tt[1].tri->mark = d_mark; // todo

  tt[0].link(tt[1]);
  tt[0].next().link(nn[1]);
  tt[0].prev().link(nn[2]);
  tt[1].prev().link(nn[0]);
  tt[1].next().link(nn[3]);

  va->adj = tt[0].prev();
  vb->adj = tt[1].prev();
  vc->adj = tt[0].next();
  vd->adj = tt[1].next();

  te.ori = 0;
}

template <typename T>
void Triangulation<T>::lawson_flip(Vertex* v, TriEdge& start) {
  Vertex* first = start.org();

  bool do_flip;
  while(true) {
    Vertex* left = start.dest();
    Vertex* right = start.org();

    do_flip = true;

    if(do_flip) {
      TriEdge startsym = start.sym();
      Vertex* top = startsym.apex();

      if(left == this->_infvrt) {
        do_flip = (orient2d(v, right, top) == ORIENTATION::POSITIVE);
      } else if(right == this->_infvrt) {
        do_flip = (orient2d(top, left, v) == ORIENTATION::POSITIVE);
      } else if(top == this->_infvrt) {
        do_flip = false;
      } else {
        do_flip = !local_delaunay_check(left, v, right, top);
      }

      if(do_flip) {
        flip22(start);
        start = start.prev();
      }
    }

    if(!do_flip) {
      if(left == first)
        return;
      start = start.next().sym().next();
    }
  }
}

template <typename T>
int Triangulation<T>::incremental_delaunay() {
  Triangle* firstT = first_tri();

  TriEdge starttri;
  for (unsigned i = 3; i < this->_vertices.size(); ++i) {
    starttri = this->_infvrt->adj;
    if (insert_vertex(this->_vertices[i], starttri) == DUPLICATEVERTEX) {
      std::cerr << "Duplicate vertex found: " << this->_vertices[i]->crd
                << std::endl;
      this->_vertices[i]->type = this->UNUSEDVERTEX;
      this->_unused_vrts++;
    }
  }

  return 1;
}

template <typename T>
typename Triangulation<T>::Triangle* Triangulation<T>::first_tri() {
  unsigned i = 2;
  if (is_same(this->_vertices[0], this->_vertices[1])) {
    for (; i < this->_vertices.size(); ++i) {
      if (!is_same(this->_vertices[1], this->_vertices[i])) break;
    }
    if (i == this->_vertices.size()) {
      std::cerr << "Error: All input vertices are identical.\n";
      quit(TRIANGULATION_QUIT_ON_INPUT_ERROR);
    }
    std::swap(this->_vertices[1], this->_vertices[i]);
  }

  i = 2;
  ORIENTATION ori;
  for (; i < this->_vertices.size(); ++i) {
    ori = orient2d(this->_vertices[0], this->_vertices[1], this->_vertices[i]);
    if (ori != ORIENTATION::ON) break;
  }
  if (i == this->_vertices.size()) {
    std::cerr << "Error: Input vertices are collinear.\n";
    quit(TRIANGULATION_QUIT_ON_INPUT_ERROR);
  }
  if (i > 2) std::swap(this->_vertices[2], this->_vertices[i]);

  if (ori == ORIENTATION::NEGATIVE)
    std::swap(this->_vertices[0], this->_vertices[1]);

  return first_tri(this->_vertices[0], this->_vertices[1], this->_vertices[2]);
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

  for (unsigned i = 1; i < 4; ++i) {
    te[i].tri->set_dummy();
  }
  this->_dummy_tris += 3;

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
  assert(v0 != this->_infvrt && v1 != this->_infvrt && v2 != this->_infvrt);
  return orient_2d(v0->crd, v1->crd, v2->crd);
}

template <typename T>
bool Triangulation<T>::local_delaunay_check(Vertex* va, Vertex* vb, Vertex* vc, Vertex* vd) const {
  assert(va != this->_infvrt && vb != this->_infvrt && vc != this->_infvrt && vd != this->_infvrt);
  return is_locally_delaunay(va->crd, vb->crd, vc->crd, vd->crd);
}

template <typename T>
T Triangulation<T>::square_length(Vertex* v0, Vertex* v1) const {
  return (v0->crd - v1->crd).length_square();
}

template <typename T>
bool Triangulation<T>::is_same(Vertex* v0, Vertex* v2) const {
  return (v0->crd == v2->crd);
}

template <typename T>
void Triangulation<T>::quit(int status) {
  this->clean();
  throw status;
}

}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_triangulation_impl_h__