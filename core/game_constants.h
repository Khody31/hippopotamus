#pragma once

#include <cstdint>
#include <QVector2D>

namespace game_constants {

constexpr uint64_t kTickTime{5};
constexpr QVector2D kMaxGameCoordinates{1.6, 0.9};

constexpr QVector2D kTopDoorCoordinates{0, 0.84};
constexpr QVector2D kBottomDoorCoordinates{0, -0.84};
constexpr QVector2D kLeftDoorCoordinates{-1.55, 0};
constexpr QVector2D kRightDoorCoordinates{1.55, 0};

constexpr QVector2D kHorizontalDoorSize{0.4, 0.1};
constexpr QVector2D kVerticalDoorSize{0.1, 0.4};

constexpr QVector2D
    kPosToMovePlayerTop{kBottomDoorCoordinates + QVector2D{0, 0.2}};
constexpr QVector2D
    kPosToMovePlayerBottom{kTopDoorCoordinates - QVector2D{0, 0.2}};
constexpr QVector2D
    kPosToMovePlayerLeft{kRightDoorCoordinates - QVector2D{0.2, 0}};
constexpr QVector2D
    kPosToMovePlayerRight{kLeftDoorCoordinates + QVector2D{0.2, 0}};

}  // namespace game_constants
