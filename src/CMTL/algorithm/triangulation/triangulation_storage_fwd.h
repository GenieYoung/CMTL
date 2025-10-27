#ifndef __algorithm_triangulation_storage_fwd_h__
#define __algorithm_triangulation_storage_fwd_h__

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

#endif  // __algorithm_triangulation_storage_fwd_h__