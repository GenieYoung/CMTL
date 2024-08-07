#ifndef __io_surface_mesh_read_obj__
#define __io_surface_mesh_read_obj__

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

template<typename T>
bool read_obj(geo3d::SurfaceMesh<T>& sm, std::istream& in)
{
    sm.clear();

    typedef typename geo3d::SurfaceMesh<T>::VertexHandle VertexHandle;
    typedef typename geo3d::SurfaceMesh<T>::Point        Point;

    std::vector<VertexHandle> vhandles;
    std::vector<VertexHandle> fvhs;
    T x, y, z;

    std::string line;
    std::string key;
    std::stringstream stream;
    while(in && !in.eof())
    {
        std::getline(in, line);
        if(in.bad())
        {
            std::cerr << "error while reading obj line." << std::endl;
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
            if(stream.bad() || stream.fail())
            {
                std::cerr << "error while reading obj vertex." << std::endl;
                return false;
            }
            vhandles.push_back(sm.add_vertex(Point(x, y, z)));
        }
        else if(key == "f")
        {
            int vid;
            fvhs.clear();
            while(stream >> vid)
            {
                if(vid > static_cast<int>(vhandles.size()) || vid == 0)
                {
                    std::cerr << "error while reading obj face." << std::endl;
                    return false;
                }
                if(vid < 0)
                    fvhs.push_back(vhandles[static_cast<int>(vhandles.size()) + vid]);
                else
                    fvhs.push_back(vhandles[vid-1]);

                // we only read vertex in "v/vt/vn" format
                stream.ignore(256, ' ');
            }
            if(stream.bad())
            {
                std::cerr << "error while reading obj face." << std::endl;
                return false;
            }
            sm.add_face(fvhs);
        }
        else if(key == "vt")
        {
            // TODO
        }
        else if(key == "vn")
        {
            // TODO
        }
    }
    
    return !in.fail();
}

/**
 * @brief build a surface mesh form .obj format file
 * @param sm surface mesh
 * @param file target .obj file position
 * @return true if sucessfully import, otherwise false
 */
template<typename T>
bool read_obj(geo3d::SurfaceMesh<T>& sm, const std::string& file)
{
    std::fstream in(file.c_str(), std::ios_base::in);
    
    if(!in.is_open() || !in.good())
    {
        std::cerr << "error while opening file " << file << std::endl;
        return false;
    }
    
    bool result = read_obj(sm, in);
    in.close();

    return result;
}

}   // namespace io
}   // namespace geometry
}   // namespace CMTL

#endif  // __io_surface_mesh_read_obj__