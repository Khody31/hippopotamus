#pragma once

#include <vector>
#include <cstdint>

namespace utility {

class DisjointSetUnion {
 public:
  explicit DisjointSetUnion(int32_t size);

  void Unite(int32_t first, int32_t second);
  bool AreUnited(int32_t first, int32_t second);

 private:
  int32_t GetParent(int32_t vertex);
  std::vector<int32_t> parents_;
};

}  // namespace utility
