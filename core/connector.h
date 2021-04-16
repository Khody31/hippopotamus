#pragma once

#include <QPainter>
#include <set>
#include <memory>

#include "engine/coordinator.h"
#include "systems/transformation_system.h"
#include "systems/render_system.h"
#include "systems/collision_system.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();

  void OnTick();
  void SetScene(QWidget* scene);

  const PixmapComponent& GetPixmapComponent(Entity entity);
  const std::set<Entity>& GetEntitiesToRender();

 private:
  void RegisterComponents();
  void RegisterSystems();
  void CreatePlayer();

  Coordinator game_coordinator_;
  std::shared_ptr<TransformationSystem> tr_system_;
  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<CollisionSystem> collision_system_;
  QWidget* scene_;
};
