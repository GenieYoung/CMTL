#include "CMTL/algorithm/lawson_flip.h"

#include "CMTL/io/surface_mesh/read_obj.h"
#include "CMTL/io/surface_mesh/write_obj.h"

void test0() {
  typedef CMTL::geo2d::SurfaceMesh<double> SurfaceMesh;
  SurfaceMesh sm;
  CMTL::io::read_obj(sm, "../mesh_data/leaf.obj");
  CMTL::io::write_obj(sm, "lawson_flip_test0_before.obj");
  CMTL::algorithm::lawson_flip(sm);
  CMTL::io::write_obj(sm, "lawson_flip_test0_after.obj");
}

void test1() {
  typedef CMTL::geo2d::SurfaceMesh<double> SurfaceMesh;
  SurfaceMesh sm;
  CMTL::io::read_obj(sm, "../mesh_data/leaf.obj");
  CMTL::io::write_obj(sm, "lawson_flip_test1_before.obj");
  std::vector<SurfaceMesh::EdgeHandle> constrained_edge;
  for (auto eit = sm.edges_begin(); eit != sm.edges_end(); ++eit)
    if (eit->idx() % 10 == 0) constrained_edge.push_back(*eit);
  CMTL::algorithm::lawson_flip(sm, constrained_edge);
  CMTL::io::write_obj(sm, "lawson_flip_test1_after.obj");
}

int main() {
  test0();
  test1();
}