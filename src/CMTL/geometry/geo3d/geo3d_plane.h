#ifndef __geo3d_plane_h__
#define __geo3d_plane_h__

#include "geo3d_point.h"
#include <vector>

namespace CMTL  {
namespace geometry{
namespace geo3d {

/**
 * @brief 3 dimension infinite plane
 * @tparam T value type of point coordinate 
 * @note suggest use exact number type to avoid numerical error
*/
template<typename T>
class Plane
{
    public:
        /**
         * @brief number type
         */
        typedef T NT;

    private:

};

}   // namespace geo3d
}   // namespace geometry
}   // namespace CMTL

#endif // __geo3d_plane_h__