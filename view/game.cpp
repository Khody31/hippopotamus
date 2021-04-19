#include <QApplication>
#include <memory>

#include "game.h"

GameWidget::GameWidget(QWidget* parent, AbstractController* controller) :
    QWidget(parent), game_scene_(nullptr), controller_(controller) {}

void GameWidget::Resize(QSize size) {
  if (game_scene_ == nullptr) {
    return;
  }
  game_scene_->resize(size);
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    controller_->OpenGameMenu();
  }
}

void GameWidget::Continue() {
  game_scene_->StartTimer();
}

void GameWidget::Pause() {
  game_scene_->StopTimer();
}

void GameWidget::Start() {
  connector_ = std::make_shared<Connector>();
  game_scene_ = std::make_shared<GameScene>(connector_, this);
}

void GameWidget::Stop() {
  connector_ = nullptr;
  game_scene_ = nullptr;
}
