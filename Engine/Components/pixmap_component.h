#pragma once

#include <QGraphicsItem>

#include "Engine/Core/game_scene.h"
#include "Engine/Components/coordinates_base.h"

class PixmapComponent : public PixmapComponentInterface {
 public:
  explicit PixmapComponent(CoordinatesBase* parent,
                           Vector2D size,
                           SceneLayerID layer = SceneLayerID::kBackground,
                           const QString& file_path = "");
  ~PixmapComponent() {
    GameScene::GetInstance().RemovePixmap(this);
  }

  [[nodiscard]] int GetLayer() const override {
    return static_cast<int>(layer_);
  }

  [[nodiscard]] Vector2D GetPosition() const override {
    return parent_->GetCoordinates();
  }

  [[nodiscard]] const QPixmap& GetPixmap() const override {
    return *pixmap_;
  }

  [[nodiscard]] Vector2D GetSize() const override {
    return size_;
  }

 private:
  static QPixmap* LoadPixmap(const QString& file_name);

  CoordinatesBase* parent_;
  Vector2D size_;
  SceneLayerID layer_;
  QPixmap* pixmap_;
};
