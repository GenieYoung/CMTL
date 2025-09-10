#ifndef __io_polygon_write_obj__
#define __io_polygon_write_obj__

#include "../../geo2d/polygon.h"
#include "../../geo3d/polygon.h"

#include <fstream>

namespace CMTL {

/**
 * @brief input/output stream
 */
namespace io {

/**
 * @brief export a 2d polygon into .obj format
 * @param poly 2d simple polygon
 * @param file target .obj file position
 */
template <typename T>
void write_obj(const geo2d::Polygon<T>& poly, const std::string& file) {
  std::ofstream fout;
  fout.open(file.c_str(), std::ofstream::trunc);

  for (unsigned i = 0; i < poly.size(); ++i) {
    const geo2d::Point<T>& p = poly[i];
    fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t"
         << to_double(p[1]) << " \t " << 0 << '\n';
  }
  fout << std::endl;

  fout << "f";
  for (unsigned i = 0; i < poly.size(); ++i) fout << " " << i + 1;

  fout.close();
}

/**
 * @brief export a 3d polygon into .obj format
 * @param poly 3d simple polygon
 * @param file target .obj file position
 */
template <typename T>
void write_obj(const geo3d::Polygon<T>& poly, const std::string& file) {
  std::ofstream fout;
  fout.open(file.c_str(), std::ofstream::trunc);

  for (unsigned i = 0; i < poly.size(); ++i) {
    const geo3d::Point<T>& p = poly[i];
    fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t"
         << to_double(p[1]) << " \t " << to_double(p[2]) << '\n';
  }
  fout << std::endl;

  fout << "f";
  for (unsigned i = 0; i < poly.size(); ++i) fout << " " << i + 1;

  fout.close();
}

}  // namespace io
}  // namespace CMTL

#endif  // __io_polygon_write_obj__