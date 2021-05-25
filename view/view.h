#pragma once

#include <memory>

#include <QWidget>
#include <QStackedWidget>
#include <QResizeEvent>

#include "core/scene.h"

#include "view/widgets/game_widget.h"
#include "view/widgets/game_menu.h"
#include "view/widgets/main_menu.h"
#include "view/buttons/menu_button.h"
#include "view/widgets/settings_menu.h"
#include "view/abstract_controller.h"
#include "view/widgets/losing_widget.h"
#include "view/widgets/winning_widget.h"
#include "utilities/cache.h"

class View : public QStackedWidget {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);

  void StartNewGame();
  void StartGame();
  void PauseGame();
  void ContinueGame();
  void StopGame();
  void ChangeSoundState(Language current_language);
  void ChangeLanguage(Language language);

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

  std::unique_ptr<MediaPlayer> media_player_;
  std::unique_ptr<Cache> cache_;

  GameWidget* game_widget_;
  GameMenu* game_menu_;
  MainMenu* main_menu_;
  SettingsMenu* settings_menu_;
  LosingWidget* losing_widget_;
  WinningWidget* winning_widget_;
};
