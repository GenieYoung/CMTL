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

int main()
{
    test0();
}