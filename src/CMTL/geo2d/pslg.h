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
  friend class algorithm::Triangulation<T>;

 public:
  PSLG() = default;

  ~PSLG() = default;

 public:
  struct Vertex {
    Point<T> pos;
  };

  struct Segment {
    int v0, v1;
  };

  struct Region {
    Point<T> pos;
  };

  struct Hole {
    Point<T> pos;
  };

 private:
  std::vector<Vertex> _points;
  std::vector<Segment> _segments;
  std::vector<Region> _regions;
  std::vector<Hole> _holes;
};

}  // namespace geo2d
}  // namespace CMTL

#endif  // __geo2d_pslg_h__