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
  painter.drawPixmap(MapRawCoordinateToPixel(pixmap->GetPosition()),
                     pixmap->GetPixmap());
}

QPointF GameScene::MapRawCoordinateToPixel(const Vector2D& point) {
  QPointF result{};
  result.setX(
      (point.x + constants::kMaxXCoordinate) / (2 * constants::kMaxXCoordinate)
          * width());
  result.setY(
      (point.y + constants::kMaxYCoordinate) / (2 * constants::kMaxYCoordinate)
          * height());
  return result;
}
