#include "pixmap_component.h"

PixmapComponent::PixmapComponent(CoordinatesBase* parent,
                                 SceneLayerID layer,
                                 const QString& file_path)
    : parent_(parent),
      layer_(layer),
      pixmap_(LoadPixmap(file_path)) {
  GameScene::GetInstance().AddPixmap(this);
}

QPixmap* PixmapComponent::LoadPixmap(const QString& file_name) {
  // TODO(Khody31): Implement
  return nullptr;
}
