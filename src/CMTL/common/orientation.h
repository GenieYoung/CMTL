#ifndef CMTL_ORIENTATION_H
#define CMTL_ORIENTATION_H

#include <ostream>

namespace CMTL {

/**
 * @brief enum used for representing orientation
 */
enum class ORIENTATION {
  POSITIVE = 1,
  INSIDE = 1,
  NEGATIVE = -1,
  OUTSIDE = -1,
  ON = 0,
  COLLINEAR = 0,
  COPLANAR = 0
};

inline std::ostream& operator<<(std::ostream& os, ORIENTATION ori) {
  switch (ori) {
    case ORIENTATION::POSITIVE:
      os << "Positive";
      break;
    case ORIENTATION::NEGATIVE:
      os << "Negative";
      break;
    case ORIENTATION::ON:
      os << "On";
      break;
    default:
      break;
  }
  return os;
}

}  // namespace CMTL

#endif  // CMTL_ORIENTATION_H