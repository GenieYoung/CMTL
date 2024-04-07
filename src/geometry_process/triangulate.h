#ifndef __geometry_process_triangulate__
#define __geometry_process_triangulate__

#include "geo2d/geo2d_polygon.h"
#include "area.h"
#include "orient.h"

#include <vector>
#include <array>

namespace CMTL  {

namespace geometry_process  {

namespace internal  {

    template<typename Polygon>
    class triangulate_polygon_modifier_2d
    {
        public:
            triangulate_polygon_modifier_2d(const Polygon& polygon)
                : _polygon(polygon)
            {
            }
        
        private:
            struct vertex
            {
                unsigned prev_id, next_id, cur_id;
                bool is_convex, is_reflex, is_ear=false;
            };

        public:
            bool execute(std::vector<std::array<unsigned, 3>>& triangles)
            {
                unsigned n_points = _polygon.size();
                if(n_points < 3)
                    return false;
                if(n_points == 3)
                {
                    triangles = std::vector<std::array<unsigned, 3>>{std::array<unsigned, 3>{0, 1, 2}};
                    return true;
                }
                _vertex_list.resize(n_points);
                for(int i = 0, j = n_points-1, k = 1; i < n_points; ++i, ++j, ++k, j%=n_points, k%=n_points)
                {
                    vertex v;
                    v.prev_id = j;
                    v.next_id = k;
                    v.cur_id = i;
                    int orientation = orient2d(_polygon[j], _polygon[i], _polygon[k]);
                    v.is_convex = (orientation == 1);
                    v.is_reflex = (orientation == -1);
                    _vertex_list[i] = v;
                }
                for(unsigned i = 0; i < n_points; ++i)
                {
                    if(_vertex_list[i].is_convex)
                        _vertex_list[i].is_ear = check_ear(_vertex_list[i]);
                }
                unsigned begin_id = 0;
                unsigned iter_times = 0;
                triangles.reserve(n_points - 2);
                while(_vertex_list[_vertex_list[begin_id].next_id].next_id != _vertex_list[begin_id].prev_id)
                {
                    unsigned first_ear = begin_id;
                    unsigned iter_times_inner = 0;
                    while(!_vertex_list[first_ear].is_ear)
                    {
                        first_ear = _vertex_list[first_ear].next_id;
                        if(++iter_times_inner > _vertex_list.size())
                            return false;
                    }
                    triangles.push_back(std::array<unsigned, 3>{_vertex_list[first_ear].prev_id, first_ear, _vertex_list[first_ear].next_id});
                    _vertex_list[_vertex_list[first_ear].prev_id].next_id = _vertex_list[first_ear].next_id;
                    _vertex_list[_vertex_list[first_ear].next_id].prev_id = _vertex_list[first_ear].prev_id;
                    re_configure(_vertex_list[_vertex_list[first_ear].prev_id]);
                    re_configure(_vertex_list[_vertex_list[first_ear].next_id]);
                    begin_id = _vertex_list[first_ear].next_id;
                    if(++iter_times > _vertex_list.size())
                        return false;
                }
                triangles.push_back(std::array<unsigned, 3>{_vertex_list[begin_id].prev_id, begin_id, _vertex_list[begin_id].next_id});
                return true;
            }

        private:
            void re_configure(vertex& v)
            {
                if(v.is_convex || v.is_ear)
                {
                    v.is_ear = check_ear(v);
                    return;
                }
                if(v.is_reflex)
                {
                    int orientation = orient2d(_polygon[v.prev_id], _polygon[v.cur_id], _polygon[v.next_id]);
                    v.is_convex = (orientation == 1);
                    v.is_reflex = (orientation == -1);
                    if(v.is_convex)
                        v.is_ear = check_ear(v);
                }

            }

            bool check_ear(const vertex& v) const
            {
                unsigned loc = _vertex_list[v.next_id].next_id;
                while(loc != v.prev_id)
                {
                    if(_vertex_list[loc].is_convex)
                    {
                        loc = _vertex_list[loc].next_id;
                        continue;
                    }
                    if(orient2d(_polygon[v.prev_id], _polygon[v.next_id], _polygon[loc]) != 1)
                        return false;
                    loc = _vertex_list[loc].next_id;
                }
                return true;
            }
        
        private:
            const Polygon& _polygon;
            std::vector<vertex> _vertex_list;
    };

}   // namespace internal

/**
 * @brief triangulate a single counterclock-wise 2d-polygon into several triangles using ear-clipping
 * @return true if the polygon be trianguled successfully.
 * @note the polygon should be intersect-free. 
 *       polygon struct should have [] operator to get the point and the size() method to get the length;
 *       the point struct should have [] opeartor to get the coordinate.
*/
template<typename Polygon>
bool triangulate_2d(const Polygon& polygon, std::vector<std::array<unsigned, 3>>& triangles)
{
    internal::triangulate_polygon_modifier_2d<Polygon> modifier(polygon);
    return modifier.execute(triangles);
}

}   // namespace geometry_process
}   // namespace CMTL

#endif  // __geometry_process_triangulate__