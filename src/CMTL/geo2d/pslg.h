#ifndef CMTL_GEO2D_PSLG_H
#define CMTL_GEO2D_PSLG_H

#include "point.h"

#include <vector>

namespace CMTL {
namespace geo2d {

/**
 * @brief planar straight line graph used for triangulation
 * @tparam T number type of point coordinate
 */
template <typename T>
class PSLG {
 public:
  PSLG() = default;
  std::vector<geo2d::Point<T>> _points;
  std::vector<std::pair<unsigned, unsigned>> _segments;
  std::vector<int> _segmentmarks;
};

}  // namespace geo2d
}  // namespace CMTL

#endif  // CMTL_GEO2D_PSLG_H