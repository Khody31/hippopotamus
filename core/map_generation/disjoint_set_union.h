#pragma once

#include <vector>

class DisjointSetUnion {
 public:
  explicit DisjointSetUnion(int32_t size);

  void Unite(int32_t first, int32_t second);
  int32_t GetParent(int32_t vertex);
 private:
  std::vector<int32_t> parents_;
};
