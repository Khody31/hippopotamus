#pragma once

#include <memory>
#include <set>

#include <QMouseEvent>

#include "spawner.h"
#include "keyboard_interface.h"
#include "room.h"


#include "systems/joystick_system.h"
#include "systems/collision_system.h"
#include "systems/movement_system.h"
#include "systems/render_system.h"
#include "systems/serialization_system.h"

#include "components/components.h"
#include "engine/coordinator.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();

  void OnTick();

  void SetScene(GameScene* scene);

  const PixmapComponent& GetPixmapComponent(Entity entity);
  const TransformationComponent& GetTransformComponent(Entity entity);
  const std::set<Entity>& GetEntitiesToRender() const;

  void OnKeyPress(Qt::Key key);
  void OnKeyRelease(Qt::Key key);
  void OnMousePress(QMouseEvent* event);

  void SetPlayer(Entity player);

  void ChangeRoom(int id);
 private:
  void RegisterComponents();
  void RegisterSystems();

  Coordinator coordinator_;
  GameScene* scene_;
  std::shared_ptr<Spawner> spawner_;
  Entity player_;

  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<CollisionSystem> collision_system_;
  std::shared_ptr<JoystickSystem> joystick_system_;
  std::shared_ptr<MovementSystem> movement_system_;
  std::shared_ptr<SerializationSystem> serialization_system;

  KeyboardInterface keyboard_interface_;
  int current_room_id_ = 1;
};
