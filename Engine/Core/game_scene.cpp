#include <QPainter>
#include "game_scene.h"
#include "Engine/Misc/constants.h"

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
  for (const auto& objects_set : objects_) {
    for (PixmapComponentInterface* pixmap : objects_set) {
      RenderPixmap(pixmap);
    }
  }
}

void GameScene::RenderPixmap(PixmapComponentInterface* pixmap) {
  static QPainter painter;
  painter.drawPixmap(GetPixmapQRect(pixmap->GetPosition(),
                                    pixmap->GetSize()),
                     pixmap->GetPixmap());
}

QRect GameScene::GetPixmapQRect(const Vector2D& pos,
                                const Vector2D& size) {
  auto map_to_pixel = [this](Vector2D point) {
    point += constants::kMaxCoordinates;
    point.x *= this->width() / constants::kMaxCoordinates.x;
    point.y *= this->height() / constants::kMaxCoordinates.y;
    return point;
  };
  Vector2D upper_left{map_to_pixel(pos - size / 2)};
  Vector2D size_in_pixels{map_to_pixel(size)};
  return QRect(static_cast<int>(upper_left.x),
               static_cast<int>(upper_left.y),
               static_cast<int>(size_in_pixels.x),
               static_cast<int>(size_in_pixels.y));
}
