#include <map>
#include "pixmap_component.h"

// file_path example ":/textures/some_basic_player.png"
PixmapComponent::PixmapComponent(CoordinatesBase* parent,
                                 Vector2D size,
                                 SceneLayerID layer,
                                 const QString& file_path)
    : parent_(parent),
      size_(size),
      layer_(layer),
      pixmap_(LoadPixmap(file_path)) {
  GameScene::GetInstance().AddPixmap(this);
}

QPixmap* PixmapComponent::LoadPixmap(const QString& file_path) {
  static std::map<QString, QPixmap> file_to_pixmap;
  file_to_pixmap.try_emplace(file_path, file_path);
  return &file_to_pixmap.at(file_path);
}
