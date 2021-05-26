#pragma once

#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

#include "core/random_generator.h"
#include "core/descriptions.h"

#include "edge.h"

using Graph = std::vector<std::unordered_set<int32_t>>;
using EnemiesDistribution =
    std::unordered_map<EntityType, std::pair<int32_t, int32_t>>;

enum class RoomDifficulty {
  kStart,
  kEasy,
  kMedium,
  kHard
};

class MapGenerator {
 public:
  MapGenerator();

  void Generate();

 private:
  Graph GenerateGraph();
  std::vector<Edge> GenerateRawGraph();
  std::vector<EntityDescription> GenerateEntities(RoomDifficulty difficulty);
  EntityDescription GenerateBoss(RoomDifficulty difficulty);

  int32_t size_;
  RandomGenerator random_;
  std::unordered_map<RoomDifficulty, bool> was_boss_generated_;
  const std::unordered_map<RoomDifficulty, EnemiesDistribution>
      distributions_;
  const std::vector<EntityType> decor_types_;
  const std::vector<EntityType> pile_types_;
};
