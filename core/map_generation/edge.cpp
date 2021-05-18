#include "edge.h"

#include <tuple>

bool Edge::operator<(const Edge& other) const {
  return std::tie(weight, vertexes) <
      std::tie(other.weight, other.vertexes);
}

bool Edge::operator==(const Edge& other) const {
  return vertexes == other.vertexes;
}

