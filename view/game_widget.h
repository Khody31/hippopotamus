#pragma once

#include <memory>

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "core/scene.h"
#include "core/connector.h"

#include "menu_button.h"
#include "abstract_controller.h"
#include "custom_widget.h"

class GameWidget : public CustomWidget {
 public:
  GameWidget(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;

  void Continue();
  void Pause();
  void Start();
  void Stop();
  void StartNewGame();

  void OnKeyPress(QKeyEvent* event);
  void OnKeyRelease(QKeyEvent* event);

 private:
  void keyPressEvent(QKeyEvent* event) override;

  std::shared_ptr<Connector> connector_;
};
