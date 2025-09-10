#include "CMTL/geo2d/surface_mesh.h"
#include "CMTL/io/surface_mesh/read_obj.h"
#include "CMTL/io/surface_mesh/write_obj.h"
#include <gtest/gtest.h>

typedef CMTL::geo2d::SurfaceMesh<double> Surface_mesh;
typedef Surface_mesh::VertexHandle VertexHandle;
typedef Surface_mesh::HalfedgeHandle HalfedgeHandle;
typedef Surface_mesh::FaceHandle FaceHandle;
typedef Surface_mesh::Point Point;

TEST(SurfaceMesh2Test, ConstructTest)
{
    Surface_mesh sm;
    std::vector<VertexHandle> vhs(4);
    vhs[0] = sm.add_vertex(Point(0, 0));
    vhs[1] = sm.add_vertex(Point(2, 0));
    vhs[2] = sm.add_vertex(Point(1, 2));
    vhs[3] = sm.add_vertex(Point(1, 1));
    
    std::vector<FaceHandle> fhs(3);
    fhs[0] = sm.add_face(vhs[0], vhs[1], vhs[3]);
    fhs[1] = sm.add_face(vhs[1], vhs[2], vhs[3]);
    fhs[2] = sm.add_face(vhs[0], vhs[3], vhs[2]);

    std::vector<HalfedgeHandle> hes(12);
    hes[0] = sm.find_halfedge(vhs[0], vhs[1]);
    hes[1] = sm.find_halfedge(vhs[1], vhs[0]);
    hes[2] = sm.find_halfedge(vhs[1], vhs[3]);
    hes[3] = sm.find_halfedge(vhs[3], vhs[1]);
    hes[4] = sm.find_halfedge(vhs[3], vhs[0]);
    hes[5] = sm.find_halfedge(vhs[0], vhs[3]);
    hes[6] = sm.find_halfedge(vhs[3], vhs[2]);
    hes[7] = sm.find_halfedge(vhs[2], vhs[3]);
    hes[8] = sm.find_halfedge(vhs[1], vhs[2]);
    hes[9] = sm.find_halfedge(vhs[2], vhs[1]);
    hes[10] = sm.find_halfedge(vhs[2], vhs[0]);
    hes[11] = sm.find_halfedge(vhs[0], vhs[2]);

    ASSERT_EQ(sm.n_vertices(), 4);
    ASSERT_EQ(sm.n_faces(), 3);
    ASSERT_EQ(sm.n_edges(), 6);

    ASSERT_EQ(sm.next_halfedge_handle(hes[0]), hes[2]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[0]), hes[4]);
    ASSERT_EQ(sm.vertex_handle(hes[0]), vhs[1]);
    ASSERT_EQ(sm.face_handle(hes[0]), fhs[0]);
    
    ASSERT_EQ(sm.next_halfedge_handle(hes[1]), hes[11]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[1]), hes[9]);
    ASSERT_EQ(sm.vertex_handle(hes[1]), vhs[0]);
    ASSERT_EQ(sm.face_handle(hes[1]), FaceHandle());

    ASSERT_EQ(sm.next_halfedge_handle(hes[2]), hes[4]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[2]), hes[0]);
    ASSERT_EQ(sm.vertex_handle(hes[2]), vhs[3]);
    ASSERT_EQ(sm.face_handle(hes[2]), fhs[0]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[3]), hes[8]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[3]), hes[7]);
    ASSERT_EQ(sm.vertex_handle(hes[3]), vhs[1]);
    ASSERT_EQ(sm.face_handle(hes[3]), fhs[1]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[4]), hes[0]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[4]), hes[2]);
    ASSERT_EQ(sm.vertex_handle(hes[4]), vhs[0]);
    ASSERT_EQ(sm.face_handle(hes[4]), fhs[0]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[5]), hes[6]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[5]), hes[10]);
    ASSERT_EQ(sm.vertex_handle(hes[5]), vhs[3]);
    ASSERT_EQ(sm.face_handle(hes[5]), fhs[2]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[6]), hes[10]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[6]), hes[5]);
    ASSERT_EQ(sm.vertex_handle(hes[6]), vhs[2]);
    ASSERT_EQ(sm.face_handle(hes[6]), fhs[2]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[7]), hes[3]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[7]), hes[8]);
    ASSERT_EQ(sm.vertex_handle(hes[7]), vhs[3]);
    ASSERT_EQ(sm.face_handle(hes[7]), fhs[1]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[8]), hes[7]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[8]), hes[3]);
    ASSERT_EQ(sm.vertex_handle(hes[8]), vhs[2]);
    ASSERT_EQ(sm.face_handle(hes[8]), fhs[1]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[9]), hes[1]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[9]), hes[11]);
    ASSERT_EQ(sm.vertex_handle(hes[9]), vhs[1]);
    ASSERT_EQ(sm.face_handle(hes[9]), FaceHandle());

    ASSERT_EQ(sm.next_halfedge_handle(hes[10]), hes[5]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[10]), hes[6]);
    ASSERT_EQ(sm.vertex_handle(hes[10]), vhs[0]);
    ASSERT_EQ(sm.face_handle(hes[10]), fhs[2]);

    ASSERT_EQ(sm.next_halfedge_handle(hes[11]), hes[9]);
    ASSERT_EQ(sm.prev_halfedge_handle(hes[11]), hes[1]);
    ASSERT_EQ(sm.vertex_handle(hes[11]), vhs[2]);
    ASSERT_EQ(sm.face_handle(hes[11]), FaceHandle());

    EXPECT_TRUE(sm.halfedge_handle(fhs[0])==hes[0]||sm.halfedge_handle(fhs[0])==hes[2]||sm.halfedge_handle(fhs[0])==hes[4]);
    EXPECT_TRUE(sm.halfedge_handle(fhs[1])==hes[3]||sm.halfedge_handle(fhs[1])==hes[8]||sm.halfedge_handle(fhs[1])==hes[7]);
    EXPECT_TRUE(sm.halfedge_handle(fhs[2])==hes[5]||sm.halfedge_handle(fhs[2])==hes[6]||sm.halfedge_handle(fhs[2])==hes[10]);

    ASSERT_EQ(sm.halfedge_handle(vhs[0]), hes[11]);
    ASSERT_EQ(sm.halfedge_handle(vhs[1]), hes[1]);
    ASSERT_EQ(sm.halfedge_handle(vhs[2]), hes[9]);
}

TEST(SurfaceMesh2Test, IteratorTest)
{
    Surface_mesh sm;
    std::vector<VertexHandle> vhs(4);
    vhs[0] = sm.add_vertex(Point(0, 0));
    vhs[1] = sm.add_vertex(Point(2, 0));
    vhs[2] = sm.add_vertex(Point(1, 2));
    vhs[3] = sm.add_vertex(Point(1, 1));
    
    std::vector<FaceHandle> fhs(3);
    fhs[0] = sm.add_face(vhs[0], vhs[1], vhs[3]);
    fhs[1] = sm.add_face(vhs[1], vhs[2], vhs[3]);
    fhs[2] = sm.add_face(vhs[0], vhs[3], vhs[2]);

    std::vector<HalfedgeHandle> hes(12);
    hes[0] = sm.find_halfedge(vhs[0], vhs[1]);
    hes[1] = sm.find_halfedge(vhs[1], vhs[0]);
    hes[2] = sm.find_halfedge(vhs[1], vhs[3]);
    hes[3] = sm.find_halfedge(vhs[3], vhs[1]);
    hes[4] = sm.find_halfedge(vhs[3], vhs[0]);
    hes[5] = sm.find_halfedge(vhs[0], vhs[3]);
    hes[6] = sm.find_halfedge(vhs[3], vhs[2]);
    hes[7] = sm.find_halfedge(vhs[2], vhs[3]);
    hes[8] = sm.find_halfedge(vhs[1], vhs[2]);
    hes[9] = sm.find_halfedge(vhs[2], vhs[1]);
    hes[10] = sm.find_halfedge(vhs[2], vhs[0]);
    hes[11] = sm.find_halfedge(vhs[0], vhs[2]);

    std::set<VertexHandle> vset;
    std::set<HalfedgeHandle> heset;
    std::set<FaceHandle> fset;

    vset.clear();
    for(auto vvit = sm.vv_begin(vhs[0]); vvit != sm.vv_end(vhs[0]); ++vvit)
    {
        vset.insert(*vvit);
    }
    ASSERT_EQ(vset.size(), 3);
    ASSERT_TRUE(vset.find(vhs[1]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[2]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[3]) != vset.end());

    vset.clear();
    for(auto vvit = sm.vv_begin(vhs[1]); vvit != sm.vv_end(vhs[1]); ++vvit)
    {
        vset.insert(*vvit);
    }
    ASSERT_EQ(vset.size(), 3);
    ASSERT_TRUE(vset.find(vhs[0]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[2]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[3]) != vset.end());

    vset.clear();
    for(auto vvit = sm.vv_begin(vhs[2]); vvit != sm.vv_end(vhs[2]); ++vvit)
    {
        vset.insert(*vvit);
    }
    ASSERT_EQ(vset.size(), 3);
    ASSERT_TRUE(vset.find(vhs[0]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[1]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[3]) != vset.end());

    vset.clear();
    for(auto vvit = sm.vv_begin(vhs[3]); vvit != sm.vv_end(vhs[3]); ++vvit)
    {
        vset.insert(*vvit);
    }
    ASSERT_EQ(vset.size(), 3);
    ASSERT_TRUE(vset.find(vhs[0]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[1]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[2]) != vset.end());

    heset.clear();
    for(auto vhit = sm.voh_begin(vhs[0]); vhit != sm.voh_end(vhs[0]); ++vhit)
    {
        heset.insert(*vhit);
    }
    ASSERT_EQ(heset.size(), 3);
    ASSERT_TRUE(heset.find(hes[0]) != heset.end());
    ASSERT_TRUE(heset.find(hes[5]) != heset.end());
    ASSERT_TRUE(heset.find(hes[11]) != heset.end());

    heset.clear();
    for(auto vhit = sm.voh_begin(vhs[1]); vhit != sm.voh_end(vhs[1]); ++vhit)
    {
        heset.insert(*vhit);
    }
    ASSERT_EQ(heset.size(), 3);
    ASSERT_TRUE(heset.find(hes[1]) != heset.end());
    ASSERT_TRUE(heset.find(hes[2]) != heset.end());
    ASSERT_TRUE(heset.find(hes[8]) != heset.end());

    heset.clear();
    for(auto vhit = sm.voh_begin(vhs[2]); vhit != sm.voh_end(vhs[2]); ++vhit)
    {
        heset.insert(*vhit);
    }
    ASSERT_EQ(heset.size(), 3);
    ASSERT_TRUE(heset.find(hes[10]) != heset.end());
    ASSERT_TRUE(heset.find(hes[7]) != heset.end());
    ASSERT_TRUE(heset.find(hes[9]) != heset.end());

    heset.clear();
    for(auto vhit = sm.voh_begin(vhs[3]); vhit != sm.voh_end(vhs[3]); ++vhit)
    {
        heset.insert(*vhit);
    }
    ASSERT_EQ(heset.size(), 3);
    ASSERT_TRUE(heset.find(hes[6]) != heset.end());
    ASSERT_TRUE(heset.find(hes[4]) != heset.end());
    ASSERT_TRUE(heset.find(hes[3]) != heset.end());

    fset.clear();
    for(auto vfit = sm.vf_begin(vhs[0]); vfit != sm.vf_end(vhs[0]); ++vfit)
    {
        fset.insert(*vfit);
    }
    ASSERT_EQ(fset.size(), 2);
    ASSERT_TRUE(fset.find(fhs[0]) != fset.end());
    ASSERT_TRUE(fset.find(fhs[2]) != fset.end());

    fset.clear();
    for(auto vfit = sm.vf_begin(vhs[1]); vfit != sm.vf_end(vhs[1]); ++vfit)
    {
        fset.insert(*vfit);
    }
    ASSERT_EQ(fset.size(), 2);
    ASSERT_TRUE(fset.find(fhs[0]) != fset.end());
    ASSERT_TRUE(fset.find(fhs[1]) != fset.end());

    fset.clear();
    for(auto vfit = sm.vf_begin(vhs[2]); vfit != sm.vf_end(vhs[2]); ++vfit)
    {
        fset.insert(*vfit);
    }
    ASSERT_EQ(fset.size(), 2);
    ASSERT_TRUE(fset.find(fhs[1]) != fset.end());
    ASSERT_TRUE(fset.find(fhs[2]) != fset.end());

    fset.clear();
    for(auto vfit = sm.vf_begin(vhs[3]); vfit != sm.vf_end(vhs[3]); ++vfit)
    {
        fset.insert(*vfit);
    }
    ASSERT_EQ(fset.size(), 3);
    ASSERT_TRUE(fset.find(fhs[0]) != fset.end());
    ASSERT_TRUE(fset.find(fhs[1]) != fset.end());
    ASSERT_TRUE(fset.find(fhs[2]) != fset.end());

    vset.clear();
    for(auto fvit = sm.fv_begin(fhs[0]); fvit != sm.fv_end(fhs[0]); ++fvit)
    {
        vset.insert(*fvit);
    }
    ASSERT_EQ(vset.size(), 3);
    ASSERT_TRUE(vset.find(vhs[0]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[1]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[3]) != vset.end());

    vset.clear();
    for(auto fvit = sm.fv_begin(fhs[1]); fvit != sm.fv_end(fhs[1]); ++fvit)
    {
        vset.insert(*fvit);
    }
    ASSERT_EQ(vset.size(), 3);
    ASSERT_TRUE(vset.find(vhs[1]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[2]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[3]) != vset.end());

    vset.clear();
    for(auto fvit = sm.fv_begin(fhs[2]); fvit != sm.fv_end(fhs[2]); ++fvit)
    {
        vset.insert(*fvit);
    }
    ASSERT_EQ(vset.size(), 3);
    ASSERT_TRUE(vset.find(vhs[0]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[2]) != vset.end());
    ASSERT_TRUE(vset.find(vhs[3]) != vset.end());

    heset.clear();
    for(auto fvit = sm.fh_begin(fhs[0]); fvit != sm.fh_end(fhs[0]); ++fvit)
    {
        heset.insert(*fvit);
    }
    ASSERT_EQ(heset.size(), 3);
    ASSERT_TRUE(heset.find(hes[0]) != heset.end());
    ASSERT_TRUE(heset.find(hes[2]) != heset.end());
    ASSERT_TRUE(heset.find(hes[4]) != heset.end());

    heset.clear();
    for(auto fvit = sm.fh_begin(fhs[1]); fvit != sm.fh_end(fhs[1]); ++fvit)
    {
        heset.insert(*fvit);
    }
    ASSERT_EQ(heset.size(), 3);
    ASSERT_TRUE(heset.find(hes[3]) != heset.end());
    ASSERT_TRUE(heset.find(hes[8]) != heset.end());
    ASSERT_TRUE(heset.find(hes[7]) != heset.end());

    heset.clear();
    for(auto fvit = sm.fh_begin(fhs[2]); fvit != sm.fh_end(fhs[2]); ++fvit)
    {
        heset.insert(*fvit);
    }
    ASSERT_EQ(heset.size(), 3);
    ASSERT_TRUE(heset.find(hes[6]) != heset.end());
    ASSERT_TRUE(heset.find(hes[10]) != heset.end());
    ASSERT_TRUE(heset.find(hes[5]) != heset.end());
}

void test1()
{
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
    Surface_mesh sm;
    std::vector<VertexHandle> vhs(4);
    vhs[0] = sm.add_vertex(Point(0, 0));
    vhs[1] = sm.add_vertex(Point(2, 0));
    vhs[2] = sm.add_vertex(Point(1, 1));
    vhs[3] = sm.add_vertex(Point(1, -1));
    sm.add_face(vhs[0], vhs[1], vhs[2]);
    sm.add_face(vhs[0], vhs[3], vhs[1]);
    CMTL::io::write_obj(sm, "geo2d_surface_mesh_test2.obj");
    for(auto eit = sm.edges_begin(); eit != sm.edges_end(); ++eit)
    {
        if(sm.is_flip_ok(*eit))
            sm.flip(*eit);
    }
    CMTL::io::write_obj(sm, "geo2d_surface_mesh_test2_2.obj");
}

void test3()
{
    Surface_mesh sm;
    CMTL::io::read_obj(sm, "/data/home/yangjinlin/work/code/geometry/mesh_data/leaf.obj");
    CMTL::io::write_obj(sm, "geo2d_surface_mesh_test2.obj");
}

void test_split()
{
    Surface_mesh sm;
    std::vector<VertexHandle> vhs(4);
    vhs[0] = sm.add_vertex(Point(0, 0));
    vhs[1] = sm.add_vertex(Point(2, 0));
    vhs[2] = sm.add_vertex(Point(1, 1));
    vhs[3] = sm.add_vertex(Point(1, -1));
    sm.add_face(vhs[0], vhs[1], vhs[2]);
    sm.add_face(vhs[0], vhs[3], vhs[1]);

    HalfedgeHandle middle_edge = sm.find_halfedge(vhs[1], vhs[0]);
    sm.split(sm.edge_handle(middle_edge), Point(1,0), true);
    CMTL::io::write_obj(sm, "geo2d_surface_mesh_split_test.obj");
}

void edge_split_test()
{
    Surface_mesh sm;
    std::vector<VertexHandle> vhs(6);
    vhs[0] = sm.add_vertex(Point(0, 0));
    vhs[1] = sm.add_vertex(Point(1, 1));
    vhs[2] = sm.add_vertex(Point(2, 1));
    vhs[3] = sm.add_vertex(Point(3, 0));
    vhs[4] = sm.add_vertex(Point(2, -1));
    vhs[5] = sm.add_vertex(Point(1, -1));
    sm.add_face(vhs[0], vhs[3], vhs[2], vhs[1]);
    sm.add_face(vhs[0], vhs[5], vhs[4], vhs[3]);

    HalfedgeHandle middle_edge = sm.find_halfedge(vhs[0], vhs[3]);
    sm.split(sm.edge_handle(middle_edge), Point(1,0), true);
    CMTL::io::write_obj(sm, "geo2d_surface_mesh_edge_split_test.obj");
}

void split_face_test()
{
    Surface_mesh sm;
    std::vector<VertexHandle> vhs(4);
    vhs[0] = sm.add_vertex(Point(0, 0));
    vhs[1] = sm.add_vertex(Point(1, -1));
    vhs[2] = sm.add_vertex(Point(2, 0));
    vhs[3] = sm.add_vertex(Point(1, 1));
    FaceHandle fh = sm.add_face(vhs[0], vhs[1], vhs[2], vhs[3]);
    sm.split_face(fh, vhs[1], vhs[3]);
    CMTL::io::write_obj(sm, "geo2d_surface_mesh_face_split_test.obj");
}

int main()
{
    //test1();
    //test2();
    //test3();
    //test_split();
    edge_split_test();
    //split_face_test();
}