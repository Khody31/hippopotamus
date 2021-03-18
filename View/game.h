#ifndef HIPPOPOTAMUS_GAME_H
#define HIPPOPOTAMUS_GAME_H

#include <QWidget>
#include <QVBoxLayout>
#include "menu_button.h"
#include "abstract_controller.h"

class GameWidget: public QWidget {
 public:
  GameWidget(QWidget* parent, AbstractController* controller);
  void MenuButtonPressEvent();
  void PauseButtonPressEvent();
 private:
  QWidget* game_scene_;
  MenuButton* menu_;
  MenuButton* pause_;
  AbstractController* controller_;
  void CreateButtons();
  void ConnectButtons();
  void Arrangement();
};


#endif //HIPPOPOTAMUS_GAME_H
