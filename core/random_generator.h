#pragma once

#include <random>
#include <limits>

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

  QVector2D GetPositionAvoidingDoors() {
    QVector2D result = GetAnyPosition();

    if (result.distanceToPoint(constants::kTopDoorCoordinates) <= 0.3) {
      result /= 2;
    }
    if (result.distanceToPoint(constants::kLeftDoorCoordinates) <= 0.3) {
      result /= 2;
    }
    if (result.distanceToPoint(constants::kBottomDoorCoordinates) <= 0.3) {
      result /= 2;
    }
    if (result.distanceToPoint(constants::kRightDoorCoordinates) <= 0.3) {
      result /= 2;
    }

    return result;
  }

  QVector2D GetAnyPosition() {
    return {
        GetReal(-constants::kMaxGameCoordinates.x(),
                constants::kMaxGameCoordinates.x()),
        GetReal(-constants::kMaxGameCoordinates.y(),
                constants::kMaxGameCoordinates.y() - 0.3f)
    };
  }

 private:
  std::mt19937 generator_;
};
