#pragma once

#include "engine/coordinator.h"

class RenderSystem : public System {
 public:
  void Update(Coordinator* game_coordinator) override;
  void Render(Coordinator* game_coordinator, QPainter* painter, int width, int height);
  QVector2D WidgetToGameCoordinates(const QPoint& coord, int width, int height);
  QPoint GameToWidgetCoordinates(const QVector2D& coord, int width, int height);
};