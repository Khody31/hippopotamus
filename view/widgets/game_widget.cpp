#include "game_widget.h"

#include "core/map_generator.h"

GameWidget::GameWidget(AbstractController* controller,
                       QWidget* parent,
                       MediaPlayer* media_player,
                       Cache* cache) :
    CustomWidget(controller, parent, ":/menu/screen-options.png"),
    media_player_(media_player), cache_(cache) {}

void GameWidget::Resize(QSize size) {
  if (connector_ == nullptr) {
    return;
  }
  connector_->GetScene()->resize(size);
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
  connector_ = std::make_shared<Connector>(this, controller_,
                                           media_player_, cache_);
  connector_->LoadGame();
}

void GameWidget::Stop() {
  connector_->GetScene()->StopTimer();
  connector_ = nullptr;
}

void GameWidget::OnKeyPress(QKeyEvent* event) {
  connector_->OnKeyPress(static_cast<Qt::Key>(event->key()));
}

void GameWidget::OnKeyRelease(QKeyEvent* event) {
  connector_->OnKeyRelease(static_cast<Qt::Key>(event->key()));
}

void GameWidget::StartNewGame() {
  connector_ = std::make_shared<Connector>(this, controller_,
                                           media_player_, cache_);
  connector_->StartNewGame();
}

void GameWidget::ChangeLanguage(Language language) {
}
