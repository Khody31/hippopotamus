#ifndef HIPPOPOTAMUS_VIEW_H
#define HIPPOPOTAMUS_VIEW_H

#include <QWidget>
#include <QStackedWidget>
#include <QResizeEvent>

#include "game.h"
#include "game_menu.h"
#include "main_menu.h"
#include "menu_button.h"
#include "settings.h"
#include "abstract_controller.h"
#include "core/game_scene.h"

class View: public QWidget {
 public:
  explicit View(AbstractController* controller);
  void SwitchToGame();
  void SwitchToGameMenu();
  void SwitchToMainMenu();
  void SwitchToSettings();
  void resizeEvent(QResizeEvent* event) override;
  void ContinueGame();
  void PauseGame();
  void StartGame();
  void StopGame();

  friend class AbstractController;
 private:
  QStackedWidget* switcher_;
  GameWidget* game_;
  GameMenuWidget* game_menu_;
  MainMenuWidget* main_menu_;
  SettingsWidget* settings_;
  AbstractController* controller_;
};

#endif //HIPPOPOTAMUS_VIEW_H
