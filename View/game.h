#ifndef HIPPOPOTAMUS_GAME_H
#define HIPPOPOTAMUS_GAME_H

#include <QWidget>
#include "menu_button.h"
#include "abstract_controller.h"

class GameWidget: public QWidget {
 public:
  GameWidget(QWidget* parent, AbstractController* controller);
 private:
  QWidget game_scene_;
  MenuButton* menu_;
  MenuButton* pause_;
  AbstractController* controller_;
};


#endif //HIPPOPOTAMUS_GAME_H
