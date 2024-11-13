#ifndef __io_surface_mesh_write_obj__
#define __io_surface_mesh_write_obj__

#include "../../geo2d/geo2d_surface_mesh.h"
#include "../../geo3d/geo3d_surface_mesh.h"
#include <fstream>

namespace CMTL{
namespace geometry{
namespace io{

/**
 * @brief export a 2d surface mesh into .obj format
 * @param sm surface mesh
 * @param exact if exact is true, we print point into rational format
 * @param file target .obj file position
 */
template<typename T>
void write_obj(const geo2d::SurfaceMesh<T>& sm, const std::string& file, bool exact = false)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(auto vit = sm.vertices_begin(); vit != sm.vertices_end(); ++vit)
    {
        const typename geo2d::SurfaceMesh<T>::Point& p = sm.point(*vit);
        if(!exact)
            fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t" << to_double(p[1]) << " \t " << 0 << '\n';
        else
            fout << "v " << to_string(p[0]) << " \t" << to_string(p[1]) << " \t " << 0 << '\n';
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

/**
 * @brief export a 3d surface mesh into .obj format
 * @param sm surface mesh
 * @param exact if exact is true, we print point into rational format
 * @param file target .obj file position
 */
template<typename T>
void write_obj(const geo3d::SurfaceMesh<T>& sm, const std::string& file, bool exact = false)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(auto vit = sm.vertices_begin(); vit != sm.vertices_end(); ++vit)
    {
        const typename geo3d::SurfaceMesh<T>::Point& p = sm.point(*vit);
        if(!exact)
            fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t" << to_double(p[1]) << " \t " << to_double(p[2]) << '\n';
        else
            fout << "v " << to_string(p[0]) << " \t" << to_string(p[1]) << " \t " << to_string(p[2]) << '\n';
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

#endif  // __io_surface_mesh_write_obj__