#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <memory>

#include "menu_button.h"
#include "abstract_controller.h"
#include "core/game_scene.h"
#include "core/connector.h"

class GameWidget : public QWidget {
 public:
  GameWidget(QWidget* parent, AbstractController* controller);
  void Resize(QSize size);
  void Continue();
  void Pause();
  void Start();
  void Stop();

  void OnKeyPress(QKeyEvent* event);
  void OnKeyRelease(QKeyEvent* event);
 private:
  void keyPressEvent(QKeyEvent* event) override;

  std::shared_ptr<GameScene> game_scene_;
  std::shared_ptr<Connector> connector_;
  std::shared_ptr<AbstractController> controller_;
};
