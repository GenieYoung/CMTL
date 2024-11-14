#include "CMTL/io/surface_mesh/read_obj.h"
#include "CMTL/io/surface_mesh/write_obj.h"


void test1()
{
    typedef CMTL::geo3d::SurfaceMesh<double> Surface_mesh;
    typedef Surface_mesh::Point Point;
    Surface_mesh sm;
    CMTL::io::read_obj(sm, "/data/home/yangjinlin/work/code/geometry/mesh_data/cube.obj");
    CMTL::io::write_obj(sm, "read_obj_test1.obj");
}

void test2()
{
    typedef CMTL::geo2d::SurfaceMesh<double> Surface_mesh;
    typedef Surface_mesh::Point Point;
    Surface_mesh sm;
    CMTL::io::read_obj(sm, "/data/home/yangjinlin/work/code/geometry/mesh_data/leaf.obj");
    CMTL::io::write_obj(sm, "read_obj_test2.obj");
}

int main()
{
    test1();
    test2();
}