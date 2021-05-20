#include <set>
#include <random>
#include <queue>
#include <algorithm>
#include <limits>

#include "map_generator.h"
#include "core/utility.h"
#include "core/constants.h"
#include "disjoint_set_union.h"

/*
 * Let us define map as a rectangle with n * m rooms.
 * We will say that there is an edge between two vertices, if their representatives(rooms) are neighbors in map.
 * So let us check for each room if it has a neighbors on bottom and on right.
 * And add the edge with random_ weight to our result graph.
 */
std::vector<Edge> MapGenerator::GenerateRawGraph() {
  int32_t size = constants::kMapHorizontalSize
      * constants::kMapVerticalSize;
  RandomGenerator random_generator;
  std::vector<Edge> edges;
  for (int32_t i = 0; i < size; ++i) {
    if (i % constants::kMapHorizontalSize + 1
        < constants::kMapHorizontalSize) {
      int32_t weight = random_generator.GenerateInt();
      edges.push_back({{i, i + 1}, weight});
    }

    if (i + constants::kMapHorizontalSize < size) {
      int32_t weight = random_generator.GenerateInt();
      edges.push_back({{i, i + constants::kMapHorizontalSize}, weight});
    }
  }
  return edges;
}

MapGenerator::Graph MapGenerator::GenerateGraph() {
  int32_t size = constants::kMapHorizontalSize
      * constants::kMapVerticalSize;

  std::vector<Edge> edges = GenerateRawGraph();
  std::sort(edges.begin(), edges.end());

  Graph result(size);
  DisjointSetUnion dsu(size);
  for (Edge& edge : edges) {
    if (dsu.AreUnited(edge.vertices.first,
                      edge.vertices.second)) {
      continue;
    }

    dsu.Unite(edge.vertices.first, edge.vertices.second);
    result[edge.vertices.first].insert(edge.vertices.second);
    result[edge.vertices.second].insert(edge.vertices.first);
  }

  return result;
}


std::vector<EntityDescription> MapGenerator::GenerateEnemies(
    RoomDifficulty difficulty) {
  std::vector<EntityDescription> result;

  for (auto[type, distribution] :
      difficulty_to_enemies_distribution_[difficulty]) {
    int32_t count = random_.GenerateInt(distribution.first, distribution.second);
    for (int i = 0; i < count; ++i) {
      QVector2D pos{
          random_.GenerateFloat(constants::kMaxGameCoordinates.x(),
                                -constants::kMaxGameCoordinates.x()),
          random_.GenerateFloat(constants::kMaxGameCoordinates.y(),
                                -constants::kMaxGameCoordinates.y())};
      result.push_back({type, pos});
    }
  }

  return result;
}



void MapGenerator::GenerateMap() {
  Graph map_graph = GenerateGraph();

  std::queue<int32_t> rooms_queue;
  rooms_queue.push(0);
  std::vector<int32_t> is_rooms_generated(map_graph.size());
  std::vector<int32_t> distances(map_graph.size());
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

    RoomDescription room{id};
    room.connected_rooms[0] = create_connection(id, id - constants::kMapHorizontalSize);
    room.connected_rooms[1] = create_connection(id, id + 1);
    room.connected_rooms[2] = create_connection(id, id + constants::kMapHorizontalSize);
    room.connected_rooms[3] = create_connection(id, id - 1);

    room.descriptions = GenerateEnemies(GetDifficulty(distances[id]));
    utility::LoadRoomToJson(room);

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

MapGenerator::MapGenerator() {
  // Set up entities distributions for each difficulty
  difficulty_to_enemies_distribution_[RoomDifficulty::kEasy] = {
      {EntityType::kStupidBot, {1, 4}},
      {EntityType::kAngryPlant, {1, 4}},
      {EntityType::kCleverBot, {0, 2}}
  };

  difficulty_to_enemies_distribution_[RoomDifficulty::kMedium] = {
      {EntityType::kStupidBot, {1, 3}},
      {EntityType::kAngryPlant, {3, 5}},
      {EntityType::kCleverBot, {2, 4}}
  };

  difficulty_to_enemies_distribution_[RoomDifficulty::kHard] = {
      {EntityType::kStupidBot, {3, 6}},
      {EntityType::kAngryPlant, {3, 5}},
      {EntityType::kCleverBot, {4, 10}}
  };
}
MapGenerator::RoomDifficulty MapGenerator::GetDifficulty(int distance) {
  if (distance < constants::kEasyRoomMaxDist) {
    return RoomDifficulty::kEasy;
  }
  if (distance < constants::kMediumRoomMaxDist) {
    return RoomDifficulty::kMedium;
  }
  return RoomDifficulty::kHard;
}
