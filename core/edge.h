#pragma once

#include <utility>
#include <cstdint>

struct Edge {
  Edge(std::pair<int32_t, int32_t> vertices, int32_t weight);

  bool operator<(const Edge& other) const;
  bool operator==(const Edge& other) const;

  std::pair<int32_t, int32_t> vertices;
  int32_t weight;
};
