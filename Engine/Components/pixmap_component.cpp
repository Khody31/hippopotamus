#include "pixmap_component.h"

// file_path example ":/textures/some_basic_player.png"
PixmapComponent::PixmapComponent(CoordinatesBase* parent,
                                 SceneLayerID layer,
                                 const QString& file_path)
    : parent_(parent),
      layer_(layer),
      pixmap_(LoadPixmap(file_path)) {
  GameScene::GetInstance().AddPixmap(this);
}

QPixmap* PixmapComponent::LoadPixmap(const QString& file_path) {
  static std::map<QString, QPixmap> file_to_pixmap;
  if (file_to_pixmap.count(file_path) == 0) {
    file_to_pixmap[file_path] = QPixmap(file_path);
  }
  return &file_to_pixmap.at(file_path);
}
