#include "view.h"

View::View(AbstractController* controller) :
    game_widget_(new GameWidget(controller, this)),
    game_menu_(new GameMenu(controller, this)),
    main_menu_(new MainMenu(controller, this)),
    settings_menu_(new SettingsMenu(controller, this)) {

  addWidget(main_menu_);
  addWidget(settings_menu_);
  addWidget(game_widget_);
  addWidget(game_menu_);

  SwitchToMainMenu();
  resize(1600, 900);
}

void View::SwitchToGame() {
  setCurrentWidget(game_widget_);
}

void View::SwitchToGameMenu() {
  setCurrentWidget(game_menu_);
}

void View::SwitchToMainMenu() {
  setCurrentWidget(main_menu_);
}

void View::SwitchToSettings() {
  setCurrentWidget(settings_menu_);
}

void View::resizeEvent(QResizeEvent* event) {
  QSize new_size = size();
  resize(new_size);
  game_widget_->Resize(new_size);
  game_menu_->Resize(new_size);
  main_menu_->Resize(new_size);
  settings_menu_->Resize(new_size);
}

void View::ContinueGame() {
  game_widget_->Continue();
}

void View::PauseGame() {
  game_widget_->Pause();
}

void View::StartGame() {
  game_widget_->Start();
}

void View::StartNewGame() {
  game_widget_->StartNewGame();
}

void View::StopGame() {
  game_widget_->Stop();
}


void View::OnKeyPress(QKeyEvent* event) {
  game_widget_->OnKeyPress(event);
}

void View::OnKeyRelease(QKeyEvent* event) {
  game_widget_->OnKeyRelease(event);
}
