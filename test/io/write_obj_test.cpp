#include "CMTL/geo3d/geo3d_surface_mesh.h"
#include "CMTL/io/surface_mesh/write_obj.h"
#include "CMTL/io/surface_mesh/read_obj.h"

void test1()
{
    typedef CMTL::geo3d::SurfaceMesh<double> Surface_mesh;
    typedef Surface_mesh::Point Point;
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
    CMTL::io::write_obj(sm, "write_obj_test1.obj");
}

void test2()
{
    typedef CMTL::geo3d::SurfaceMesh<mpq_class> Surface_mesh;
    typedef Surface_mesh::Point Point;
    Surface_mesh sm;
    std::vector<Surface_mesh::VertexHandle> vertices;
    vertices.push_back(sm.add_vertex(Point(0,0,0)));
    vertices.push_back(sm.add_vertex(Point(1.23456,0,0)));
    vertices.push_back(sm.add_vertex(Point(1.23456,1.23456,0)));
    vertices.push_back(sm.add_vertex(Point(0,1.23456,0)));
    vertices.push_back(sm.add_vertex(Point(-1.23456,1.23456,0)));
    vertices.push_back(sm.add_vertex(Point(-1.23456,0,0)));
    vertices.push_back(sm.add_vertex(Point(-1.23456,-1.23456,0)));
    vertices.push_back(sm.add_vertex(Point(0,-1.23456,0)));
    vertices.push_back(sm.add_vertex(Point(1.23456,-1.23456,0)));
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[1], vertices[2], vertices[3]});
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[3], vertices[4], vertices[5]});
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[5], vertices[6], vertices[7]});
    sm.add_face(std::vector<Surface_mesh::VertexHandle>{vertices[0], vertices[7], vertices[8], vertices[1]});
    CMTL::io::write_obj(sm, "write_obj_test2.obj");
    CMTL::io::read_obj(sm, "write_obj_test2.obj");
    CMTL::io::write_obj(sm, "write_obj_test2_1.obj");
}

int main()
{
    test1();
    test2();
    return 0;
}