#include <QApplication>
#include <memory>

#include "game_widget.h"

GameWidget::GameWidget(AbstractController* controller, QWidget* parent) :
    CustomWidget(controller, parent) {}

void GameWidget::Resize(QSize size) {
  if (connector_ == nullptr) {
    return;
  }
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    controller_->OpenGameMenu();
  }
}

void GameWidget::Continue() {
  connector_->GetScene()->StartTimer();
}

void GameWidget::Pause() {
  connector_->GetScene()->StopTimer();
}

void GameWidget::Start() {
  connector_ = std::make_shared<Connector>(this, controller_);
}

void GameWidget::Stop() {
  connector_ = nullptr;
}

void GameWidget::OnKeyPress(QKeyEvent* event) {
  connector_->OnKeyPress(static_cast<Qt::Key>(event->key()));
}

void GameWidget::OnKeyRelease(QKeyEvent* event) {
  connector_->OnKeyRelease(static_cast<Qt::Key>(event->key()));
}

void GameWidget::StartNewGame() {
  connector_->StartNewGame();
}
