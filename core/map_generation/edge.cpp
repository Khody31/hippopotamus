#include "edge.h"

#include <tuple>

bool Edge::operator<(const Edge& other) const {
  return std::tie(weight, vertices) <
      std::tie(other.weight, other.vertices);
}

bool Edge::operator==(const Edge& other) const {
  return vertices == other.vertices;
}

Edge::Edge(std::pair<int32_t, int32_t> vertices, int32_t weight)
  : vertices(vertices), weight(weight) {

}

