#pragma once

#include <QPainter>
#include <QMouseEvent>
#include <set>
#include <memory>

#include "engine/coordinator.h"
#include "systems/transformation_system.h"
#include "systems/render_system.h"
#include "systems/bullet_system.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();

  void OnTick();
  void SetScene(QWidget* scene);

  void MouseClick(QMouseEvent* event);

  QVector2D WidgetToGameCoordinates(QPoint point);

  const PixmapComponent& GetPixmapComponent(Entity entity);
  const std::set<Entity>& GetEntitiesToRender();

 private:
  void RegisterComponents();
  void RegisterSystems();
  void CreatePlayer();

  Coordinator game_coordinator_;

  std::shared_ptr<TransformationSystem> tr_system_;
  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<BulletSystem> bullet_system;

  QWidget* scene_;
};
