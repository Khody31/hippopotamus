#include "main_menu.h"
#include "constants.h"

MainMenuWidget::MainMenuWidget(QWidget* parent,
                               AbstractController* controller) : QWidget
                                                                     (parent) {
  controller_ = controller;
  CreateButtons();
  ConnectButtons();
}

void MainMenuWidget::LoadButtonPressEvent() {
  controller_->LoadGame();
}

void MainMenuWidget::SettingsButtonPressEvent() {
  controller_->OpenSettings();
}

void MainMenuWidget::ExitButtonPressEvent() {
  controller_->Close();
}

void MainMenuWidget::NewGameButtonPressEvent() {
  controller_->StartNewGame();
}

void MainMenuWidget::CreateButtons() {
  new_game_button_ = new MenuButton(tr("NEW GAME"), this,
                                    menu_constants::kNewGameButton);
  load_game_button_ = new MenuButton(tr("LOAD GAME"), this,
                                     menu_constants::kLoadGameButton);
  settings_button_ =
      new MenuButton(tr("SETTINGS"), this, menu_constants::kSettingsButton);
  exit_button_ = new MenuButton(tr("EXIT"), this, menu_constants::kExitButton);
}

void MainMenuWidget::ConnectButtons() {
  connect(new_game_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::NewGameButtonPressEvent);
  connect(load_game_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::LoadButtonPressEvent);
  connect(settings_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::SettingsButtonPressEvent);
  connect(exit_button_, &::QPushButton::clicked, this,
          &::MainMenuWidget::ExitButtonPressEvent);
}

void MainMenuWidget::Resize(QSize size) {
  new_game_button_->setGeometry(new_game_button_->CalculateActualPos(size));
  load_game_button_->setGeometry(load_game_button_->CalculateActualPos(size));
  settings_button_->setGeometry(settings_button_->CalculateActualPos(size));
  exit_button_->setGeometry(exit_button_->CalculateActualPos(size));
}
