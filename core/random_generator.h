#pragma once

#include <random>

class RandomGenerator {
 public:
  RandomGenerator();

  int32_t GenerateInt(int32_t from = std::numeric_limits<int32_t>::min(),
                      int32_t to = std::numeric_limits<int32_t>::max());
  float GenerateFloat(float from = std::numeric_limits<float>::min(),
                      float to = std::numeric_limits<float>::max());
 private:
  std::mt19937 generator_;
};
