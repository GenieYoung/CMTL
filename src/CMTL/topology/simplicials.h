#ifndef __topologic_simplicials_h__
#define __topologic_simplicials_h__

#include <vector>

namespace CMTL {

/**
 * @brief simplicial complex structure
 */
namespace simplicials {

/**
 * @brief 2-dimensional simplicial complex
 */
template <class VertexData, class EdgeData, class TriangleData>
class Simplicials_2 {
 protected:
  class Vertex;
  class Triangle;

  class Edge : public EdgeData {
   public:
    Edge();
    ~Edge();

    Edge next();
    Edge prev();
    Edge twin();

    Vertex* ori();
    Vertex* dst();
    Vertex* apex();

    Triangle* _tri;
    unsigned char _i;
  };

  class Vertex : public VertexData {
   public:
    Vertex();
    Vertex(const VertexData& vd);
    ~Vertex();

    Edge _adj;
  };

  class Triangle : public TriangleData {
   public:
    Triangle();
    Triangle(const TriangleData& td);
    ~Triangle();

    Vertex* vrt[3];
    Edge nei[3];
  };

 public:
  Simplicials_2() = default;
  ~Simplicials_2() = default;

 protected:
  std::vector<Vertex*> _vertices;
  std::vector<Triangle*> _triangles;
};

}  // namespace simplicials
}  // namespace CMTL

#endif  // __topologic_simplicials_h__