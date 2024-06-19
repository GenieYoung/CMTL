#ifndef __io_import_obj__
#define __io_import_obj__

#include "common/number_utils.h"
#include "geo3d/geo3d_surface_mesh.h"
#include <fstream>

namespace CMTL{
namespace geometry{
namespace io{

/**
 * @brief trim both leading and trailing spaces
 */
inline void trim_line_string(std::string& str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end   = str.find_last_not_of(" \t\r\n");
    
    if((std::string::npos == start ) || (std::string::npos == end))
        str = "";
    else
        str = str.substr( start, end-start+1 );
}

/**
 * @brief build a surface mesh form .obj format file
 * @param sm surface mesh
 * @param file target .obj file position
 * @return true if sucessfully import, otherwise false
 */
template<typename T>
bool import_obj(geo3d::SurfaceMesh<T>& sm, const std::string& file)
{
    std::fstream in(file.c_str(), std::ios_base::in);
    
    if(!in.is_open() || !in.good())
    {
        std::cerr << "can not open file " << file << std::endl;
        return false;
    }

    typedef typename geo3d::SurfaceMesh<T>::VertexHandle VertexHandle;
    typedef typename geo3d::SurfaceMesh<T>::Point        Point;

    geo3d::SurfaceMesh<T> result;
    std::vector<VertexHandle> vhandles;
    float x, y, z;

    std::string line;
    std::string key;
    std::stringstream stream;
    while(in && !in.eof())
    {
        std::getline(in, line);
        if(in.bad())
        {
            std::cerr << "read obj failed" << std::endl;
            return false;
        }

        trim_line_string(line);

        if(line.empty() || line[0] == '#' || isspace(line[0]))
            continue;

        stream.str(line);
        stream.clear();
        stream >> key;
        
        if(key == "v")
        {
            stream >> x; stream >> y; stream >> z;
            if(!stream.fail())
                vhandles.push_back(result.add_vertex(Point(x, y, z)));
        }
        else if(key == "f")
        {

        }
    }

    return true;
}

}   // namespace io
}   // namespace geometry
}   // namespace CMTL

#endif  // __io_export_obj__