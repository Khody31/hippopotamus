#pragma once

#include <QMouseEvent>
#include <unordered_set>
#include <memory>
#include <view/abstract_controller.h>

#include "spawner.h"
#include "keyboard_interface.h"

#include "systems/joystick_system.h"
#include "systems/collision_system.h"
#include "systems/movement_system.h"
#include "systems/render_system.h"
#include "systems/serialization_system.h"
#include "systems/death_system.h"

// connecting link between engine and game
class Connector {
 public:
  explicit Connector(QWidget* parent, AbstractController* controller);

  void OnTick();

  const PixmapComponent& GetPixmapComponent(Entity entity);
  const TransformationComponent& GetTransformComponent(Entity entity);
  const std::unordered_set<Entity>& GetEntitiesToRender() const;

  void OnKeyPress(Qt::Key key);
  void OnKeyRelease(Qt::Key key);
  void OnMousePress(QMouseEvent* event);

  void StartNewGame();
  void LoadGame();
  void ChangeRoom(const DoorComponent& component);

  Scene* GetScene();

 private:
  void RegisterComponents();
  void RegisterSystems();

  std::unique_ptr<Scene> scene_;
  std::unique_ptr<Coordinator> coordinator_;
  std::unique_ptr<Spawner> spawner_;
  std::unique_ptr<KeyboardInterface> keyboard_;
  std::unique_ptr<Entity> player_;

  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<CollisionSystem> collision_system_;
  std::shared_ptr<JoystickSystem> joystick_system_;
  std::shared_ptr<MovementSystem> movement_system_;
  std::shared_ptr<SerializationSystem> serialization_system_;
  std::shared_ptr<DeathSystem> death_system_;
};
