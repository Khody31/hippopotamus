#include "game.h"

GameWidget::GameWidget(QWidget *parent, AbstractController *controller) :
    QWidget(parent) {
  controller_ = controller;
  game_scene_ = new QWidget(this);
  CreateButtons();
  Arrangement();
  ConnectButtons();
}

void GameWidget::MenuButtonPressEvent() {
  controller_->OpenGameMenu();
}

void GameWidget::PauseButtonPressEvent() {
controller_->PauseGame();
}

void GameWidget::CreateButtons() {
  menu_ = new MenuButton(tr("MENU"), this);
  pause_ = new MenuButton(tr("PAUSE"), this);
}

void GameWidget::ConnectButtons() {
  connect(menu_, &::QPushButton::clicked, this,
          &::GameWidget::MenuButtonPressEvent);
  connect(pause_, &::QPushButton::clicked, this,
          &::GameWidget::PauseButtonPressEvent);
}

void GameWidget::Arrangement() {
 // temp
 QVBoxLayout* layout = new QVBoxLayout(this);
 layout->addWidget(menu_);
 layout->addWidget(pause_);
 setLayout(layout);
}

