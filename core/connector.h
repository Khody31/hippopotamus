#pragma once

#include <QPainter>

#include "engine/coordinator.h"
#include "systems/transformation_system.h"
#include "systems/render_system.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();
  void OnTick();
  void Render(QPainter* painter, int width, int height);
 private:
  Coordinator game_coordinator_;
  std::shared_ptr<TransformationSystem> tr_system_;
  std::shared_ptr<RenderSystem> render_system_;
};