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
      distributions_{{RoomDifficulty::kEasy, {
          {EntityType::kStupidBot, {1, 4}},
          {EntityType::kAngryPlant, {1, 4}},
          {EntityType::kCleverBot, {0, 2}}
      }}, {RoomDifficulty::kMedium, {
          {EntityType::kStupidBot, {1, 3}},
          {EntityType::kAngryPlant, {3, 5}},
          {EntityType::kCleverBot, {2, 4}}
      }}, {RoomDifficulty::kHard, {
          {EntityType::kStupidBot, {3, 6}},
          {EntityType::kAngryPlant, {3, 5}},
          {EntityType::kCleverBot, {4, 10}}
      }}} {
}

RoomDifficulty GetDifficulty(int distance) {
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

std::vector<EntityDescription> MapGenerator::GenerateEnemies(
    RoomDifficulty difficulty) {
  std::vector<EntityDescription> result;

  for (auto&[type, distribution] :
      distributions_.at(difficulty)) {
    int32_t count = random_.GetInt(distribution.first, distribution.second);
    for (int i = 0; i < count; ++i) {
      result.emplace_back(type, QVector2D(
          random_.GetReal(constants::kMaxGameCoordinates.x(),
                          -constants::kMaxGameCoordinates.x()),
          random_.GetReal(constants::kMaxGameCoordinates.y(),
                          -constants::kMaxGameCoordinates.y())));
    }
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
        id, GenerateEnemies(GetDifficulty(distances[id])), {
            create_connection(id, id - constants::kMapHorizontalSize),
            create_connection(id, id + 1),
            create_connection(id, id + constants::kMapHorizontalSize),
            create_connection(id, id - 1)}});

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
