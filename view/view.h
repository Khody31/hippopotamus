#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QResizeEvent>

#include "game_widget.h"
#include "game_menu.h"
#include "main_menu.h"
#include "menu_button.h"
#include "settings_menu.h"
#include "abstract_controller.h"
#include "core/scene.h"
#include "losing_widget.h"
#include "winning_widget.h"


class View : public QStackedWidget {
 public:
  explicit View(AbstractController* controller);

  void StartNewGame();
  void StartGame();
  void PauseGame();
  void ContinueGame();
  void StopGame();

  void SwitchToGame();
  void SwitchToGameMenu();
  void SwitchToMainMenu();
  void SwitchToSettings();
  void SwitchToLosingWidget();
  void SwitchToWinningWidget();

  void OnKeyPress(QKeyEvent* event);
  void OnKeyRelease(QKeyEvent* event);

 private:
  void resizeEvent(QResizeEvent* event) override;

  GameWidget* game_widget_;
  GameMenu* game_menu_;
  MainMenu* main_menu_;
  SettingsMenu* settings_menu_;
  LosingWidget* losing_widget_;
  WinningWidget* winning_widget_;

};
