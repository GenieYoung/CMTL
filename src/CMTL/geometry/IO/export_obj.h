#ifndef __io_export_obj__
#define __io_export_obj__

#include "common/number_utils.h"
#include "geo3d/geo3d_surface_mesh.h"
#include <fstream>

namespace CMTL{
namespace geometry{
namespace io{

template<class Traits>
void export_obj(const geo3d::SurfaceMesh<Traits>& sm, const std::string& file)
{
    std::ofstream fout;
    fout.open(file.c_str(), std::ofstream::trunc);

    for(auto vit = sm.vertices_begin(); vit != sm.vertices_end(); ++vit)
    {
        const typename Traits::Point& p = sm.point(*vit);
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