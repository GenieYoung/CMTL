#ifndef __geometry_process_extrude_surface__
#define __geometry_process_extrude_surface__

#include "../geo3d/geo3d_surface_mesh.h"
#include "../geo3d/geo3d_polygon_soup.h"
#include "normal.h"

#include <algorithm>
#include <set>

namespace CMTL{
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
            }

        public:
            bool execute(geo3d::SurfaceMesh<T>& result_mesh)
            {
                result_mesh.clear();
                
                std::vector<geo3d::Point<T>> normals(_origin_mesh.n_faces());
                for(auto f_it = _origin_mesh.faces_begin(); f_it != _origin_mesh.faces_end(); ++f_it)
                {
                    normals[f_it->idx()] = normalize_3d(_origin_mesh.normal(*f_it));
                }

                _fv_upper_bottom_offset.resize(_origin_mesh.n_faces());
                auto similar_normal_cmp = [](const geo3d::Point<T>& n0, const geo3d::Point<T>& n1)
                {
                    return (n0 * n1) < 0.995 && n0 < n1;
                };
                for(auto v_it = _origin_mesh.vertices_begin(); v_it != _origin_mesh.vertices_end(); ++v_it)
                {
                    std::set<geo3d::Point<T>, decltype(similar_normal_cmp)> vf_normals(similar_normal_cmp);
                    for(auto vf_it = _origin_mesh.vf_begin(*v_it); vf_it != _origin_mesh.vf_end(*v_it); ++vf_it)
                    {
                        auto find_similar_normal = vf_normals.find(normals[vf_it->idx()]);
                        if(find_similar_normal == vf_normals.end())
                        {
                            vf_normals.insert(normals[vf_it->idx()]);
                            _fv_upper_bottom_offset[vf_it->idx()][v_it->idx()].first  = _origin_mesh.point(*v_it) + normals[vf_it->idx()] * _shift;
                            _fv_upper_bottom_offset[vf_it->idx()][v_it->idx()].second = _origin_mesh.point(*v_it) - normals[vf_it->idx()] * _shift;
                        }
                        else
                        {
                            _fv_upper_bottom_offset[vf_it->idx()][v_it->idx()].first  = _origin_mesh.point(*v_it) + *find_similar_normal * _shift;
                            _fv_upper_bottom_offset[vf_it->idx()][v_it->idx()].second = _origin_mesh.point(*v_it) - *find_similar_normal * _shift;
                        }
                    }
                }

                for(auto v_it = _origin_mesh.vertices_begin(); v_it != _origin_mesh.vertices_end(); ++v_it)
                {
                    if(v_it->is_boundary())
                    {
                        auto next_boundary_edge = v_it->halfedge();
                        auto prev_boundary_edge = v_it->halfedge().prev();
                        assert(next_boundary_edge.is_boundary() && prev_boundary_edge.is_boundary());
                        auto prev_vh = prev_boundary_edge.from_vertex();
                        auto next_vh = next_boundary_edge.to_vertex();
                        auto prev_boundary_face = prev_boundary_edge.opposite().face();
                        auto next_boundary_face = next_boundary_edge.opposite().face();
                        geo3d::Point<T> prev_edge_vec = normalize_3d(_origin_mesh.point(*v_it) - _origin_mesh.point(prev_vh));
                        geo3d::Point<T> next_edge_vec = normalize_3d(_origin_mesh.point(next_vh) - _origin_mesh.point(*v_it));
                        geo3d::Point<T> prev_edge_normal = normals[prev_boundary_face.idx()] % prev_edge_vec;
                        geo3d::Point<T> next_edge_normal = normals[next_boundary_face.idx()] % next_edge_vec;
                        geo3d::Point<T> prev_extend = _origin_mesh.point(*v_it) + prev_edge_normal * _shift;
                        geo3d::Point<T> next_extend = _origin_mesh.point(*v_it) + next_edge_normal * _shift;
                        if(prev_edge_normal * next_edge_normal > 0.99)
                        {
                            if(normals[prev_boundary_face.idx()]%(normals[next_boundary_face.idx()]) == geo3d::Point<T>::Origin)
                            {
                                geo3d::Point<T> middle_extend = (prev_extend + next_extend) / T(2);
                                _boundary_vertex_extend[v_it->idx()] = std::make_pair(middle_extend, middle_extend);
                            }
                            else
                            {
                                geo3d::Point<T> middle_edge_normal = normalize_3d(normals[prev_boundary_face.idx()] % normals[next_boundary_face.idx()]);
                                geo3d::Point<T> middle_extend = _origin_mesh.point(*v_it) + middle_edge_normal * _shift;
                                _boundary_vertex_extend[v_it->idx()] = std::make_pair(middle_extend, middle_extend);
                            }
                        }
                        else
                            _boundary_vertex_extend[v_it->idx()] = std::make_pair(prev_extend, next_extend);
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
                        if(v00_upper_bottom_points.first != v10_upper_bottom_points.first)
                        {
                            assert(v01_upper_bottom_points.first != v11_upper_bottom_points.first);
                            assert(v00_upper_bottom_points.second != v10_upper_bottom_points.second);
                            assert(v01_upper_bottom_points.second != v11_upper_bottom_points.second);
                            std::vector<geo3d::Point<T>> upper_face = {v00_upper_bottom_points.first, v10_upper_bottom_points.first, 
                                                                       v11_upper_bottom_points.first, v01_upper_bottom_points.first};
                            std::vector<geo3d::Point<T>> bottom_face = {v00_upper_bottom_points.second, v01_upper_bottom_points.second, 
                                                                        v11_upper_bottom_points.second, v10_upper_bottom_points.second};
                            extrude_faces.push_back(upper_face);
                            extrude_faces.push_back(bottom_face);
                        }
                    }
                    else
                    {
                        typename geo3d::SurfaceMesh<T>::FaceHandle fh;
                        typename geo3d::SurfaceMesh<T>::VertexHandle vh0, vh1;
                        if(_origin_mesh.is_boundary(_origin_mesh.halfedge_handle(*e_it, 0)))
                        {
                            fh = _origin_mesh.face_handle(_origin_mesh.halfedge_handle(*e_it, 1));
                            vh0 = _origin_mesh.from_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0));
                            vh1 = _origin_mesh.to_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 0));
                        }
                        else
                        {
                            fh = _origin_mesh.face_handle(_origin_mesh.halfedge_handle(*e_it, 0));
                            vh0 = _origin_mesh.from_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 1));
                            vh1 = _origin_mesh.to_vertex_handle(_origin_mesh.halfedge_handle(*e_it, 1));
                        }
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v0_upper_bottom_points = _fv_upper_bottom_offset[fh.idx()][vh0.idx()];
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& v1_upper_bottom_points = _fv_upper_bottom_offset[fh.idx()][vh1.idx()];
                        geo3d::Point<T> extend_v0 = _boundary_vertex_extend[vh0.idx()].second;
                        geo3d::Point<T> extend_v1 = _boundary_vertex_extend[vh1.idx()].first;
                        std::vector<geo3d::Point<T>> upper_face = {v0_upper_bottom_points.first, v1_upper_bottom_points.first, 
                                                                   extend_v1, extend_v0};
                        std::vector<geo3d::Point<T>> bottom_face = {v1_upper_bottom_points.second, v0_upper_bottom_points.second, 
                                                                   extend_v0, extend_v1};
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
                            if(upper_face.empty() || upper_bottom_points.first != upper_face.back())
                                upper_face.push_back(upper_bottom_points.first);
                            if(bottom_face.empty() || upper_bottom_points.second != bottom_face.back())
                                bottom_face.push_back(upper_bottom_points.second);
                        }
                        for(unsigned i = 1, j = 2; j < upper_face.size(); ++i, ++j)
                        {
                            if(upper_face[0] != upper_face[i] && upper_face[0] != upper_face[j])
                            {
                                extrude_faces.push_back(std::vector<geo3d::Point<T>>{upper_face[0], upper_face[i], upper_face[j]});
                                extrude_faces.push_back(std::vector<geo3d::Point<T>>{bottom_face[0], bottom_face[j], bottom_face[i]});
                            }
                        }
                    }
                    else
                    {
                        const std::pair<geo3d::Point<T>, geo3d::Point<T>>& prev_next_extend = _boundary_vertex_extend[v_it->idx()];
                        std::vector<geo3d::Point<T>> upper_face;
                        if(prev_next_extend.first != prev_next_extend.second)
                            upper_face = {prev_next_extend.second, prev_next_extend.first};
                        else
                            upper_face = {prev_next_extend.second};
                        std::vector<geo3d::Point<T>> bottom_face = upper_face;
                        for(auto vf_it = _origin_mesh.vf_ccwbegin(*v_it); vf_it != _origin_mesh.vf_ccwend(*v_it); ++vf_it)
                        {
                            const std::pair<geo3d::Point<T>, geo3d::Point<T>>& upper_bottom_points = _fv_upper_bottom_offset[vf_it->idx()][v_it->idx()];
                            if(upper_bottom_points.first != upper_face.back())
                                upper_face.push_back(upper_bottom_points.first);
                            if(upper_bottom_points.second != bottom_face.back())
                                bottom_face.push_back(upper_bottom_points.second);
                        }
                        for(unsigned i = 1, j = 2; j < upper_face.size(); ++i, ++j)
                        {
                            if(upper_face[0] != upper_face[i] && upper_face[0] != upper_face[j])
                            {
                                extrude_faces.push_back(std::vector<geo3d::Point<T>>{upper_face[0], upper_face[i], upper_face[j]});
                                extrude_faces.push_back(std::vector<geo3d::Point<T>>{bottom_face[0], bottom_face[j], bottom_face[i]});
                            }
                        }
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
                        {
                            fhs.push_back(find_point->second);
                        }
                        else 
                        {
                            fhs.push_back(result_mesh.add_vertex(face[j]));
                            unique_points.insert({face[j], fhs.back()});
                        }
                    }
                    result_mesh.add_face(fhs);
                }

                return true;
            }

        private:
            std::vector<std::map<unsigned, std::pair<geo3d::Point<T>, geo3d::Point<T>>>> _fv_upper_bottom_offset;

            std::map<unsigned, std::pair<geo3d::Point<T>, geo3d::Point<T>>> _boundary_vertex_extend;
        
        private:
            const geo3d::SurfaceMesh<T>& _origin_mesh;

            T _shift;
    };

}   // namespace internal

template<typename T>
bool extrude_surface(const geo3d::SurfaceMesh<T>& sm, 
                     const typename geo3d::SurfaceMesh<T>::FT& shift, 
                     geo3d::SurfaceMesh<T>& result)
{
    internal::surface_extrude_modifier<T> modifier(sm, shift);
    return modifier.execute(result);
}

}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_extrude_surface__