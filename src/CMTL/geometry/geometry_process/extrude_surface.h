#ifndef __geometry_process_extrude_surface__
#define __geometry_process_extrude_surface__

#include "geo3d/geo3d_surface_mesh.h"
#include "geo3d/geo3d_polygon_soup.h"
#include "normal.h"

#include <algorithm>

namespace CMTL{
namespace geometry{
namespace geometry_process{

namespace internal{

    template<typename T>
    class surface_extrude_modifier
    {
        public:
            surface_extrude_modifier(const geo3d::SurfaceMesh<T>& input_mesh, const T& shift)
                : _origin_mesh(input_mesh), _shift(shift)
            {
                assert(_origin_mesh.is_triangle_mesh());
            }

            ~surface_extrude_modifier()
            {
                // for(unsigned i = 0; i < _fv_upper_bottom_offset.size(); ++i)
                // {
                //     for(auto it = _fv_upper_bottom_offset[i].begin(); it != _fv_upper_bottom_offset[i].end(); ++it)
                //     {
                //         if(it->second.first)
                //         {
                //             delete it->second.first;
                //             it->second.first = nullptr;
                //         }
                //         if(it->second.second)
                //         {
                //             delete it->second.second;
                //             it->second.second = nullptr;
                //         }
                //     }
                // }
            }

        public:
            bool execute(geo3d::SurfaceMesh<T>& result_mesh)
            {
                result_mesh.clear();
                
                _fv_upper_bottom_offset.resize(_origin_mesh.n_faces());
                std::vector<geo3d::Point<T>> normals(_origin_mesh.n_faces());
                for(auto f_it = _origin_mesh.faces_begin(); f_it != _origin_mesh.faces_end(); ++f_it)
                {
                    geo3d::Point<T> face_normal = normalize_3d(_origin_mesh.normal(*f_it));
                    normals[f_it->idx()] = face_normal;
                    for(auto fv_it = _origin_mesh.fv_begin(*f_it); fv_it != _origin_mesh.fv_end(*f_it); ++fv_it)
                    {
                        _fv_upper_bottom_offset[f_it->idx()][fv_it->idx()].first = geo3d::Point<T>(_origin_mesh.point(*fv_it) + face_normal * _shift);
                        _fv_upper_bottom_offset[f_it->idx()][fv_it->idx()].second = geo3d::Point<T>(_origin_mesh.point(*fv_it) - face_normal * _shift);
                    }
                }

                std::vector<std::vector<geo3d::Point<T>>> extrude_faces;
                // offset faces
                for(auto f_it = _origin_mesh.faces_begin(); f_it != _origin_mesh.faces_end(); ++f_it)
                {
                    std::vector<geo3d::Point<T>> upper_face;
                    std::vector<geo3d::Point<T>> bottom_face;
                    for(auto fv_it = _origin_mesh.fv_begin(*f_it); fv_it != _origin_mesh.fv_end(*f_it); ++fv_it)
                    {
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& upper_bottom_points = _fv_upper_bottom_offset[f_it->idx()][fv_it->idx()];
                        upper_face.push_back(upper_bottom_points.first);
                        bottom_face.push_back(upper_bottom_points.second);
                    }
                    std::reverse(bottom_face.begin(), bottom_face.end());
                    extrude_faces.push_back(upper_face);
                    extrude_faces.push_back(bottom_face);
                }
                // offset edges
                for(auto e_it = _origin_mesh.edges_begin(); e_it != _origin_mesh.edges_end(); ++e_it)
                {
                    if(!_origin_mesh.is_boundary(*e_it))
                    {
                        unsigned f0 = _origin_mesh.face_handle(_origin_mesh.halfedge_handle(*e_it, 0)).idx();
                        unsigned f1 = _origin_mesh.face_handle(_origin_mesh.halfedge_handle(*e_it, 1)).idx();
                        unsigned v0 = _origin_mesh.from_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0)).idx();
                        unsigned v1 = _origin_mesh.to_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0)).idx();
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v00_upper_bottom_points = _fv_upper_bottom_offset[f0][v0];
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v01_upper_bottom_points = _fv_upper_bottom_offset[f0][v1];
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v11_upper_bottom_points = _fv_upper_bottom_offset[f1][v1];
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v10_upper_bottom_points = _fv_upper_bottom_offset[f1][v0];
                        std::vector<geo3d::Point<T>> upper_face = {v00_upper_bottom_points.first, v10_upper_bottom_points.first, 
                                                                   v11_upper_bottom_points.first, v01_upper_bottom_points.first};
                        std::vector<geo3d::Point<T>> bottom_face = {v00_upper_bottom_points.second, v01_upper_bottom_points.second, 
                                                                    v11_upper_bottom_points.second, v10_upper_bottom_points.second};
                        extrude_faces.push_back(upper_face);
                        extrude_faces.push_back(bottom_face);
                    }
                    else
                    {
                        typename geo3d::SurfaceMesh<T>::FaceHandle fh;
                        typename geo3d::SurfaceMesh<T>::VertexHandle vh0, vh1;
                        if(_origin_mesh.is_boundary(_origin_mesh.halfedge_handle(*e_it, 0)))
                        {
                            fh = _origin_mesh.face_handle(_origin_mesh.halfedge_handle(*e_it, 1));
                            vh0 = _origin_mesh.from_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 1));
                            vh1 = _origin_mesh.to_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 1));
                        }
                        else
                        {
                            fh = _origin_mesh.face_handle(_origin_mesh.halfedge_handle(*e_it, 0));
                            vh0 = _origin_mesh.from_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0));
                            vh1 = _origin_mesh.to_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0));
                        }
                        geo3d::Point<T> tangent = normalize_3d(_origin_mesh.point(vh1) - _origin_mesh.point(vh0)) % normals[fh.idx()];
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v0_upper_bottom_points = _fv_upper_bottom_offset[fh.idx()][vh0.idx()];
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v1_upper_bottom_points = _fv_upper_bottom_offset[fh.idx()][vh1.idx()];
                        geo3d::Point<T> extend_v0 = _origin_mesh.point(vh0) + tangent * _shift;
                        geo3d::Point<T> extend_v1 = _origin_mesh.point(vh1) + tangent * _shift;
                        std::vector<geo3d::Point<T>> upper_face = {v1_upper_bottom_points.first, v0_upper_bottom_points.first, 
                                                                   extend_v0, extend_v1};
                        std::vector<geo3d::Point<T>> bottom_face = {v0_upper_bottom_points.second, v1_upper_bottom_points.second, 
                                                                   extend_v1, extend_v0};
                        extrude_faces.push_back(upper_face);
                        extrude_faces.push_back(bottom_face);
                    }
                }
                // offset vertices
                for(auto v_it = _origin_mesh.vertices_begin(); v_it != _origin_mesh.vertices_end(); ++v_it)
                {
                    if(!_origin_mesh.is_boundary(*v_it))
                    {
                        std::vector<geo3d::Point<T>> upper_face;
                        std::vector<geo3d::Point<T>> bottom_face;
                        for(auto vf_it = _origin_mesh.vf_ccwbegin(*v_it); vf_it != _origin_mesh.vf_ccwend(*v_it); ++vf_it)
                        {
                            const std::pair<geo3d::Point<T>, geo3d::Point<T>>& upper_bottom_points = _fv_upper_bottom_offset[vf_it->idx()][v_it->idx()];
                            upper_face.push_back(upper_bottom_points.first);
                            bottom_face.push_back(upper_bottom_points.second);
                        }
                        std::reverse(bottom_face.begin(), bottom_face.end());
                        extrude_faces.push_back(upper_face);
                        extrude_faces.push_back(bottom_face);
                    }
                    else
                    {
                        
                    }
                }
                
                std::map<geo3d::Point<T>, typename geo3d::SurfaceMesh<T>::VertexHandle> unique_points;
                for(unsigned i = 0; i < extrude_faces.size(); ++i)
                {
                    const std::vector<geo3d::Point<T>>& face = extrude_faces[i];
                    std::vector<typename geo3d::SurfaceMesh<T>::VertexHandle> fhs;
                    for(unsigned j = 0; j < face.size(); ++j)
                    {
                        auto find_point = unique_points.find(face[j]);
                        if(find_point != unique_points.end())
                            fhs.push_back(find_point->second);
                        else 
                            fhs.push_back(result_mesh.add_vertex(face[j]));
                    }
                    result_mesh.add_face(fhs);
                }

                return true;

                // for(auto e_it = _origin_mesh.edges_begin(); e_it != _origin_mesh.edges_end(); ++e_it)
                // {
                //     if(_origin_mesh.is_boundary(*e_it))
                //         continue;
                //     unsigned face0 = _origin_mesh.halfedge_handle(*e_it, 0).idx();
                //     unsigned face1 = _origin_mesh.halfedge_handle(*e_it, 1).idx();
                //     unsigned v00 = _origin_mesh.from_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0)).idx();
                //     unsigned v01 = _origin_mesh.to_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0)).idx();
                //     unsigned v10 = _origin_mesh.to_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 1)).idx();
                //     unsigned v11 = _origin_mesh.from_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 1)).idx();
                //     if(normals[face0] * normals[face1] > 0.999)
                //     {
                //         geo3d::Point<T>* p00_upper = _fv_upper_bottom_offset[face0][v00].first;
                //         geo3d::Point<T>* p01_upper = _fv_upper_bottom_offset[face0][v01].first;
                //         geo3d::Point<T>* p00_bottom = _fv_upper_bottom_offset[face0][v00].second;
                //         geo3d::Point<T>* p01_bottom = _fv_upper_bottom_offset[face0][v01].second;
                //         geo3d::Point<T>* p10_upper = _fv_upper_bottom_offset[face1][v10].first;
                //         geo3d::Point<T>* p11_upper = _fv_upper_bottom_offset[face1][v11].first;
                //         geo3d::Point<T>* p10_bottom = _fv_upper_bottom_offset[face1][v10].second;
                //         geo3d::Point<T>* p11_bottom = _fv_upper_bottom_offset[face1][v11].second;
                //         *p01_upper = (*p00_upper + *p01_upper) / T(2.0); p00_upper = p01_upper;
                //         *p01_bottom = (*p00_bottom + *p01_bottom) / T(2.0); p00_bottom = p01_bottom;
                //         *p11_upper = (*p10_upper + *p11_upper) / T(2.0); p10_upper = p11_upper;
                //         *p11_bottom = (*p10_bottom + *p11_bottom) / T(2.0); p10_bottom = p11_bottom;
                //     }
                // }
                // std::vector<std::vector<geo3d::Point<T>*>> extrude_faces;
                // for(auto f_it = _origin_mesh.faces_begin(); f_it != _origin_mesh.faces_end(); ++f_it)
                // {
                //     std::vector<geo3d::Point<T>*> upper_face;
                //     std::vector<geo3d::Point<T>*> bottom_face;
                //     for(auto fv_it = _origin_mesh.fv_begin(*f_it); fv_it != _origin_mesh.fv_end(*f_it); ++fv_it)
                //     {
                //         upper_face.push_back(_fv_upper_bottom_offset[f_it->idx()][fv_it->idx()].first);
                //         bottom_face.push_back(_fv_upper_bottom_offset[f_it->idx()][fv_it->idx()].second);
                //     }
                //     std::reverse(bottom_face.begin(), bottom_face.end());
                //     extrude_faces.push_back(upper_face);
                //     extrude_faces.push_back(bottom_face);
                // }
            }

        private:
            std::vector<std::map<unsigned, std::pair<geo3d::Point<T>, geo3d::Point<T>>>> _fv_upper_bottom_offset;

            std::map<std::pair<unsigned, unsigned>, geo3d::Point<T>> _boundary_edge_vertex_extend;
        
        private:
            const geo3d::SurfaceMesh<T>& _origin_mesh;

            T _shift;
    };

}   // namespace internal

template<typename T>
bool extrude_surface(const geo3d::SurfaceMesh<T>& sm, 
                     const typename geo3d::SurfaceMesh<T>::NT& shift, 
                     geo3d::SurfaceMesh<T>& result)
{
    internal::surface_extrude_modifier<T> modifier(sm, shift);
    return modifier.execute(result);
}

}   // namespace geometry_process
}   // namespace geometry
}   // namespace CMTL

#endif  // __geometry_process_extrude_surface__