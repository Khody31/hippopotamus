#include "game.h"
#include <iostream>

GameWidget::GameWidget(QWidget *parent, AbstractController *controller) :
    QWidget(parent) {
  controller_ = controller;
  game_scene_ = new QWidget(this);
  CreateButtons();
  ConnectButtons();
}

void GameWidget::MenuButtonPressEvent() {
  controller_->OpenGameMenu();
}

void GameWidget::PauseButtonPressEvent() {
controller_->PauseGame();
}

void GameWidget::CreateButtons() {
  menu_ = new MenuButton(tr("MENU"), this, QRect(90, 0, 10, 10));
  pause_ = new MenuButton(tr("PAUSE"), this, QRect(40, 0, 20, 10));
}

void GameWidget::ConnectButtons() {
  connect(menu_, &::QPushButton::clicked, this,
          &::GameWidget::MenuButtonPressEvent);
  connect(pause_, &::QPushButton::clicked, this,
          &::GameWidget::PauseButtonPressEvent);
}

void GameWidget::Resize(QSize size) {
 menu_->setGeometry(menu_->CalculateActualPos(size));
 pause_->setGeometry(pause_->CalculateActualPos(size));
}

