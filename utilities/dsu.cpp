#include "dsu.h"

namespace utility {

void DisjointSetUnion::Unite(int32_t first, int32_t second) {
  parents_[GetParent(first)] = GetParent(second);
}

int32_t DisjointSetUnion::GetParent(int32_t vertex) {
  if (vertex == parents_[vertex]) {
    return vertex;
  }
  return parents_[vertex] = GetParent(parents_[vertex]);
}

DisjointSetUnion::DisjointSetUnion(int32_t size) : parents_(size) {
  for (int i = 0; i < size; ++i) {
    parents_[i] = i;
  }
}

bool DisjointSetUnion::AreUnited(int32_t first, int32_t second) {
  return GetParent(first) == GetParent(second);
}

}  // namespace utility
