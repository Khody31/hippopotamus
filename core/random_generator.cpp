#include "random_generator.h"

RandomGenerator::RandomGenerator()
    : generator_(time(nullptr)) {
}

int32_t RandomGenerator::GenerateInt(int32_t left_border,
                                     int32_t right_border) {
  std::uniform_int_distribution<int32_t> distribution(left_border, right_border);
  return distribution(generator_);
}

float RandomGenerator::GenerateFloat(float left_border, float right_border) {
  std::uniform_real_distribution<float> distribution(left_border, right_border);
  return distribution(generator_);
}





