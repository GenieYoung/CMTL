#include "CMTL/geometry/geo3d/geo3d_surface_mesh.h"

typedef CMTL::geometry::geo3d::SurfaceMesh<double> Surface_mesh;
typedef Surface_mesh::PointAttribute Point;

void test1()
{
    Surface_mesh sm;
    std::vector<Surface_mesh::VertexHandle> face1;
    face1.push_back(sm.add_vertex(Point(0,0,0)));
    face1.push_back(sm.add_vertex(Point(1,0,0)));
    face1.push_back(sm.add_vertex(Point(0,1,0)));
    sm.add_face(face1);
    std::cout << sm.n_vertices() << " " << sm.n_halfedges() << " " << sm.n_edges() << " " << sm.n_faces() << std::endl;
    
    std::cout << "all vertices" << std::endl;
    for(auto it = sm.vertices_begin(); it != sm.vertices_end(); ++it)
    {
        std::cout << sm.vertex_attribute(*it) << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "vertices near " << sm.vertex_attribute(face1[0]) << std::endl;
    for(auto it = sm.vv_begin(face1[0]); it != sm.vv_end(face1[0]); ++it)
    {
        std::cout << sm.vertex_attribute(*it) << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    test1();
}