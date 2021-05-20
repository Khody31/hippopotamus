#include <set>
#include <random>
#include <queue>
#include <algorithm>
#include <limits>

#include "core/map_generation/map_generation.h"
#include "core/descriptions.h"
#include "core/utility.h"
#include "core/constants.h"
#include "core/random_generator.h"
#include "disjoint_set_union.h"
#include "edge.h"

/*
 * Let us define map as a rectangle with n * m rooms.
 * We will say that there is an edge between two vertices, if their representatives(rooms) are neighbors in map.
 * So let us check for each room if it has a neighbors on top and on left.
 * And add the edge with random weight to our result graph.
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

void MapGenerator::GenerateEntities(int32_t count,
                      EntityType type,
                      std::vector<EntityDescription>* destination) {
  for (int i = 0; i < count; ++i) {
    QVector2D pos {
        random.GenerateFloat(constants::kMaxGameCoordinates.x(),
                             -constants::kMaxGameCoordinates.x()),
        random.GenerateFloat(constants::kMaxGameCoordinates.y(),
                             -constants::kMaxGameCoordinates.y())};
    destination->push_back({EntityType::kAngryPlant,
                       pos});
  }
}

std::vector<EntityDescription> MapGenerator::GenerateEnemies(int32_t distance) {
  RandomGenerator random;

  int angry_plant_cnt = 0;
  int stupid_bot_cnt = 0;
  int clever_bot_cnt = 0;
  if (distance < 15) {
    angry_plant_cnt = random.GenerateInt() % 3 + 1;
    stupid_bot_cnt = random.GenerateInt() % 3 + 2;
    clever_bot_cnt = random.GenerateInt() % 2;
  } else if (distance < 30) {
    angry_plant_cnt = random.GenerateInt() % 3 + 1;
    stupid_bot_cnt = random.GenerateInt() % 2;
    clever_bot_cnt = random.GenerateInt() % 4 + 2;
  } else if (distance < 50) {
    angry_plant_cnt = random.GenerateInt() % 7 + 3;
    clever_bot_cnt = random.GenerateInt() % 13 + 2;
  }

  std::vector<EntityDescription> enemies;

  GenerateEntities(clever_bot_cnt, EntityType::kCleverBot, &enemies);
  GenerateEntities(stupid_bot_cnt, EntityType::kStupidBot, &enemies);
  GenerateEntities(angry_plant_cnt, EntityType::kAngryPlant, &enemies);

  return enemies;
}

void MapGenerator::GenerateMap() {
  Graph map_graph = GenerateGraph();

  std::queue<int32_t> rooms_queue;
  rooms_queue.push(0);
  std::vector<int32_t> is_rooms_generated(map_graph.size());
  std::vector<int32_t> distances(map_graph.size());
  is_rooms_generated.front() = true;

  while (!rooms_queue.empty()) {
    int32_t id = rooms_queue.front();
    rooms_queue.pop();

    RoomDescription room{id};
    room.connected_rooms[0] =
        map_graph[id].find(id - constants::kMapHorizontalSize) !=
            map_graph[id].end() ? id - constants::kMapHorizontalSize : -1;
    room.connected_rooms[1] =
        map_graph[id].find(id + 1) != map_graph[id].end() ? id + 1 : -1;
    room.connected_rooms[2] =
        map_graph[id].find(id + constants::kMapHorizontalSize)
            != map_graph[id].end() ? id + constants::kMapHorizontalSize : -1;
    room.connected_rooms[3] =
        map_graph[id].find(id - 1) != map_graph[id].end() ? id - 1 : -1;

    room.descriptions = GenerateEnemies(distances[id]);
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
