#pragma once

#include <QVector2D>

namespace constants {

constexpr uint64_t kTickTime = 5;
constexpr float kCorrectionPercent = 0.2;
constexpr float kCorrectionSlop = 0.01;

constexpr QVector2D kMaxGameCoordinates(1.6, 0.9);

constexpr QVector2D kHorizontalDoorSize
    (kMaxGameCoordinates.x() / 4, kMaxGameCoordinates.y() / 9);
constexpr QVector2D
    kVerticalDoorSize(kHorizontalDoorSize.y(), kHorizontalDoorSize.x());

constexpr QVector2D kTopDoorCoordinates
    (0, kMaxGameCoordinates.y() - kHorizontalDoorSize.y() / 2);
constexpr QVector2D kRightDoorCoordinates
    (kMaxGameCoordinates.x() - kVerticalDoorSize.x() / 2, 0);

constexpr QVector2D kBottomDoorCoordinates(-kTopDoorCoordinates);
constexpr QVector2D kLeftDoorCoordinates(-kRightDoorCoordinates);

constexpr QVector2D
    kPosToMovePlayerTop(kBottomDoorCoordinates + QVector2D{0, 0.2});
constexpr QVector2D
    kPosToMovePlayerBottom(kTopDoorCoordinates - QVector2D{0, 0.2});
constexpr QVector2D
    kPosToMovePlayerLeft(kRightDoorCoordinates - QVector2D{0.2, 0});
constexpr QVector2D
    kPosToMovePlayerRight(kLeftDoorCoordinates + QVector2D{0.2, 0});

constexpr QVector2D kVerticalWallSize(0.2, kMaxGameCoordinates.y());
constexpr QVector2D kHorizontalWallSize(kMaxGameCoordinates.x(), 0.2);

constexpr QVector2D kTopWallCoordinates
    (0, kMaxGameCoordinates.y() + kHorizontalDoorSize.y() / 2);
constexpr QVector2D kRightWallCoordinates
    (kMaxGameCoordinates.x() + kVerticalDoorSize.x() / 2, 0);

constexpr QVector2D kBottomWallCoordinates(-kTopWallCoordinates);
constexpr QVector2D kLeftWallCoordinates(-kRightWallCoordinates);

constexpr int32_t map_vertical_size = 10;
constexpr int32_t map_horizontal_size = 10;

}  // namespace constants
