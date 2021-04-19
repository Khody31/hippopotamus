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
  if (game_is_on_) {
    game_is_on_ = false;
    StopGame();
  }
  view->SwitchToMainMenu();
}

void ButtonController::StartGame() {
  game_is_on_ = true;
  view->StartGame();
  view->SwitchToGame();
}

void ButtonController::ContinueGame() {
  view->SwitchToGame();
  view->ContinueGame();
}

void ButtonController::StopGame() {
  game_is_on_ = false;
  view->StopGame();
}

void ButtonController::PauseGame() {
  view->PauseGame();
}

void ButtonController::OpenGameMenu() {
  PauseGame();
  view->SwitchToGameMenu();
}
