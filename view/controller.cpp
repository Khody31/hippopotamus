#include "view/controller.h"

Controller::Controller() : view(new View(this)) {
  view->setFocus();
  view->show();
}

void Controller::OpenSettings() {
  view->SwitchToSettings();
}

void Controller::Close() {
  view->close();
}

void Controller::OpenMainMenu() {
  if (is_game_on_) {
    is_game_on_ = false;
  }
  view->SwitchToMainMenu();
}

void Controller::LoadGame() {
  is_game_on_ = true;
  view->StartGame();
  view->SwitchToGame();
}

void Controller::ContinueGame() {
  view->SwitchToGame();
  view->ContinueGame();
}

void Controller::StopGame() {
  is_game_on_ = false;
  view->StopGame();
}

void Controller::PauseGame() {
  view->PauseGame();
}

void Controller::OpenGameMenu() {
  PauseGame();
  view->SwitchToGameMenu();
}

void Controller::OnKeyPress(QKeyEvent* event) {
  view->OnKeyPress(event);
}

void Controller::OnKeyRelease(QKeyEvent* event) {
  view->OnKeyRelease(event);
}

void Controller::StartNewGame() {
  view->StartNewGame();
  view->SwitchToGame();
}

void Controller::OpenWinningWidget() {
  view->SwitchToWinningWidget();
}

void Controller::OpenLosingWidget() {
  view->SwitchToLosingWidget();
}

void Controller::ChangeSoundState() {
  view->ChangeSoundState(language_);
  view->repaint();
}

void Controller::ChangeLanguage(Language language) {
  language_ = language;
  view->ChangeLanguage(language);
  view->repaint();
}
