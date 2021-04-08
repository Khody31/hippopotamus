#pragma once

#include <QVector2D>

#include "Backbone/coordinator.h"

extern Coordinator game_coordinator;

class TransformationSystem : public System {
 public:
  void Update(const QVector2D& vec);
};