#pragma once

#include <set>

#include "engine/coordinator.h"
#include "components/components.h"

class RenderSystem : public System {
 public:
  void Update(Coordinator* game_coordinator);
  const std::set<Entity>& GetEntities();
  void SetScene(QWidget* scene);

 private:
  static QPoint GameToWidgetCoordinates(const QVector2D& coord, int width, int height);

  QWidget* scene_;
};
