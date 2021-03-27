#include <map>
#include "pixmap_component.h"


// file_path example ":/textures/some_basic_player.png"
PixmapComponent::PixmapComponent(GameObjectInterface* parent,
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
  // точно каждый раз создавать QPixmap из QString не быстрее чем находить его в мапке?
  static std::map<QString, QPixmap> file_to_pixmap;
  return &(*file_to_pixmap.try_emplace(file_path, file_path).first).second;
}

void PixmapComponent::Update() {
  // Пока пустая. Возможно в будущем будет служить для анимации?
}
