#include "button_controller.h"

ButtonController::ButtonController() : view(new View(this)) {
  view->setFocus();
  view->show();
}

void ButtonController::OpenSettings() {
  view->SwitchToSettings();
}

void ButtonController::Close() {
  view->close();
}

void ButtonController::OpenMainMenu() {
  if (is_game_on_) {
    is_game_on_ = false;
    StopGame();
  }
  view->SwitchToMainMenu();
}

void ButtonController::StartGame() {
  is_game_on_ = true;
  view->StartGame();
  view->SwitchToGame();
}

void ButtonController::ContinueGame() {
  view->SwitchToGame();
  view->ContinueGame();
}

void ButtonController::StopGame() {
  is_game_on_ = false;
  view->StopGame();
}

void ButtonController::PauseGame() {
  view->PauseGame();
}

void ButtonController::OpenGameMenu() {
  PauseGame();
  view->SwitchToGameMenu();
}
