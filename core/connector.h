#pragma once

#include <QPainter>
#include <set>
#include <memory>
#include <systems/joystick_system.h>
#include <systems/movement_system.h>

#include "engine/coordinator.h"
#include "systems/render_system.h"
#include "components/components.h"
#include "keyboard_interface.h"

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

 private:
  void RegisterComponents();
  void RegisterSystems();
  void CreatePlayer();

  Coordinator coordinator_;
  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<JoystickSystem> joystick_system_;
  std::shared_ptr<MovementSystem> movement_system_;

  KeyboardInterface keyboard_interface_;
};
