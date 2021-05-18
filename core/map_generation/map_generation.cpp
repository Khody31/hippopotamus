#include <set>
#include <random>
#include <queue>

#include "core/map_generation/map_generation.h"
#include "core/descriptions.h"
#include "core/utility.h"
#include "core/constants.h"
#include "disjoint_set_union.h"
#include "edge.h"

std::vector<Edge> GenerateRawGraph() {
  int32_t size = constants::map_horizontal_size
      * constants::map_vertical_size;

  std::mt19937 generator;
  std::uniform_int_distribution distribution(
      std::numeric_limits<int32_t>::min(),
      std::numeric_limits<int32_t>::max());

  std::vector<Edge> edges;
  for (int32_t i = 0; i < size; ++i) {
    if (i % constants::map_horizontal_size + 1
        < constants::map_horizontal_size) {
      int32_t weight = distribution(generator);
      edges.push_back({{i, i + 1}, weight});
    }

    if (i + constants::map_vertical_size < size) {
      int32_t weight = distribution(generator);
      edges.push_back({{i, i + constants::map_vertical_size}, weight});
    }
  }
  return edges;
}

Graph GenerateGraph() {
  int32_t size = constants::map_horizontal_size
      * constants::map_vertical_size;

  std::vector<Edge> edges = GenerateRawGraph();
  std::sort(edges.begin(), edges.end());

  Graph result(size);
  DisjointSetUnion dsu(size);

  for (Edge& edge : edges) {
    if (dsu.GetParent(edge.vertexes.first)
        == dsu.GetParent(edge.vertexes.second)) {
      continue;
    }

    dsu.Unite(edge.vertexes.first, edge.vertexes.second);
    result[edge.vertexes.first].insert(edge.vertexes.second);
    result[edge.vertexes.second].insert(edge.vertexes.first);
  }

  return result;
}

std::vector<EntityDescription> GenerateEnemies(int32_t distance) {
  // TODO(Khody31) : implement
  return {};
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
        map_graph[id].find(id - constants::map_horizontal_size) !=
            map_graph[id].end() ? id - constants::map_horizontal_size : -1;
    room.connected_rooms[1] =
        map_graph[id].find(id + 1) != map_graph[id].end() ? id + 1 : -1;
    room.connected_rooms[2] =
        map_graph[id].find(id + constants::map_horizontal_size)
            != map_graph[id].end() ? id + constants::map_horizontal_size : -1;
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
