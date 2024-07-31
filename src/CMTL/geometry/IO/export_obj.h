#ifndef __io_export_obj__
#define __io_export_obj__

#include "common/number_utils.h"
#include "geo2d/geo2d_polygon.h"
#include "geo3d/geo3d_polygon.h"
#include "geo3d/geo3d_surface_mesh.h"
#include <fstream>

namespace CMTL{
namespace geometry{
namespace io{

/**
 * @brief export a 2d polygon into .obj format
 * @param poly 2d simple polygon
 * @param file target .obj file position
 */
template<typename T>
void export_obj(const geo2d::Polygon<T>& poly, const std::string& file)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(unsigned i = 0; i < poly.size(); ++i)
    {
        const geo2d::Point<T>& p = poly[i];
        fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t" << to_double(p[1]) << " \t " << 0 << '\n';
    }
    fout << std::endl;

    fout << "f";
    for(unsigned i = 0; i < poly.size(); ++i)
        fout << " " << i + 1;

    fout.close();
}

/**
 * @brief export a 3d polygon into .obj format
 * @param poly 3d simple polygon
 * @param file target .obj file position
 */
template<typename T>
void export_obj(const geo3d::Polygon<T>& poly, const std::string& file)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(unsigned i = 0; i < poly.size(); ++i)
    {
        const geo3d::Point<T>& p = poly[i];
        fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t" << to_double(p[1]) << " \t " << to_double(p[2]) << '\n';
    }
    fout << std::endl;

    fout << "f";
    for(unsigned i = 0; i < poly.size(); ++i)
        fout << " " << i + 1;

    fout.close();
}

/**
 * @brief export a surface mesh into .obj format
 * @param sm surface mesh
 * @param file target .obj file position
 */
template<typename T>
void export_obj(const geo3d::SurfaceMesh<T>& sm, const std::string& file)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(auto vit = sm.vertices_begin(); vit != sm.vertices_end(); ++vit)
    {
        const typename geo3d::SurfaceMesh<T>::Point& p = sm.point(*vit);
        fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t" << to_double(p[1]) << " \t " << to_double(p[2]) << '\n';
    }
    fout << std::endl;

    for(auto fit = sm.faces_begin(); fit != sm.faces_end(); ++fit)
    {
        fout << "f";
        for(auto fv = sm.fv_begin(*fit); fv != sm.fv_end(*fit); ++fv)
        {
            fout << " " << fv->idx() + 1;
        }
        fout << std::endl;
    }
    fout.close();
}

}   // namespace io
}   // namespace geometry
}   // namespace CMTL

#endif  // __io_export_obj__