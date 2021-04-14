#pragma once

#include <set>

#include "engine/coordinator.h"

class RenderSystem : public System {
 public:
  void Update(Coordinator* game_coordinator) override;
  const std::set<Entity>& GetEntities();
  void SetScene(QWidget* scene);
 private:
  QPoint GameToWidgetCoordinates(const QVector2D& coord, int width, int height);
  QWidget* scene_;
};
