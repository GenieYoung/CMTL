#include "CMTL/geometry/geo2d/geo2d_surface_mesh.h"
#include "CMTL/geometry/io/surface_mesh/read_obj.h"
#include "CMTL/geometry/io/surface_mesh/write_obj.h"

void test1()
{
    typedef CMTL::geometry::geo2d::SurfaceMesh<double> Surface_mesh;
    typedef Surface_mesh::VertexHandle VertexHandle;
    typedef Surface_mesh::Point Point;
    Surface_mesh sm;
    VertexHandle v0 = sm.add_vertex(Point(0, 0));
    std::cout << sm.n_vertices() << " " << sm.n_edges() << " " << sm.n_faces() << std::endl;
    std::cout << sm.degree(v0) << std::endl;
    unsigned vf_count = 0;
    for(auto vf = sm.vf_begin(v0); vf != sm.vf_end(v0); ++vf)
        vf_count++;
    std::cout << vf_count << std::endl;
}

void test2()
{
    typedef CMTL::geometry::geo2d::SurfaceMesh<double> Surface_mesh;
    typedef Surface_mesh::VertexHandle VertexHandle;
    typedef Surface_mesh::Point Point;
    Surface_mesh sm;
    std::vector<VertexHandle> vhs(4);
    vhs[0] = sm.add_vertex(Point(0, 0));
    vhs[1] = sm.add_vertex(Point(2, 0));
    vhs[2] = sm.add_vertex(Point(1, 1));
    vhs[3] = sm.add_vertex(Point(1, -1));
    sm.add_face(vhs[0], vhs[1], vhs[2]);
    sm.add_face(vhs[0], vhs[3], vhs[1]);
    CMTL::geometry::io::write_obj(sm, "geo2d_surface_mesh_test2.obj");
    for(auto eit = sm.edges_begin(); eit != sm.edges_end(); ++eit)
    {
        if(sm.is_flip_ok(*eit))
            sm.flip(*eit);
    }
    CMTL::geometry::io::write_obj(sm, "geo2d_surface_mesh_test2_2.obj");
}

void test3()
{
    typedef CMTL::geometry::geo2d::SurfaceMesh<double> Surface_mesh;
    typedef Surface_mesh::Point Point;
    Surface_mesh sm;
    CMTL::geometry::io::read_obj(sm, "/data/home/yangjinlin/work/code/geometry/mesh_data/leaf.obj");
    CMTL::geometry::io::write_obj(sm, "geo2d_surface_mesh_test2.obj");
}

int main()
{
    test1();
    test2();
    test3();
}