#ifndef __geo2d_triangulation_h__
#define __geo2d_triangulation_h__

#include <unordered_map>
#include <set>
#include <vector>
#include <stack>

#include "../algorithm/predicate.h"

namespace CMTL{
namespace algorithm{

// #define Trianglulation_Ghost_Idx INT_MAX

// class TriangulationStorage
// {
//     public:
//         TriangulationStorage() = default;

//         ~TriangulationStorage() = default;

//     protected:
//         struct Triangle;

//         struct Edge
//         {
//             Triangle* tri;
//             unsigned char i;
//         };

//         struct Triangle
//         {
//             Triangle(int u, int v, int w);
//             int vrt[3];
//             bool ghost;
//             bool deleted;
//         };

//         struct TriangleList
//         {
//             std::vector<Triangle> _triangles;
//             std::stack<Triangle> _dead_triangles;
//         };

//     public:
//         /**
//          * @brief add a positively oriented triangle uvw
//          */
//         void add_triangle(int u, int v, int w);

//         /**
//          * @brief delete a positively oriented triangle uvw
//          */
//         void delete_triangle(int u, int v, int w);

//         /**
//          * @brief return a vertex w such that uvw is a positively oriented triangle
//          */
//         int adjacent(int u, int v);

//         /**
//          * @brief return vertices v, w such that uvw is a positively oriented triangle
//          */
//         void adjacent2vertex(int u, int& v, int & w);

//     private:
//         struct pair_hash
//         {
//             std::size_t operator () (const std::pair<int,int> &p) const 
//             {
//                 auto h1 = std::hash<int>{}(p.first);
//                 auto h2 = std::hash<int>{}(p.second);
//                 return h1 ^ h2;  
//             }
//         };
        
//         /* used for adjacent method */
//         std::unordered_map<std::pair<int, int>, int, pair_hash> _adjacent_face_table;

//         /* used for adjacent2vertex method, given an i'th vertex, return a vertex in a same triangle */
//         std::vector<int> _adjacent_edge_table;
// };

// TriangulationStorage::Triangle::Triangle(int u, int v, int w)
// {
// }

// // bool TriangulationStorage::Triangle::operator<(const Triangle& other) const
// // {
// //     return (vids[0] < other.vids[0]) || (vids[0] == other.vids[0] && vids[1] < other.vids[1]);
// // }

// void TriangulationStorage::add_triangle(int u, int v, int w)
// {
//     assert(adjacent(u, v) < 0);
//     _adjacent_face_table[std::make_pair(u, v)] = w;
//     _adjacent_face_table[std::make_pair(v, w)] = u;
//     _adjacent_face_table[std::make_pair(w, u)] = v;
//     _adjacent_edge_table[u] = v;
//     _adjacent_edge_table[v] = w;
//     _adjacent_edge_table[w] = u;
// }

// void TriangulationStorage::delete_triangle(int u, int v, int w)
// {
//     _adjacent_face_table.erase(std::make_pair(u, v));
//     _adjacent_face_table.erase(std::make_pair(v, w));
//     _adjacent_face_table.erase(std::make_pair(w, u));
//     /* following operation may be redundant, if make sure every triangle deletion 
//        is followed by triangle creations that cover all the same vertices */
//     if(_adjacent_edge_table[u] == v || _adjacent_edge_table[u] == w)
//         _adjacent_edge_table[u] = -1;
//     if(_adjacent_edge_table[v] == w || _adjacent_edge_table[v] == u)
//         _adjacent_edge_table[v] = -1;
//     if(_adjacent_edge_table[w] == u || _adjacent_edge_table[w] == v)
//         _adjacent_edge_table[w] = -1;
// }

// int TriangulationStorage::adjacent(int u, int v)
// {
//     auto it = _adjacent_face_table.find(std::make_pair(u, v));
//     if(it == _adjacent_face_table.end())
//         return -1;
//     else
//         return it->second;
// }

// void TriangulationStorage::adjacent2vertex(int u, int& v, int & w)
// {
//     v = _adjacent_edge_table[u];
//     assert(v >= 0);
//     w = adjacent(u, v);
//     if(w < 0)
//         w = adjacent(v, u);
// }

// /**
//  * @brief constrained delaunay triangulation
//  * @tparam T number type of point coordinate 
//  */  
// template<typename T>
// class Triangulation : public TriangulationStorage
// {
//     public:
//         Triangulation();

//         ~Triangulation() = default;

//         typedef geo2d::Point<T> Point;

//         public:
//             struct Vertex
//             {
//                 Point pos;
//             };

//     public:
//         /**
//          * @brief return the number of vertices, excluding ghost point
//          */
//         unsigned n_vertices() const;

//         /**
//          * @brief clear all vertices and triangles, excluding ghost point
//          */
//         void clear();
        
//         /**
//          * @brief insert a vertex into a Delaunay Triangulation
//          */
//         int insert_vertex(const Vertex& v, bool append = true);

//         /**
//          * @brief Bowyer–Watson point-insert algorithm
//          */
//         void insert_vertex(int u, Triangle& t);

//     private:
//         /* try to build first triangle and ghost triangles */
//         void first_tri(int u, int v, int w);

//         void dig_cavity(int u, int v, int w);

//     private:
//         std::vector<Vertex> _vertices;
// };

// template<typename T>
// Triangulation<T>::Triangulation()
// {
// }

// template<typename T>
// unsigned Triangulation<T>::n_vertices() const
// {
//     return _vertices.size();
// }

// template<typename T>
// void Triangulation<T>::clear()
// {
//     _vertices.clear();
//     _triangles.clear();
// }

// template<typename T>
// int Triangulation<T>::insert_vertex(const Vertex& v, bool append)
// {
//     if(append)
//         _vertices.push_back(v);

//     if(_vertices.size() < 3)
//         return _vertices.size() - 1;

//     // has no triangles or all previous vertices are collinear
//     if(_triangles.empty())
//     {
//         ORIENTATION ori = orient_2d(_vertices[0].pos, _vertices[1].pos, v.pos);
//         if(ori == ORIENTATION::COLLINEAR)   // still all collinear, just insert the vertex
//             return _vertices.size() - 1;

//         if(ori == ORIENTATION::POSITIVE)
//             first_tri(0, 1, _vertices.size()-1);
//         else
//             first_tri(0, _vertices.size()-1, 0);
        
//         for(unsigned i = 2; i < _vertices.size() - 1; ++i)
//             insert_vertex(_vertices[i], false);

//         return _vertices.size() - 1;
//     }
// }

// template<typename T>
// void Triangulation<T>::insert_vertex(int u, Triangle& t)
// {
//     delete_triangle(t.vids[0], t.vids[1], t.vids[2]);
//     dig_cavity(u, t.vids[0], t.vids[1]);
//     dig_cavity(u, t.vids[1], t.vids[2]);
//     dig_cavity(u, t.vids[2], t.vids[0]);
// }

// template<typename T>
// void Triangulation<T>::dig_cavity(int u, int v, int w)
// {
//     int x = adjacent(w, v);
//     if(x < 0)
//         return;
    
// }

// template<typename T>
// void Triangulation<T>::first_tri(int u, int v, int w)
// {
//     add_triangle(u, v, w);
//     add_triangle(v, u, Trianglulation_Ghost_Idx);
//     add_triangle(w, v, Trianglulation_Ghost_Idx);
//     add_triangle(u, w, Trianglulation_Ghost_Idx);
// }


}   // namespace algorithm
}   // namespace CMTL

#endif // __geo2d_triangulation_h__