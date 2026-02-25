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
 * indices
 * @return a list of connected manifolds, each manifold is represented by a list
 * of face
 */
std::vector<std::vector<unsigned>> connected_manifold_partition_3d(
    const std::vector<std::vector<unsigned>>& faces) {
  struct EdgeHash {
    size_t operator()(const std::pair<unsigned, unsigned>& edge) const {
      return std::hash<unsigned>()(edge.first) ^
             std::hash<unsigned>()(edge.second);
    }
  };

  // first, build edge-face map
  std::unordered_map<std::pair<unsigned, unsigned>, std::vector<unsigned>,
                     EdgeHash>
      edge_face_map;
  for (unsigned i = 0; i < faces.size(); ++i) {
    const std::vector<unsigned>& face = faces[i];
    for (unsigned j = 0, k = 1; j < face.size(); ++j, ++k, k %= face.size()) {
      unsigned v0 = face[j];
      unsigned v1 = face[k];
      if (v0 > v1) std::swap(v0, v1);
      edge_face_map[std::make_pair(v0, v1)].push_back(i);
    }
  }

  // then, build face adjacency list, skip non-manifold edges
  std::vector<std::vector<unsigned>> face_adj_list(faces.size());
  for (const auto& entry : edge_face_map) {
    if (entry.second.size() == 2) {
      face_adj_list[entry.second[0]].push_back(entry.second[1]);
      face_adj_list[entry.second[1]].push_back(entry.second[0]);
    }
  }

  std::vector<unsigned> visited(faces.size(), 0);
  std::vector<std::vector<unsigned>> results;

  // ok, now we can extract connected components
  for (unsigned i = 0; i < faces.size(); ++i) {
    if (visited[i]) continue;
    std::vector<unsigned> group;
    std::queue<unsigned> stack;
    stack.push(i);
    visited[i] = 1;
    while (!stack.empty()) {
      unsigned curr = stack.front();
      stack.pop();
      group.push_back(curr);
      for (unsigned adj : face_adj_list[curr]) {
        if (!visited[adj]) {
          visited[adj] = 1;
          stack.push(adj);
        }
      }
    }
    results.push_back(group);
  }
  return results;
}

}  // namespace algorithm
}  // namespace CMTL

#endif  // __algorithm_connected_manifold_partition__