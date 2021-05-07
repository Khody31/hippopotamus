#include "view.h"

View::View(AbstractController* controller) :
    game_(new GameWidget(this, controller)),
    game_menu_(new GameMenuWidget(this, controller)),
    main_menu_(new MainMenuWidget(this, controller)),
    settings_(new SettingsWidget(this, controller)),
    losing_widget_(new LosingWidget(this, controller)),
    winning_widget_(new WinningWidget(this, controller)) {
  AddWidgets();
  SwitchToMainMenu();
  resize(1600, 900);
}

void View::SwitchToGame() {
  setCurrentWidget(game_);
}

void View::SwitchToGameMenu() {
  setCurrentWidget(game_menu_);
}

void View::SwitchToMainMenu() {
  setCurrentWidget(main_menu_);
}

void View::SwitchToSettings() {
  setCurrentWidget(settings_);
}

void View::SwitchToLosingWidget() {
  setCurrentWidget(losing_widget_);
}

void View::SwitchToWinningWidget() {
  setCurrentWidget(winning_widget_);
}
void View::resizeEvent(QResizeEvent* event) {
  QSize new_size = size();
  resize(new_size);
  game_->Resize(new_size);
  game_menu_->Resize(new_size);
  main_menu_->Resize(new_size);
  settings_->Resize(new_size);
  losing_widget_->Resize(new_size);
  winning_widget_->Resize(new_size);
}

void View::ContinueGame() {
  game_->Continue();
}

void View::PauseGame() {
  game_->Pause();
}

void View::StartGame() {
  game_->Start();
}

void View::StartNewGame() {
  game_->StartNewGame();
}

void View::StopGame() {
  game_->Stop();
}

void View::AddWidgets() {
  addWidget(main_menu_);
  addWidget(settings_);
  addWidget(game_);
  addWidget(game_menu_);
  addWidget(losing_widget_);
  addWidget(winning_widget_);
}

void View::OnKeyPress(QKeyEvent* event) {
  game_->OnKeyPress(event);
}

void View::OnKeyRelease(QKeyEvent* event) {
  game_->OnKeyRelease(event);
}
