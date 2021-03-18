#pragma once

#include <QGraphicsItem>

#include "Engine/Core/game_scene.h"
#include "Engine/Components/Interfaces/pixmap_component_interface.h"
#include "Engine/Components/Interfaces/game_object_interface.h"
#include "Engine/Components/Interfaces/transformation_component_interface.h"



class PixmapComponent : public PixmapComponentInterface {
 public:
  explicit PixmapComponent(GameObjectInterface* parent,
                           Vector2D size,
                           SceneLayerID layer = SceneLayerID::kBackground,
                           const QString& file_path = "");
  ~PixmapComponent() {
    GameScene::GetInstance().RemovePixmap(this);
  }

  [[nodiscard]] int GetLayer() const override {
    return static_cast<int>(layer_);
  }

  void SetLayer(SceneLayerID layer) override {
    GameScene::GetInstance().RemovePixmap(this);
    layer_ = layer;
    GameScene::GetInstance().AddPixmap(this);
  }

  [[nodiscard]] Vector2D GetPosition() const override {
    return parent_->GetTransformationComponent()->GetCoordinates();
  }

  [[nodiscard]] const QPixmap& GetPixmap() const override {
    return *pixmap_;
  }

  [[nodiscard]] Vector2D GetSize() const override {
    return size_;
  }

 private:
  static QPixmap* LoadPixmap(const QString& file_name);

  GameObjectInterface* parent_;
  Vector2D size_;
  SceneLayerID layer_;
  QPixmap* pixmap_;
};
