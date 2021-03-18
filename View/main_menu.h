#ifndef HIPPOPOTAMUS_MAIN_MENU_H
#define HIPPOPOTAMUS_MAIN_MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include "menu_button.h"
#include "abstract_controller.h"


class MainMenuWidget: public QWidget {
 public:
  MainMenuWidget(QWidget* parent, AbstractController* controller);
  void StartButtonPressEvent();
  void SettingsButtonPressEvent();
  void ExitButtonPressEvent();
 private:
  MenuButton* start_game_button_;
  MenuButton* settings_button_;
  MenuButton* exit_button_;
  AbstractController* controller_;
  QVBoxLayout* layout_;
  void  CreateButtons();
  void ConnectButtons();
  void LayoutPart();
};

#endif //HIPPOPOTAMUS_MAIN_MENU_H
