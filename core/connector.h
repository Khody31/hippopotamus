#pragma once

#include <QPainter>
#include <set>
#include <memory>

#include "engine/coordinator.h"
#include "systems/render_system.h"
#include "systems/collision_system.h"
#include "systems/joystick_system.h"
#include "systems/movement_system.h"
#include "systems/serialization_system.h"
#include "components/components.h"
#include "keyboard_interface.h"
#include "room.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();

  void OnTick();
  void SetScene(QWidget* scene);

  const PixmapComponent& GetPixmapComponent(Entity entity);
  const std::set<Entity>& GetEntitiesToRender();

  void OnKeyPress(Qt::Key key);
  void OnKeyRelease(Qt::Key key);

  void ChangeRoom(int id);
 private:
  void RegisterComponents();
  void RegisterSystems();
  void CreatePlayer();
  void CreateBall();
  void CreateWall();

  Coordinator coordinator_;
  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<CollisionSystem> collision_system_;
  std::shared_ptr<JoystickSystem> joystick_system_;
  std::shared_ptr<MovementSystem> movement_system_;
  std::shared_ptr<SerializationSystem> serialization_system;

  KeyboardInterface keyboard_interface_;
  int current_room_id_;
};
