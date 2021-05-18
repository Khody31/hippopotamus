#include "disjoint_set_union.h"


void DisjointSetUnion::Unite(int32_t first, int32_t second) {
  first = GetParent(first);
  second = GetParent(second);

  parents_.at(first) = second;
}

int32_t DisjointSetUnion::GetParent(int32_t vertex) {
  if (vertex == parents_.at(vertex)) {
    return vertex;
  }
  return parents_.at(vertex) = GetParent(parents_.at(vertex));
}

DisjointSetUnion::DisjointSetUnion(int32_t size)
    : parents_(size) {
  for (int i = 0; i < size; ++i) {
    parents_[i] = i;
  }
}