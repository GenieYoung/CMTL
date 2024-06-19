#include "CMTL/geometry/geometry_process/extrude_surface.h"
#include "CMTL/geometry/IO/export_obj.h"
#include "gmpxx.h"

typedef CMTL::geometry::geo3d::SurfaceMesh<double> SurfaceMesh;
typedef SurfaceMesh::Point Point;
using CMTL::geometry::geometry_process::extrude_surface;
using CMTL::geometry::io::export_obj;

void test1()
{
    SurfaceMesh sm;
    std::vector<SurfaceMesh::VertexHandle> vertices;
    vertices.push_back(sm.add_vertex(Point(0,0,1)));
    vertices.push_back(sm.add_vertex(Point(1,0,0)));
    vertices.push_back(sm.add_vertex(Point(1,1,0)));
    vertices.push_back(sm.add_vertex(Point(0,1,-1)));
    vertices.push_back(sm.add_vertex(Point(-1,1,0)));
    vertices.push_back(sm.add_vertex(Point(-1,0,0)));
    // vertices.push_back(sm.add_vertex(Point(-1,-1,0)));
    // vertices.push_back(sm.add_vertex(Point(0,-1,0)));
    // vertices.push_back(sm.add_vertex(Point(1,-1,0)));
    sm.add_face(std::vector<SurfaceMesh::VertexHandle>{vertices[0], vertices[1], vertices[2]});
    sm.add_face(std::vector<SurfaceMesh::VertexHandle>{vertices[0], vertices[2], vertices[3]});
    sm.add_face(std::vector<SurfaceMesh::VertexHandle>{vertices[0], vertices[3], vertices[4]});
    sm.add_face(std::vector<SurfaceMesh::VertexHandle>{vertices[0], vertices[4], vertices[5]});
    // sm.add_face(std::vector<SurfaceMesh::VertexHandle>{vertices[0], vertices[5], vertices[6], vertices[7]});
    // sm.add_face(std::vector<SurfaceMesh::VertexHandle>{vertices[0], vertices[7], vertices[8], vertices[1]});
    export_obj(sm, "test1_input.obj");
    SurfaceMesh extrude_mesh;
    extrude_surface(sm, 0.1, extrude_mesh);
    export_obj(extrude_mesh, "test1_output.obj");
}

int main()
{
    test1();
}