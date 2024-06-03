#include "CMTL/geometry/geo3d/geo3d_surface_mesh.h"

typedef CMTL::geometry::geo3d::SurfaceMesh<double> Surface_mesh;
typedef Surface_mesh::Point Point;

void check(const Surface_mesh& sm)
{
    for(auto hit = sm.halfedges_begin(); hit != sm.halfedges_end(); ++hit)
    {
        assert(sm.next_halfedge_handle(*hit).idx() == hit->next().idx());
        assert(sm.prev_halfedge_handle(*hit).idx() == hit->prev().idx());
        assert(sm.opposite_halfedge_handle(*hit).idx() == hit->opposite().idx());
    }
}

void test1()
{
    std::cout << "=====test1=====" << std::endl;
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
        std::cout << sm.point(*it) << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "vertices near " << sm.point(face1[0]) << std::endl;
    for(auto it = sm.vv_begin(face1[0]); it != sm.vv_end(face1[0]); ++it)
    {
        std::cout << sm.point(*it) << std::endl;
    }
    std::cout << std::endl;
}

void test2()
{
    std::cout << "=====test2=====" << std::endl;
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

    sm.print();
    check(sm);

    for(auto vv_it = sm.vv_ccwbegin(vertices[0]); vv_it != sm.vv_ccwend(vertices[0]); ++vv_it)
    {
        std::cout << vv_it->idx() << " ";
    }
    std::cout << std::endl;

    for(auto vv_it = sm.vv_cwbegin(vertices[0]); vv_it != sm.vv_cwend(vertices[0]); ++vv_it)
    {
        std::cout << vv_it->idx() << " ";
    }
    std::cout << std::endl;

    for(auto vf_it = sm.vf_begin(vertices[0]); vf_it != sm.vf_end(vertices[0]); ++vf_it)
    {
        std::cout << vf_it->idx() << " ";
    }
    std::cout << std::endl;

    for(auto vf_it = sm.vf_cwbegin(vertices[0]); vf_it != sm.vf_cwend(vertices[0]); ++vf_it)
    {
        std::cout << vf_it->idx() << " ";
    }
    std::cout << std::endl;

    for(auto fv_it = sm.fv_ccwbegin(sm.face_handle(0)); fv_it != sm.fv_ccwend(sm.face_handle(0)); ++fv_it)
    {
        std::cout << fv_it->idx() << " ";
    }
    std::cout << std::endl;

    for(auto fv_it = sm.fv_cwbegin(sm.face_handle(0)); fv_it != sm.fv_cwend(sm.face_handle(0)); ++fv_it)
    {
        std::cout << fv_it->idx() << " ";
    }
    std::cout << std::endl;

    for(auto fh_it = sm.fh_ccwbegin(sm.face_handle(0)); fh_it != sm.fh_ccwend(sm.face_handle(0)); ++fh_it)
    {
        std::cout << fh_it->idx() << " ";
    }
    std::cout << std::endl;

    for(auto fh_it = sm.fh_cwbegin(sm.face_handle(0)); fh_it != sm.fh_cwend(sm.face_handle(0)); ++fh_it)
    {
        std::cout << fh_it->idx() << " ";
    }
    std::cout << std::endl;

}

int main()
{
    test1();
    test2();
}