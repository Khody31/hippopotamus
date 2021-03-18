#ifndef HIPPOPOTAMUS_VIEW_H
#define HIPPOPOTAMUS_VIEW_H

#include <QWidget>
#include <QStackedWidget>
#include "game.h"
#include "game_menu.h"
#include "main_menu.h"
#include "menu_button.h"
#include "settings.h"
#include "abstract_controller.h"

class View: public QWidget {
 public:
  explicit View(AbstractController* controller);
  void SwitchToGame();
  void SwitchToGameMenu();
  void SwitchToMainMenu();
  void SwitchToSettings();
  void resizeEvent(QResizeEvent *);
 private:
  QStackedWidget* switcher_;
  GameWidget* game_;
  GameMenuWidget* game_menu_;
  MainMenuWidget* main_menu_;
  SettingsWidget* settings_;
  AbstractController* controller_;
};

#endif //HIPPOPOTAMUS_VIEW_H
