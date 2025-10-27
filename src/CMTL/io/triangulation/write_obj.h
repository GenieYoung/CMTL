#ifndef __io_triangulation_write_obj__
#define __io_triangulation_write_obj__

#include "../../algorithm/triangulation.h"

#include <fstream>

namespace CMTL {
namespace io {

template <typename T>
void write_obj(
    const CMTL::algorithm::Internal::TriangulationStorage<T>& triangulation,
    const std::string& file) {
  std::ofstream fout;
  fout.open(file.c_str(), std::ofstream::trunc);

  std::vector<unsigned> perm(triangulation._vertices.size());
  for (unsigned i = 0; i < triangulation._vertices.size(); ++i) {
    perm[triangulation._vertices[i]->idx] = i;
  }

  for (unsigned i = 0; i < perm.size(); ++i) {
    const auto& p = triangulation._vertices[perm[i]]->crd;
    fout << "v " << std::setprecision(15) << p[0] << " \t" << p[1] << " \t "
         << 0 << '\n';
  }
  fout << std::endl;

  for (unsigned i = 0; i < triangulation._triangles.size(); ++i) {
    const auto& tri = triangulation._triangles[i];
    if (tri->is_dummy()) continue;
    fout << "f " << tri->vrt[0]->idx + 1 << " " << tri->vrt[1]->idx + 1 << " "
         << tri->vrt[2]->idx + 1 << std::endl;
  }
  fout.close();
}

}  // namespace io
}  // namespace CMTL

#endif  // __io_triangulation_write_obj__