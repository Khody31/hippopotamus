#include <set>
#include <queue>
#include <algorithm>
#include <utility>

#include "utilities/transformation.h"
#include "utilities/conversion.h"
#include "utilities/dsu.h"
#include "core/map_generator.h"
#include "core/constants.h"

// Set up size of the map and entities distributions for each difficulty
MapGenerator::MapGenerator()
    : size_(constants::kMapHorizontalSize * constants::kMapVerticalSize),
      was_boss_generated_{
          {RoomDifficulty::kEasy, true},
          {RoomDifficulty::kMedium, false},
          {RoomDifficulty::kHard, false}
      },
      distributions_{{RoomDifficulty::kEasy, {
          {EntityType::kBattleTotem, {0, 1}},
          {EntityType::kWasp, {2, 5}}
      }}, {RoomDifficulty::kMedium, {
          {EntityType::kBouncingTotem, {1, 2}},
          {EntityType::kBattleTotem, {0, 1}},
          {EntityType::kWasp, {3, 4}}
      }}, {RoomDifficulty::kHard, {
          {EntityType::kBouncingTotem, {3, 5}},
          {EntityType::kBattleTotem, {3, 5}},
          {EntityType::kWasp, {4, 10}}
      }}},
      decor_types_{
          EntityType::kDecorative1,
          EntityType::kDecorative2,
          EntityType::kDecorative3,
          EntityType::kDecorative4,
          EntityType::kDecorative5,
          EntityType::kDecorative6,
          EntityType::kDecorative7,
          EntityType::kDecorative8,
          EntityType::kDecorative9,
          EntityType::kDecorative10,
          EntityType::kDecorative11,
          EntityType::kDecorative12,
          EntityType::kDecorative13,
          EntityType::kDecorative14,
          EntityType::kDecorative15
      },
      pile_types_{
          EntityType::kPile1,
          EntityType::kPile2,
          EntityType::kPile3,
          EntityType::kPile4,
          EntityType::kPile5,
      } {
}

RoomDifficulty GetDifficulty(int distance) {
  if (distance == 0) {
    return RoomDifficulty::kStart;
  }
  if (distance < constants::kEasyRoomMaxDist) {
    return RoomDifficulty::kEasy;
  }
  if (distance < constants::kMediumRoomMaxDist) {
    return RoomDifficulty::kMedium;
  }
  return RoomDifficulty::kHard;
}

/*
 * Let us define map as a rectangle with n * m rooms.
 * We will say that there is an edge between two vertices, if their representatives(rooms) are neighbors in map.
 * So let us check for each room if it has a neighbors on bottom and on right.
 * And add the edge with random weight to our result graph.
 */
std::vector<Edge> MapGenerator::GenerateRawGraph() {
  std::vector<Edge> edges;
  for (int32_t i = 0; i < size_; ++i) {
    if (i % constants::kMapHorizontalSize + 1
        < constants::kMapHorizontalSize) {
      edges.emplace_back(
          std::pair(i, i + 1),
          random_.GetInt<int32_t>());
    }

    if (i + constants::kMapHorizontalSize < size_) {
      edges.emplace_back(
          std::pair(i, i + constants::kMapHorizontalSize),
          random_.GetInt<int32_t>());
    }
  }
  return edges;
}

Graph MapGenerator::GenerateGraph() {
  Graph result(size_);
  utility::DisjointSetUnion dsu(size_);
  std::vector<Edge> edges = GenerateRawGraph();
  std::sort(edges.begin(), edges.end());

  for (const auto&[vertices, weight] : edges) {
    if (dsu.AreUnited(vertices.first, vertices.second)) {
      continue;
    }

    dsu.Unite(vertices.first, vertices.second);
    result[vertices.first].insert(vertices.second);
    result[vertices.second].insert(vertices.first);
  }

  return result;
}

EntityDescription MapGenerator::GenerateBoss(RoomDifficulty difficulty) {
  if (difficulty == RoomDifficulty::kMedium) {
    return {EntityType::kNecromancer, random_.GetPositionAvoidingDoors()};
  } else {
    return {EntityType::kShootingBoss, random_.GetPositionAvoidingDoors()};
  }
}

std::vector<EntityDescription> MapGenerator::GenerateEntities(
    RoomDifficulty difficulty) {
  if (difficulty == RoomDifficulty::kStart) {
    return {{EntityType::kTutorial, QVector2D{0, 0}}};
  }

  if (!was_boss_generated_[difficulty]) {
    was_boss_generated_[difficulty] = true;
    return {GenerateBoss(difficulty)};
  }

  std::vector<EntityDescription> result;
  for (auto&[type, distribution] :
      distributions_.at(difficulty)) {
    int32_t count = random_.GetInt(distribution.first, distribution.second);
    for (int i = 0; i < count; ++i) {
      result.emplace_back(type, random_.GetPositionAvoidingDoors());
    }
  }

  int32_t decor_count = random_.GetInt(0, 6);
  for (int i = 0; i < decor_count; ++i) {
    result.emplace_back(
        decor_types_[random_.GetInt(0, 14)],
        random_.GetAnyPosition());
  }

  int32_t piles_count = random_.GetInt(0, 3);
  for (int i = 0; i < piles_count; ++i) {
    result.emplace_back(
        pile_types_[random_.GetInt(0, 4)],
        random_.GetPositionAvoidingDoors());
  }

  return result;
}

void MapGenerator::Generate() {
  Graph map_graph = GenerateGraph();

  std::queue<int32_t> rooms_queue;
  rooms_queue.push(0);
  std::vector<bool> is_rooms_generated(size_);
  std::vector<int32_t> distances(size_);
  is_rooms_generated.front() = true;

  auto create_connection = [&map_graph](int32_t source, int32_t destination) {
    if (map_graph[source].find(destination) != map_graph[source].end()) {
      return destination;
    }
    return -1;
  };

  while (!rooms_queue.empty()) {
    int32_t id = rooms_queue.front();
    rooms_queue.pop();

    utility::LoadRoomToJson(RoomDescription{
        id, {create_connection(id, id - constants::kMapHorizontalSize),
             create_connection(id, id + 1),
             create_connection(id, id + constants::kMapHorizontalSize),
             create_connection(id, id - 1)},
        GenerateEntities(GetDifficulty(distances[id]))});

    for (auto next_id : map_graph[id]) {
      if (is_rooms_generated[next_id]) {
        continue;
      }
      rooms_queue.push(next_id);
      distances[next_id] = distances[id] + 1;
      is_rooms_generated[next_id] = true;
    }
  }
}
