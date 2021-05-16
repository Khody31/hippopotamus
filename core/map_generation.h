#pragma once

#include <utility>
#include <cstdint>
#include <tuple>
#include <vector>
#include <unordered_set>

using Graph = std::vector<std::unordered_set<int32_t>>;

struct Edge {
  std::pair<int32_t, int32_t> vertexes;
  int32_t weight;

  bool operator<(const Edge& other) const;
  bool operator==(const Edge& other) const;
};

class DisjointSetUnion {
 public:
  explicit DisjointSetUnion(int32_t size);

  void Unite(int32_t first, int32_t second);
  int32_t GetParent(int32_t vertex);
 private:
  std::vector<int32_t> parents_;
};

Graph GenerateGraph();
void GenerateMap();