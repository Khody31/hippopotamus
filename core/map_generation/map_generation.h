#pragma once

#include <utility>
#include <cstdint>
#include <tuple>
#include <vector>
#include <unordered_set>
#include <core/random_generator.h>
#include <core/descriptions.h>
#include "edge.h"

class MapGenerator {
 public:
  using Graph = std::vector<std::unordered_set<int32_t>>;

  void GenerateMap();
 private:
  Graph GenerateGraph();
  std::vector<Edge> GenerateRawGraph();
  std::vector<EntityDescription> GenerateEnemies(int32_t distance);
  void GenerateEntities(int32_t count,
                        EntityType type,
                        std::vector<EntityDescription>* destination);

  RandomGenerator random;
};