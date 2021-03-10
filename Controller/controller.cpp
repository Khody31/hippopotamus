#include "controller.h"
Controller::Controller() : AbstractController() {
  view_ptr_ = std::make_unique<View>(this);
  model_ptr_ = std::make_unique<Model>();
}

void Controller::LoadRoom() {

}

void Controller::StartGame() {
  view_ptr_->ShowGame();
}

void Controller::EndGame() {

}

void Controller::OnTick() {

}

void Controller::LoadMainMenu() {
  view_ptr_->ShowMainMenu();
}

void Controller::LoadSettings() {
  view_ptr_->ShowSettings();
}
