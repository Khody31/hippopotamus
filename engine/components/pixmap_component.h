#pragma once

#include <QGraphicsItem>
#include <QVector2D>

#include "engine/core/game_scene.h"
#include "engine/components/interfaces/pixmap_component_interface.h"
#include "engine/components/interfaces/game_object_interface.h"
#include "engine/components/interfaces/transformation_component_interface.h"

class PixmapComponent : public PixmapComponentInterface {
 public:
  explicit PixmapComponent(GameObjectInterface* parent,
                           const QVector2D& size,
                           SceneLayerID layer = SceneLayerID::kBackground,
                           const QString& file_path = "");
  ~PixmapComponent() {
    GameScene::GetInstance().RemovePixmap(this);
  }

  virtual void Update() override;

  [[nodiscard]] int GetLayer() const override {
    return static_cast<int>(layer_);
  }

  void SetLayer(SceneLayerID layer) override {
    GameScene::GetInstance().RemovePixmap(this);
    layer_ = layer;
    GameScene::GetInstance().AddPixmap(this);
  }

  [[nodiscard]] const QVector2D& GetPosition() const override {
    return parent_->GetTransformationComponent()->GetCoordinates();
  }

  [[nodiscard]] const QPixmap& GetPixmap() const override {
    return *pixmap_;
  }

  [[nodiscard]] const QVector2D& GetSize() const override {
    return size_;
  }

 private:
  static QPixmap* LoadPixmap(const QString& file_name);

  GameObjectInterface* parent_;
  QVector2D size_;
  SceneLayerID layer_;
  QPixmap* pixmap_;
};
