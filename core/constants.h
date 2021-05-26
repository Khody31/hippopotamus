#pragma once

#include <QVector2D>

namespace constants {

constexpr float kScreenScalingFactor = 0.85;

constexpr uint64_t kTickTime = 15;
constexpr uint64_t kSingleShotTime = 200;

constexpr float kCorrectionPercent = 0.2;
constexpr float kCorrectionSlope = 0.2;

constexpr QVector2D kMaxGameCoordinates(1.6, 0.9);

constexpr QVector2D kVerticalDoorSize(0.15, 0.65);
constexpr QVector2D kTopDoorPixmapSize(0.3, 0.45);
constexpr QVector2D kTopDoorColliderSize(0.3, 0.3);
constexpr QVector2D kBottomDoorSize(0.3, 0.15);

constexpr QVector2D kTopDoorCoordinates
    (0, kMaxGameCoordinates.y() - kTopDoorPixmapSize.y() / 2);
constexpr QVector2D kRightDoorCoordinates
    (kMaxGameCoordinates.x() - kVerticalDoorSize.x() / 2, 0);

constexpr QVector2D kBottomDoorCoordinates(0, -kMaxGameCoordinates.y() + 0.08);
constexpr QVector2D kLeftDoorCoordinates(-kRightDoorCoordinates);

constexpr QVector2D kPosToMovePlayerTop
    (0, kBottomDoorCoordinates.y() + kBottomDoorSize.y() / 2 + 0.11);
constexpr QVector2D kPosToMovePlayerBottom
    (0, kTopDoorCoordinates.y() - kTopDoorPixmapSize.y() / 2 - 0.11);

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

constexpr QVector2D kArtifactSize(0.15, 0.15);
constexpr QVector2D kMinArtifactCoordinates(
    kLeftWallCoordinates.x() + kVerticalWallSize.x() / 2 + kCorrectionSlope,
    kBottomWallCoordinates.y() + kHorizontalWallSize.y() / 2
        + kCorrectionSlope);
constexpr QVector2D kMaxArtifactCoordinates(
    kRightWallCoordinates.x() - kVerticalWallSize.x() / 2 - kCorrectionSlope,
    kTopWallCoordinates.y() - kHorizontalWallSize.y() / 2 - kCorrectionSlope);

constexpr int32_t kEasyRoomMaxDist = 15;
constexpr int32_t kMediumRoomMaxDist = 30;

constexpr int32_t kMaxBuffTime = 6000;
constexpr int32_t kEnemyCoolDown = 1000;

constexpr int32_t kTrySpawnArtifactPeriod = 20;
constexpr int32_t kInvArtifactSpawnChance = 200;
constexpr int32_t kMaxArtifactExistingTime = 3000;

constexpr int32_t kFireballMaxNumOfWallHits = 4;

constexpr int32_t kWinTimeInterval = 2000;

constexpr int32_t kHealingPotionHealthIncrement = 150;

constexpr QVector2D kPilePixmapSize(0.45, 0.45);
constexpr QVector2D kPileColliderSize(0.2, 0.2);

constexpr QVector2D kTotemPixmapSize{0.25, 0.49};
constexpr QVector2D kTotemColliderSize{0.1, 0.3};

}  // namespace constants
