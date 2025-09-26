#ifndef __geo2d_pslg_h__
#define __geo2d_pslg_h__

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
};

}  // namespace geo2d
}  // namespace CMTL

#endif  // __geo2d_pslg_h__