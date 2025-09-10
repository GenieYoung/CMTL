#ifndef __io_polyline_write_obj__
#define __io_polyline_write_obj__

#include "../../common/numeric_utils.h"

#include <fstream>
#include <vector>

namespace CMTL {
namespace io {

template <typename Point>
void write_obj(const std::vector<std::pair<Point, Point>>& edges,
               const std::string& file) {
  std::ofstream fout;
  fout.open(file.c_str(), std::ofstream::trunc);

  for (size_t i = 0; i < edges.size(); ++i) {
    for (const Point& p : {edges[i].first, edges[i].second}) {
      if (p.size() == 2)
        fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t"
             << to_double(p[1]) << " \t " << 0 << '\n';
      else
        fout << "v " << std::setprecision(15) << to_double(p[0]) << " \t"
             << to_double(p[1]) << " \t " << to_double(p[2]) << '\n';
    }
  }

  for (size_t i = 0; i < edges.size(); ++i)
    fout << "l " << 2 * i + 1 << " " << 2 * i + 2 << std::endl;

  fout.close();
}

}  // namespace io
}  // namespace CMTL

#endif  // __io_polyline_write_obj__