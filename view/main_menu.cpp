#include "main_menu.h"

MainMenuWidget::MainMenuWidget(QWidget* parent,
                               AbstractController* controller) : QWidget
                                                                     (parent) {
  controller_ = controller;
  CreateButtons();
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
  start_game_button_ = new MenuButton(tr("START GAME"), this, QRect(35, 20,
                                                                    30, 10));
  settings_button_ = new MenuButton(tr("SETTINGS"), this, QRect(35, 35, 30,
                                                                10));
  exit_button_ = new MenuButton(tr("EXIT"), this, QRect(35, 50, 30, 10));
}

void MainMenuWidget::ConnectButtons() {
  connect(start_game_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::StartButtonPressEvent);
  connect(settings_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::SettingsButtonPressEvent);
  connect(exit_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::ExitButtonPressEvent);
}

void MainMenuWidget::Resize(QSize size) {
  start_game_button_->setGeometry(start_game_button_->CalculateActualPos(size));
  settings_button_->setGeometry(settings_button_->CalculateActualPos(size));
  exit_button_->setGeometry(exit_button_->CalculateActualPos(size));
}
