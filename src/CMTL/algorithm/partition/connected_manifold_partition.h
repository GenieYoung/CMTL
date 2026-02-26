#ifndef __algorithm_connected_manifold_partition__
#define __algorithm_connected_manifold_partition__

#include <queue>
#include <unordered_map>
#include <vector>

namespace CMTL {
namespace algorithm {

/**
 * @brief partition the input faces into connected manifolds
 * @param faces input faces, each face is represented by a list of vertex
 * @param groups a list of connected manifolds, each manifold is represented by
 * a list of face indices
 * @tparam VertexIndex vertex index type, must be hashable and comparable
 * @tparam FaceIndex face index type
 */
template <typename VertexIndex, typename FaceIndex>
void connected_manifold_partition_3d(
    const std::vector<std::vector<VertexIndex>>& faces,
    std::vector<std::vector<FaceIndex>>& groups) {
  struct EdgeHash {
    size_t operator()(const std::pair<VertexIndex, VertexIndex>& edge) const {
      return std::hash<VertexIndex>()(edge.first) ^
             std::hash<VertexIndex>()(edge.second);
    }
  };

  // first, build edge-face map
  std::unordered_map<std::pair<VertexIndex, VertexIndex>,
                     std::vector<FaceIndex>, EdgeHash>
      edge_face_map;
  for (std::size_t i = 0; i < faces.size(); ++i) {
    const std::vector<VertexIndex>& face = faces[i];
    for (std::size_t j = 0, k = 1; j < face.size();
         ++j, ++k, k %= face.size()) {
      VertexIndex v0 = face[j];
      VertexIndex v1 = face[k];
      if (v0 > v1) std::swap(v0, v1);
      edge_face_map[std::make_pair(v0, v1)].push_back(i);
    }
  }

  // then, build face adjacency list, skip non-manifold edges
  std::vector<std::vector<FaceIndex>> face_adj_list(faces.size());
  for (const auto& entry : edge_face_map) {
    if (entry.second.size() == 2) {
      face_adj_list[entry.second[0]].push_back(entry.second[1]);
      face_adj_list[entry.second[1]].push_back(entry.second[0]);
    }
  }

  std::vector<bool> visited(faces.size(), false);
  groups.clear();

  // ok, now we can extract connected components
  for (std::size_t i = 0; i < faces.size(); ++i) {
    if (visited[i]) continue;
    std::vector<FaceIndex> group;
    std::queue<FaceIndex> stack;
    stack.push(i);
    visited[i] = true;
    while (!stack.empty()) {
      FaceIndex curr = stack.front();
      stack.pop();
      group.push_back(curr);
      for (FaceIndex adj : face_adj_list[curr]) {
        if (!visited[adj]) {
          visited[adj] = true;
          stack.push(adj);
        }
      }
    }
    groups.push_back(group);
  }
}

}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_connected_manifold_partition__