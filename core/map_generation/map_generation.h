#pragma once

#include <utility>
#include <cstdint>
#include <tuple>
#include <vector>
#include <unordered_set>

using Graph = std::vector<std::unordered_set<int32_t>>;

Graph GenerateGraph();
void GenerateMap();