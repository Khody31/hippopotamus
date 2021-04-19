#include "game_menu.h"

GameMenuWidget::GameMenuWidget(QWidget* parent,
                               AbstractController* controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  ConnectButtons();
}

void GameMenuWidget::ResumeButtonPressEvent() {
  controller_->ContinueGame();
}

void GameMenuWidget::RestartButtonPressEvent() {
  controller_->StopGame();
  controller_->StartGame();
}

void GameMenuWidget::ToMainMenuButtonPressEvent() {
  controller_->OpenMainMenu();
}

void GameMenuWidget::SoundButtonPressEvent() {
  // TODO
}

void GameMenuWidget::CreateButtons() {
  resume_button_ = new MenuButton(tr("RESUME"), this, QRect(35, 20, 30, 10));
  restart_button_ = new MenuButton(tr("RESTART"), this, QRect(35, 35, 30, 10));
  sound_button_ = new MenuButton(tr("SOUND"), this, QRect(35, 50, 30, 10));
  to_main_menu_button_ = new MenuButton(tr("TO MAIN MENU"), this, QRect(35,
                                                                        65,
                                                                        30,
                                                                        10));
}

void GameMenuWidget::ConnectButtons() {
  connect(restart_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::RestartButtonPressEvent);
  connect(resume_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::ResumeButtonPressEvent);
  connect(sound_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::SoundButtonPressEvent);
  connect(to_main_menu_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::ToMainMenuButtonPressEvent);
}

void GameMenuWidget::Resize(QSize size) {
  restart_button_->setGeometry(restart_button_->CalculateActualPos(size));
  resume_button_->setGeometry(resume_button_->CalculateActualPos(size));
  sound_button_->setGeometry(sound_button_->CalculateActualPos(size));
  to_main_menu_button_->setGeometry(to_main_menu_button_->CalculateActualPos
      (size));
}
