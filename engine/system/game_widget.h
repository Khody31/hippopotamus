#pragma  once

#include <QWidget>

#include "abstract_mouse_listener.h"
#include "abstract_keyboard_listener.h"
#include "engine/misc/constants.h"
#include "keyboard_interface.h"

class GameWidget : public QWidget {
 public:
  GameWidget(const GameWidget&) = delete;
  void operator=(const GameWidget&) = delete;

  static GameWidget& Get();

  void SetMouseListener(AbstractMouseListener*);
  void SetSceneWidget(QWidget*);

 private:
  GameWidget() = default;

  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void mousePressEvent(QMouseEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void resizeEvent(QResizeEvent*) override;

  AbstractMouseListener* mouse_listener_{nullptr};
  AbstractKeyboardListener* keyboard_listener_{nullptr};

  QWidget* scene_widget_{nullptr};
};
