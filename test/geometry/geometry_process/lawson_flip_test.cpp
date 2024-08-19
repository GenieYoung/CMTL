#include "CMTL/geometry/geometry_process/lawson_flip.h"
#include "CMTL/geometry/io/surface_mesh/read_obj.h"
#include "CMTL/geometry/io/surface_mesh/write_obj.h"

void test0()
{
    typedef CMTL::geometry::geo2d::SurfaceMesh<double> SurfaceMesh;
    SurfaceMesh sm;
    CMTL::geometry::io::read_obj(sm, "../mesh_data/leaf.obj");
    CMTL::geometry::io::write_obj(sm, "lawson_flip_test0_before.obj");
    CMTL::geometry::geometry_process::lawson_flip(sm);
    CMTL::geometry::io::write_obj(sm, "lawson_flip_test0_after.obj");
}

void test1()
{
    typedef CMTL::geometry::geo2d::SurfaceMesh<double> SurfaceMesh;
    SurfaceMesh sm;
    CMTL::geometry::io::read_obj(sm, "../mesh_data/leaf.obj");
    CMTL::geometry::io::write_obj(sm, "lawson_flip_test1_before.obj");
    std::vector<SurfaceMesh::EdgeHandle> constrained_edge;
    for(auto eit = sm.edges_begin(); eit != sm.edges_end(); ++eit)
        if(eit->idx() % 10 == 0)
            constrained_edge.push_back(*eit);
    CMTL::geometry::geometry_process::lawson_flip(sm, constrained_edge);
    CMTL::geometry::io::write_obj(sm, "lawson_flip_test1_after.obj");
}

int main()
{
    test0();
    test1();
}