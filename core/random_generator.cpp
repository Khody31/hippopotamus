#include "random_generator.h"

RandomGenerator::RandomGenerator()
    : generator_(time(nullptr)) {
}

int32_t RandomGenerator::GenerateInt(int32_t from,
                                     int32_t to) {
  std::uniform_int_distribution<int32_t> distribution(from, to);
  return distribution(generator_);
}

float RandomGenerator::GenerateFloat(float from, float to) {
  std::uniform_real_distribution<float> distribution(from, to);
  return distribution(generator_);
}





