#pragma once

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

class View : public QStackedWidget {
 public:
  explicit View(AbstractController* controller);
  void SwitchToGame();
  void SwitchToGameMenu();
  void SwitchToMainMenu();
  void SwitchToSettings();
  void ContinueGame();
  void PauseGame();
  void StartGame();
  void StopGame();

  void OnKeyPress(QKeyEvent* event);
  void OnKeyRelease(QKeyEvent* event);

  friend class AbstractController;
 private:
  void resizeEvent(QResizeEvent* event) override;
  void AddWidgets();

  GameWidget* game_;
  GameMenuWidget* game_menu_;
  MainMenuWidget* main_menu_;
  SettingsWidget* settings_;
};
