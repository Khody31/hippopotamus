#ifndef HIPPOPOTAMUS_GAME_H
#define HIPPOPOTAMUS_GAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "menu_button.h"
#include "abstract_controller.h"
#include "core/game_scene.h"
#include "core/connector.h"

class GameWidget : public QWidget {
 public:
  GameWidget(AbstractController* controller, QWidget* parent);
  void Resize(QSize size);
  void keyPressEvent(QKeyEvent* event);

  void Continue();
  void Pause();
  void Start();
  void Stop();
 private:
  std::shared_ptr<GameScene> game_scene_;
  std::shared_ptr<Connector> connector_;
  AbstractController* controller_;
};

#endif //HIPPOPOTAMUS_GAME_H
