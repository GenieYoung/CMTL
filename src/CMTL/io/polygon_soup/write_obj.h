#ifndef __io_polygon_soup_write_obj__
#define __io_polygon_soup_write_obj__

#include "../../geo2d/geo2d_polygon_soup.h"
#include "../../geo3d/geo3d_polygon_soup.h"
#include <fstream>

namespace CMTL{
namespace io{

/**
 * @brief export a 2d polygon soup into .obj format
 * @param poly 2d simple polygon soup
 * @param file target .obj file position
 */
template<typename T>
void write_obj(const geo2d::PolygonSoup<T>& poly, const std::string& file)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(unsigned i = 0; i < poly.n_points(); ++i)
    {
        const geo2d::Point<T>& p = poly.point(i);
        fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t" << to_double(p[1]) << " \t " << 0 << '\n';
    }
    fout << std::endl;

    for(unsigned i = 0; i < poly.n_polygons(); ++i)
    {
        const std::vector<unsigned>& polygon = poly.polygon(i);
        if(polygon.empty()) continue;
        fout << "f";
        for(unsigned j = 0; j < polygon.size(); ++j)
        {
            fout << " " << polygon[j] + 1;
        }
        fout << std::endl;
    }

    fout.close();
}

/**
 * @brief export a 3d polygon soup into .obj format
 * @param poly 3d simple polygon soup
 * @param file target .obj file position
 */
template<typename T>
void write_obj(const geo3d::PolygonSoup<T>& poly, const std::string& file)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(unsigned i = 0; i < poly.n_points(); ++i)
    {
        const geo3d::Point<T>& p = poly.point(i);
        fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t" << to_double(p[1]) << " \t " << to_double(p[2]) << '\n';
    }
    fout << std::endl;

    for(unsigned i = 0; i < poly.n_polygons(); ++i)
    {
        const std::vector<unsigned>& polygon = poly.polygon(i);
        if(polygon.empty()) continue;
        fout << "f";
        for(unsigned j = 0; j < polygon.size(); ++j)
        {
            fout << " " << polygon[j] + 1;
        }
        fout << std::endl;
    }

    fout.close();
}

}   // namespace io
}   // namespace CMTL

#endif  // __io_polygon_soup_write_obj__