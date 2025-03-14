#include <set>
#include "CMTL/geo2d/geo2d_polygon.h"
#include "CMTL/geometry_algorithm/triangulate.h"
#include "CMTL/io/polygon/write_obj.h"
#include "CMTL/io/polygon_soup/write_obj.h"

void test1()
{
    std::vector<CMTL::geo2d::Point<double>> points;
    points.push_back(CMTL::geo2d::Point<double>{0,0});
    points.push_back(CMTL::geo2d::Point<double>{1,0});
    points.push_back(CMTL::geo2d::Point<double>{0.3,0.3});
    points.push_back(CMTL::geo2d::Point<double>{0,1});
    CMTL::geo2d::Polygon<double> polygon(points);
    CMTL::io::write_obj(polygon, "test1_input.obj");
    std::vector<std::array<unsigned int, 3>> clip_triangles;
    CMTL::geometry_algorithm::triangulate_2d(polygon, clip_triangles);
    CMTL::io::write_obj(CMTL::geo2d::PolygonSoup<double>(points, clip_triangles), "test1_output.obj");
    std::cout << "test1 : " << std::endl;
    for(unsigned i = 0; i < clip_triangles.size(); ++i)
    {
        std::cout << clip_triangles[i][0] << " " << clip_triangles[i][1] << " " << clip_triangles[i][2] << " " << std::endl;
    }
}

void test2()
{
    std::vector<CMTL::geo2d::Point<double>> points;
    points.push_back(CMTL::geo2d::Point<double>{0,0});
    points.push_back(CMTL::geo2d::Point<double>{1,0});
    points.push_back(CMTL::geo2d::Point<double>{2,0});
    points.push_back(CMTL::geo2d::Point<double>{0,1});
    CMTL::geo2d::Polygon<double> polygon(points);
    std::vector<std::array<unsigned int, 3>> clip_triangles;
    CMTL::geometry_algorithm::triangulate_2d(polygon, clip_triangles);
    std::cout << "test2 : " << std::endl;
    for(unsigned i = 0; i < clip_triangles.size(); ++i)
    {
        std::cout << clip_triangles[i][0] << " " << clip_triangles[i][1] << " " << clip_triangles[i][2] << " " << std::endl;
    }
}

void test3()
{
    std::vector<CMTL::geo2d::Point<double>> points;
    points.push_back(CMTL::geo2d::Point<double>{0,0});
    points.push_back(CMTL::geo2d::Point<double>{1,0});
    points.push_back(CMTL::geo2d::Point<double>{0.3,0.3});
    points.push_back(CMTL::geo2d::Point<double>{0,1});
    std::vector<std::array<unsigned int, 3>> clip_triangles;
    CMTL::geometry_algorithm::triangulate_2d(points, clip_triangles);
    std::cout << "test3 : " << std::endl;
    for(unsigned i = 0; i < clip_triangles.size(); ++i)
    {
        std::cout << clip_triangles[i][0] << " " << clip_triangles[i][1] << " " << clip_triangles[i][2] << " " << std::endl;
    }
}

void test4()
{
    std::vector<CMTL::geo3d::Point<double>> points;
    points.push_back(CMTL::geo3d::Point<double>{0,0,0});
    points.push_back(CMTL::geo3d::Point<double>{1,0,1});
    points.push_back(CMTL::geo3d::Point<double>{0.3,0.5,0.3});
    points.push_back(CMTL::geo3d::Point<double>{1,1,1});
    points.push_back(CMTL::geo3d::Point<double>{0,1,0});
    CMTL::geo3d::Polygon<double> polygon(points);
    std::vector<std::array<unsigned int, 3>> clip_triangles;
    CMTL::geometry_algorithm::triangulate_3d(polygon, clip_triangles);
    std::cout << "test4 : " << std::endl;
    for(unsigned i = 0; i < clip_triangles.size(); ++i)
    {
        std::cout << clip_triangles[i][0] << " " << clip_triangles[i][1] << " " << clip_triangles[i][2] << " " << std::endl;
    }
}

void test5()
{
    std::vector<CMTL::geo3d::Point<double>> points;
    points.push_back(CMTL::geo3d::Point<double>{0,0,0});
    points.push_back(CMTL::geo3d::Point<double>{1,0,1});
    points.push_back(CMTL::geo3d::Point<double>{0.3,0.5,0.3});
    points.push_back(CMTL::geo3d::Point<double>{1,1,1});
    points.push_back(CMTL::geo3d::Point<double>{0,1,0});
    std::vector<std::array<unsigned int, 3>> clip_triangles;
    CMTL::geometry_algorithm::triangulate_3d<double>(points, clip_triangles);
    std::cout << "test5 : " << std::endl;
    for(unsigned i = 0; i < clip_triangles.size(); ++i)
    {
        std::cout << clip_triangles[i][0] << " " << clip_triangles[i][1] << " " << clip_triangles[i][2] << " " << std::endl;
    }
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
}