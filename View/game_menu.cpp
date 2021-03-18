#include "game_menu.h"

GameMenuWidget::GameMenuWidget(QWidget *parent,
                               AbstractController *controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  LayoutPart();
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
 resume_button_ = new MenuButton(tr("RESUME"), this);
 restart_button_ = new MenuButton(tr("RESTART"), this);
 sound_button_ = new MenuButton(tr("SOUND"), this);
 to_main_menu_button_ = new MenuButton(tr("TO MAIN MENU"), this);
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
void GameMenuWidget::LayoutPart() {
  layout_ = new QVBoxLayout(this);
  layout_->addWidget(resume_button_);
  layout_->addWidget(restart_button_);
  layout_->addWidget(sound_button_);
  layout_->addWidget(to_main_menu_button_);
  setLayout(layout_);
}
