#include "CMTL/geometry/geo3d/geo3d_surface_mesh.h"
#include "CMTL/geometry/IO/import_obj.h"
#include "CMTL/geometry/IO/export_obj.h"

typedef CMTL::geometry::geo3d::SurfaceMesh<double> Surface_mesh;
typedef Surface_mesh::Point Point;

void test1()
{
    Surface_mesh sm;
    CMTL::geometry::io::import_obj(sm, "/data/home/yangjinlin/work/code/geometry/mesh_data/cube.obj");
    CMTL::geometry::io::export_obj(sm, "import_obj_test1.obj");
}

int main()
{
    test1();
}