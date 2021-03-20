#include "game.h"
#include <iostream>

GameWidget::GameWidget(QWidget *parent, AbstractController *controller) :
    QWidget(parent) {
  controller_ = controller;
  game_scene_ = new QWidget(this);
}

void GameWidget::Resize(QSize size) {
 game_scene_->resize(size);
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
  if(event->key() == Qt::Key_Escape) {
    controller_->OpenGameMenu();
  }
}

