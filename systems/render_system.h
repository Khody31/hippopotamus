#pragma once

#include <unordered_set>

#include "engine/coordinator.h"
#include "components/components.h"

class RenderSystem : public System {
 public:
  RenderSystem();

  void Update(Coordinator* game_coordinator);
  const std::unordered_set<Entity>& GetEntities();
  void SetScene(QWidget* scene);

 private:
  QPoint GameToWidgetCoordinates(const QVector2D& coord);

  QWidget* scene_;
};
