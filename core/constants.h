#pragma once

#include <QVector2D>

namespace constants {

constexpr float kScreenScalingFactor = 0.85;

constexpr uint64_t kTickTime = 15;
constexpr uint64_t kSingleShotTime = 200;

constexpr float kCorrectionPercent = 0.2;
constexpr float kCorrectionSlope = 0.2;

constexpr QVector2D kMaxGameCoordinates(1.6, 0.9);

constexpr QVector2D kVerticalDoorSize(0.2, 0.5);
constexpr QVector2D kTopDoorSize(0.3, 0.4);
constexpr QVector2D kBottomDoorSize(0.3, 0.2);

constexpr QVector2D kTopDoorCoordinates
    (0, kMaxGameCoordinates.y() - kTopDoorSize.y() / 2);
constexpr QVector2D kRightDoorCoordinates
    (kMaxGameCoordinates.x() - kVerticalDoorSize.x() / 2, 0);

constexpr QVector2D kBottomDoorCoordinates(0, -kMaxGameCoordinates.y() + 0.1);
constexpr QVector2D kLeftDoorCoordinates(-kRightDoorCoordinates);

constexpr QVector2D kPosToMovePlayerTop
    (kBottomDoorCoordinates + kBottomDoorSize / 2 + QVector2D(0, 0.11));
constexpr QVector2D kPosToMovePlayerBottom
    (kTopDoorCoordinates - kTopDoorSize / 2 - QVector2D(0, 0.11));

constexpr QVector2D
    kPosToMovePlayerLeft(kRightDoorCoordinates - QVector2D(0.2, 0));
constexpr QVector2D
    kPosToMovePlayerRight(kLeftDoorCoordinates + QVector2D(0.2, 0));

constexpr QVector2D kVerticalWallSize(0.5, 2 * kMaxGameCoordinates.y());
constexpr QVector2D kHorizontalWallSize(2 * kMaxGameCoordinates.x(), 0.5);

constexpr QVector2D kTopWallCoordinates
    (0, kMaxGameCoordinates.y() + kHorizontalWallSize.y() / 2 - 0.2);
constexpr QVector2D kRightWallCoordinates
    (kMaxGameCoordinates.x() + kVerticalWallSize.x() / 2, 0);

constexpr QVector2D kBottomWallCoordinates{
    0, -kMaxGameCoordinates.y() - kHorizontalWallSize.y() / 2};
constexpr QVector2D kLeftWallCoordinates(-kRightWallCoordinates);

constexpr int32_t kMapVerticalSize = 5;
constexpr int32_t kMapHorizontalSize = 5;

constexpr float kSafeDistance = 0.1;
constexpr float kSafeAngleCosine = 0.3;
constexpr float kDegreeOfAvoidance = 400;

constexpr QVector2D kArtifactSize(0.1, 0.1);
constexpr QVector2D kMinArtifactCoordinates(
    kLeftWallCoordinates.x() + kVerticalWallSize.x() / 2 + kCorrectionSlope,
    kBottomWallCoordinates.y() + kHorizontalWallSize.y() / 2
        + kCorrectionSlope);
constexpr QVector2D kMaxArtifactCoordinates(
    kRightWallCoordinates.x() - kVerticalWallSize.x() / 2 - kCorrectionSlope,
    kTopWallCoordinates.y() - kHorizontalWallSize.y() / 2 - kCorrectionSlope);

constexpr int32_t kEasyRoomMaxDist = 1;
constexpr int32_t kMediumRoomMaxDist = 30;

constexpr int32_t kMaxBuffTime = 6000;
constexpr int32_t kEnemyCoolDown = 1000;

constexpr int32_t kTrySpawnArtifactPeriod = 20;
constexpr int32_t kInvArtifactSpawnChance = 100;
constexpr int32_t kMaxArtifactExistingTime = 3000;

constexpr int32_t kFireballMaxNumOfWallHits = 4;

constexpr int32_t kWinTimeInterval = 1'000;

constexpr int32_t kHealingPotionHealthIncrement = 7;

}  // namespace constants
