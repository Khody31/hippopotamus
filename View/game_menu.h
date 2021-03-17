#ifndef HIPPOPOTAMUS_GAME_MENU_H
#define HIPPOPOTAMUS_GAME_MENU_H

#include <QWidget>
#include "menu_button.h"
#include "abstract_controller.h"



class GameMenuWidget: public QWidget {
 public:
  GameMenuWidget(QWidget* parent, AbstractController* controller);
 private:
  QWidget resume_button_;
  MenuButton* restart_button_;
  MenuButton* sound_button_;
  MenuButton* to_main_menu_button_;
  AbstractController* controller_;
};



#endif //HIPPOPOTAMUS_GAME_MENU_H
