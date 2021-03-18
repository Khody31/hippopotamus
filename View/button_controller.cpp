#include "button_controller.h"


ButtonController::ButtonController() {
 view = new View(this);
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
  if(game_is_on_) {
    game_is_on_ = false;
    StopGame();
  }
 view->SwitchToMainMenu();
}

void ButtonController::StartGame() {
  game_is_on_ = true;
  game_is_on_pause_ = false;
  view->SwitchToGame();
  // TODO
}

void ButtonController::ContinueGame() {
  game_is_on_pause_ = false;
  view->SwitchToGame();
    // TODO
}

void ButtonController::StopGame() {
  game_is_on_ = false;
  // TODO
}

void ButtonController::PauseGame() {
  game_is_on_pause_ = true;
 // TODO
}

void ButtonController::OpenGameMenu() {
  PauseGame();
  view->SwitchToGameMenu();
}
