#pragma once

#include <utility>
#include <cstdint>
#include <tuple>
#include <vector>
#include <unordered_set>

#include "core/random_generator.h"
#include "core/descriptions.h"

#include "edge.h"

class MapGenerator {
 public:
  using Graph = std::vector<std::unordered_set<int32_t>>;
  using EnemiesDistribution = std::unordered_map<
      EntityType, std::pair<int32_t, int32_t>>;

  MapGenerator();
  void GenerateMap();

 private:
  enum class RoomDifficulty {
    kEasy,
    kMedium,
    kHard
  };

 private:
  static RoomDifficulty GetDifficulty(int distance);
  Graph GenerateGraph();
  std::vector<Edge> GenerateRawGraph();
  std::vector<EntityDescription> GenerateEnemies(RoomDifficulty difficulty);

  int32_t size_;
  RandomGenerator random_;
  std::unordered_map<RoomDifficulty, EnemiesDistribution>
      difficulty_to_enemies_distribution_;
};