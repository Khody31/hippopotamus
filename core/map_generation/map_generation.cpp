#include <set>
#include <random>
#include <queue>
#include <algorithm>
#include <limits>

#include "core/map_generation/map_generation.h"
#include "core/descriptions.h"
#include "core/utility.h"
#include "core/constants.h"
#include "disjoint_set_union.h"
#include "edge.h"

/*
 * Let us define map as a rectangle with n * m rooms.
 * We will say that there is an edge between two vertices, if their representatives(rooms) are neighbors in map.
 * So let us check for each room if it has a neighbors on top and on left.
 * And add the edge with random weight to our result graph.
 */
std::vector<Edge> GenerateRawGraph() {
  int32_t size = constants::kMapHorizontalSize
      * constants::kMapVerticalSize;

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution distribution(
      std::numeric_limits<int32_t>::min(),
      std::numeric_limits<int32_t>::max());

  std::vector<Edge> edges;
  for (int32_t i = 0; i < size; ++i) {
    if (i % constants::kMapHorizontalSize + 1
        < constants::kMapHorizontalSize) {
      int32_t weight = distribution(generator);
      edges.push_back({{i, i + 1}, weight});
    }

    if (i + constants::kMapHorizontalSize < size) {
      int32_t weight = distribution(generator);
      edges.push_back({{i, i + constants::kMapHorizontalSize}, weight});
    }
  }
  return edges;
}

Graph GenerateGraph() {
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

std::vector<EntityDescription> GenerateEnemies(int32_t distance) {
  std::vector<EntityDescription> enemies;

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution distribution(
      std::numeric_limits<int32_t>::min(),
      std::numeric_limits<int32_t>::max());

  int angry_plant_cnt = 0;
  int stupid_bot_cnt = 0;
  int clever_bot_cnt = 0;
  if (distance < 15) {
    angry_plant_cnt = distribution(generator) % 3 + 1;
    stupid_bot_cnt = distribution(generator) % 3 + 2;
    clever_bot_cnt = distribution(generator) % 2;
  } else if (distance < 30) {
    angry_plant_cnt = distribution(generator) % 3 + 1;
    stupid_bot_cnt = distribution(generator) % 2;
    clever_bot_cnt = distribution(generator) % 4 + 2;
  } else if (distance < 50) {
    angry_plant_cnt = distribution(generator) % 7 + 3;
    clever_bot_cnt = distribution(generator) % 13 + 2;
  }

  std::uniform_real_distribution<float> x_distribution(
      constants::kMaxGameCoordinates.x(),
      -constants::kMaxGameCoordinates.x());
  std::uniform_real_distribution<float> y_distribution(
      constants::kMaxGameCoordinates.y(),
      -constants::kMaxGameCoordinates.y());

  for (int i = 0; i < angry_plant_cnt; ++i) {
    enemies.push_back({EntityType::kAngryPlant,
                       {x_distribution(generator),
                        y_distribution(generator)}});
  }

  for (int i = 0; i < stupid_bot_cnt; ++i) {
    enemies.push_back({EntityType::kStupidBot,
                       {x_distribution(generator),
                        y_distribution(generator)}});
  }

  for (int i = 0; i < clever_bot_cnt; ++i) {
    enemies.push_back({EntityType::kCleverBot,
                       {x_distribution(generator),
                        y_distribution(generator)}});
  }

  return enemies;
}

void GenerateMap() {
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
