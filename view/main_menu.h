#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"
#include "abstract_controller.h"

class MainMenuWidget : public QWidget {
 public:
  MainMenuWidget(QWidget* parent, AbstractController* controller);
  void Resize(QSize size);

 private:
  void CreateButtons();
  void ConnectButtons();
  void LoadButtonPressEvent();
  void NewGameButtonPressEvent();
  void SettingsButtonPressEvent();
  void ExitButtonPressEvent();

  MenuButton* load_game_button_;
  MenuButton* new_game_button_;
  MenuButton* settings_button_;
  MenuButton* exit_button_;
  AbstractController* controller_;
};
