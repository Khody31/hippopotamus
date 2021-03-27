#include "game_widget.h"
#include "engine/misc/utils.h"

GameWidget& GameWidget::Get() {
  static GameWidget instance;
  return instance;
}
void GameWidget::mousePressEvent(QMouseEvent* event) {
  if (!mouse_listener_) {
    return;
  }
  QVector2D event_pos{utils::WidgetToGameCoordinates(event->pos())};
  switch (event->button()) {
    case Qt::LeftButton: {
      mouse_listener_->OnLeftClick(event_pos);
      break;
    }
    case Qt::RightButton: {
      mouse_listener_->OnRightClick(event_pos);
      break;
    }
    default: { break; }
  }
}
void GameWidget::mouseReleaseEvent(QMouseEvent* event) {
  if (!mouse_listener_) {
    return;
  }
  QVector2D event_pos{utils::WidgetToGameCoordinates(event->pos())};
  switch (event->button()) {
    case Qt::LeftButton: {
      mouse_listener_->OnLeftRelease(event_pos);
      break;
    }
    case Qt::RightButton: {
      mouse_listener_->OnRightRelease(event_pos);
      break;
    }
    default: { break; }
  }
}
void GameWidget::SetMouseListener(AbstractMouseListener* mli_ptr) {
  mouse_listener_ = mli_ptr;
}
void GameWidget::keyPressEvent(QKeyEvent* event) {
  if (keyboard_listener_) {
    keyboard_listener_->OnPress(event);
  }
  KeyboardInterface::OnPress(event->nativeVirtualKey());
}
void GameWidget::keyReleaseEvent(QKeyEvent* event) {
  if (keyboard_listener_) {
    keyboard_listener_->OnRelease(event);
  }
  KeyboardInterface::OnRelease(event->nativeVirtualKey());
}
