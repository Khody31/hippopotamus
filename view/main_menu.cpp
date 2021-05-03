#include "main_menu.h"
#include "constants.h"

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
  start_game_button_ = new MenuButton(tr("START GAME"), this,
                                      menu_constants::kStartGameButton);
  settings_button_ =
      new MenuButton(tr("SETTINGS"), this, menu_constants::kSettingsButton);
  exit_button_ = new MenuButton(tr("EXIT"), this, menu_constants::kExitButton);
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
