#include "main_menu.h"
#include <iostream>

MainMenuWidget::MainMenuWidget(QWidget *parent,
                               AbstractController *controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  LayoutPart();
  ConnectButtons();
}

void MainMenuWidget::StartButtonPressEvent() {
 controller_->StartGame();
}

void MainMenuWidget::SettingsButtonPressEvent() {
 controller_->OpenSettings();
}

void MainMenuWidget::ExitButtonPressEvent() {
 controller_->Close();
}

void MainMenuWidget::CreateButtons() {
  start_game_button_ = new MenuButton(tr("START GAME"), this);
  settings_button_ = new MenuButton(tr("SETTINGS"), this);
  exit_button_ = new MenuButton(tr("EXIT"), this);
}

void MainMenuWidget::ConnectButtons() {
  connect(start_game_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::StartButtonPressEvent);
  connect(settings_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::SettingsButtonPressEvent);
  connect(exit_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::ExitButtonPressEvent);
}
void MainMenuWidget::LayoutPart() {
 layout_ = new QVBoxLayout(this);
 layout_->addWidget(start_game_button_);
 layout_->addWidget(settings_button_);
 layout_->addWidget(exit_button_);
 setLayout(layout_);
}
