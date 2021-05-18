#pragma once

#include <utility>
#include <cstdint>

struct Edge {
  std::pair<int32_t, int32_t> vertexes;
  int32_t weight;

  bool operator<(const Edge& other) const;
  bool operator==(const Edge& other) const;
};