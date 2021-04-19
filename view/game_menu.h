#ifndef HIPPOPOTAMUS_GAME_MENU_H
#define HIPPOPOTAMUS_GAME_MENU_H

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"
#include "abstract_controller.h"

class GameMenuWidget : public QWidget {
 public:
  GameMenuWidget(QWidget* parent, AbstractController* controller);
  void ResumeButtonPressEvent();
  void RestartButtonPressEvent();
  void SoundButtonPressEvent();
  void ToMainMenuButtonPressEvent();
  void Resize(QSize size);
 private:
  void CreateButtons();
  void ConnectButtons();

  MenuButton* resume_button_;
  MenuButton* restart_button_;
  MenuButton* sound_button_;
  MenuButton* to_main_menu_button_;
  AbstractController* controller_;
};

#endif //HIPPOPOTAMUS_GAME_MENU_H
