#pragma once

#include <cstdint>
#include <QVector2D>

namespace game_constants {

constexpr uint64_t kTickTime{5};
constexpr QVector2D kMaxGameCoordinates{1.6, 0.9};

constexpr QVector2D kHorizontalDoorSize{
    kMaxGameCoordinates.x() / 4, kMaxGameCoordinates.y() / 9};
constexpr QVector2D kVerticalDoorSize{
    kHorizontalDoorSize.y(), kHorizontalDoorSize.x()};

constexpr QVector2D kTopDoorCoordinates{
  0, kMaxGameCoordinates.y() - kHorizontalDoorSize.y() / 2};
constexpr QVector2D kBottomDoorCoordinates{-kTopDoorCoordinates};
constexpr QVector2D kRightDoorCoordinates{
  kMaxGameCoordinates.x() - kVerticalDoorSize.x() / 2, 0};
constexpr QVector2D kLeftDoorCoordinates{-kRightDoorCoordinates};

constexpr QVector2D
    kPosToMovePlayerTop{kBottomDoorCoordinates + QVector2D{0, 0.2}};
constexpr QVector2D
    kPosToMovePlayerBottom{kTopDoorCoordinates - QVector2D{0, 0.2}};
constexpr QVector2D
    kPosToMovePlayerLeft{kRightDoorCoordinates - QVector2D{0.2, 0}};
constexpr QVector2D
    kPosToMovePlayerRight{kLeftDoorCoordinates + QVector2D{0.2, 0}};

}  // namespace game_constants
