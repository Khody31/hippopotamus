#include <QPainter>
#include <QKeyEvent>
#include "game_scene.h"
#include "Engine/Misc/constants.h"
#include "keyboard_interface.h"
#include "Engine/Entities/player.h"
#include "Engine/Entities/bullet.h"
#include <cmath>

GameScene& GameScene::GetInstance() {
  static GameScene instance;
  return instance;
}

void GameScene::AddPixmap(PixmapComponentInterface* pixmap) {
  objects_[pixmap->GetLayer()].insert(pixmap);
}

void GameScene::RemovePixmap(PixmapComponentInterface* pixmap) {
  objects_[pixmap->GetLayer()].erase(pixmap);
}

void GameScene::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  for (const auto& objects_set : objects_) {
    for (PixmapComponentInterface* pixmap : objects_set) {
      RenderPixmap(pixmap, painter);
    }
  }
}

void GameScene::RenderPixmap(PixmapComponentInterface* pixmap,
                             QPainter& painter) {
  painter.drawPixmap(GetPixmapQRect(pixmap->GetPosition(),
                                    pixmap->GetSize()),
                     pixmap->GetPixmap());
}

QRect GameScene::GetPixmapQRect(const Vector2D& pos,
                                const Vector2D& size) {
  auto map_to_pixel = [this](Vector2D point) {
    point += constants::kMaxCoordinates;
    point.x *= this->width() / (2 * constants::kMaxCoordinates.x);
    point.y *= this->height() / (2 * constants::kMaxCoordinates.y);
    return point;
  };
  Vector2D upper_left{map_to_pixel(pos - size / 2)};
  Vector2D lower_right{map_to_pixel(pos + size / 2)};
  return QRect(static_cast<int>(upper_left.x),
               static_cast<int>(upper_left.y),
               static_cast<int>(lower_right.x - upper_left.x),
               static_cast<int>(lower_right.y - upper_left.y));
}

void GameScene::keyPressEvent(QKeyEvent* event) {
  KeyboardInterface::GetInstance().SetKeyPressed(event->key());
}

void GameScene::keyReleaseEvent(QKeyEvent* event) {
  KeyboardInterface::GetInstance().SetKeyReleased(event->key());
}

void GameScene::mousePressEvent(QMouseEvent* event) {
  double x = static_cast<double>(event->x())
      * 2.0 * constants::kMaxCoordinates.x / static_cast<double>(width());
  double y = static_cast<double>(event->y())
      * 2.0 * constants::kMaxCoordinates.y / static_cast<double>(height());
  x -= constants::kMaxCoordinates.x;
  y -= constants::kMaxCoordinates.y;
  x -= player_->GetTransformationComponent()->GetCoordinates().x;
  y -= player_->GetTransformationComponent()->GetCoordinates().y;
  Vector2D bullet_velocity{x,y};
  bullet_velocity.MakeLength(0.2);
  new Bullet(
      player_->GetTransformationComponent()->GetCoordinates(), bullet_velocity);
}

void GameScene::SetPlayer(Player* player) {
  player_ = player;
}
