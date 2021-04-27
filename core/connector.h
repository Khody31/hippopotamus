#pragma once

#include <QPainter>
#include <memory>
#include <systems/joystick_system.h>
#include <systems/movement_system.h>

#include "engine/coordinator.h"
#include "systems/render_system.h"
#include "systems/collision_system.h"
#include "components/components.h"
#include "keyboard_interface.h"

// connecting link between engine and game
class Connector {
 public:
  Connector();

  void OnTick();
  void SetScene(GameScene* scene);

  void OnKeyPress(Qt::Key key);
  void OnKeyRelease(Qt::Key key);

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

  GameScene* scene_;

  KeyboardInterface keyboard_interface_;

  friend class GameScene;
  friend class Functions;
};
