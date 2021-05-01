#pragma once

#include <QPainter>
#include <QMouseEvent>

#include <unordered_set>
#include <memory>

#include "systems/joystick_system.h"
#include "systems/movement_system.h"
#include "core/spawner.h"
#include "engine/coordinator.h"
#include "systems/render_system.h"
#include "systems/collision_system.h"
#include "components/components.h"
#include "keyboard_interface.h"
#include "mouse_interface.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();

  void OnTick();

  void SetScene(GameScene* scene);

  const PixmapComponent& GetPixmapComponent(Entity entity);
  const TransformationComponent& GetTransformComponent(Entity entity);
  const std::unordered_set<Entity>& GetEntitiesToRender() const;

  void OnKeyPress(Qt::Key key);
  void OnKeyRelease(Qt::Key key);
  void OnMousePress(QMouseEvent* event);

 private:
  void RegisterComponents();
  void RegisterSystems();
  void CreatePlayer();

  Coordinator coordinator_;
  GameScene* scene_;
  std::shared_ptr<Spawner> spawner_;

  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<CollisionSystem> collision_system_;
  std::shared_ptr<JoystickSystem> joystick_system_;
  std::shared_ptr<MovementSystem> movement_system_;

  KeyboardInterface keyboard_interface_;
  MouseInterface mouse_interface_;
};
