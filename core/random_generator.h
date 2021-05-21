#pragma once

#include <random>

class RandomGenerator {
 public:
  RandomGenerator() : generator_(std::random_device()()) {
  }

  template<typename T>
  T GetInt(T from = std::numeric_limits<T>::min(),
           T to = std::numeric_limits<T>::max()) {
    std::uniform_int_distribution<T> distribution(from, to);
    return distribution(generator_);
  }

  template<typename T>
  T GetReal(T from = std::numeric_limits<T>::min(),
            T to = std::numeric_limits<T>::max()) {
    std::uniform_real_distribution<T> distribution(from, to);
    return distribution(generator_);
  }

 private:
  std::mt19937 generator_;
};
