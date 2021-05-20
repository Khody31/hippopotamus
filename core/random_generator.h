#pragma once

#include <random>

class RandomGenerator {
 public:
  RandomGenerator();

  int32_t GenerateInt(int32_t left_border = std::numeric_limits<int32_t>::min(),
                      int32_t right_border = std::numeric_limits<int32_t>::max());
  float GenerateFloat(float left_border = std::numeric_limits<float>::min(),
                      float right_border = std::numeric_limits<float>::max());
 private:
  std::mt19937 generator_;
};
