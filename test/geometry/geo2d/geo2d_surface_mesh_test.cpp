#include "CMTL/geometry/geo2d/geo2d_surface_mesh.h"

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

int main()
{
    test1();
}