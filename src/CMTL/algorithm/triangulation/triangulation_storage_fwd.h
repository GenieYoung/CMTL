#ifndef CMTL_TRIANGULATION_STORAGE_FWD_H
#define CMTL_TRIANGULATION_STORAGE_FWD_H

#include <string>

namespace CMTL {
namespace algorithm {
namespace Internal {

template <class T>
class TriangulationStorage;

}  // namespace Internal
}  // namespace algorithm

namespace io {
template <typename T>
void write_obj(
    const algorithm::Internal::TriangulationStorage<T>& triangulation,
    const std::string& file);
}

}  // namespace CMTL

#endif  // CMTL_TRIANGULATION_STORAGE_FWD_H