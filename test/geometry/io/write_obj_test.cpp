#include "CMTL/geometry/geo3d/geo3d_surface_mesh.h"
#include "CMTL/geometry/io/surface_mesh/write_obj.h"

typedef CMTL::geometry::geo3d::SurfaceMesh<double> Surface_mesh;
typedef Surface_mesh::Point Point;

void test1()
{
    Surface_mesh sm;
    std::vector<Surface_mesh::VertexHandle> vertices;
    vertices.push_back(sm.add_vertex(Point(0,0,0)));
    vertices.push_back(sm.add_vertex(Point(1,0,0)));
    vertices.push_back(sm.add_vertex(Point(1,1,0)));
    vertices.push_back(sm.add_vertex(Point(0,1,0)));
    vertices.push_back(sm.add_vertex(Point(-1,1,0)));
    vertices.push_back(sm.add_vertex(Point(-1,0,0)));
    vertices.push_back(sm.add_vertex(Point(-1,-1,0)));
    vertices.push_back(sm.add_vertex(Point(0,-1,0)));
    vertices.push_back(sm.add_vertex(Point(1,-1,0)));
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[1], vertices[2], vertices[3]});
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[3], vertices[4], vertices[5]});
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[5], vertices[6], vertices[7]});
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[7], vertices[8], vertices[1]});
    CMTL::geometry::io::write_obj(sm, "out.obj");
}

int main()
{
    test1();
    return 0;
}