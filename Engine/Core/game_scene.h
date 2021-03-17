#pragma once

#include <QGraphicsScene>
#include <QWidget>
#include <set>

#include "Engine/Misc/singleton.h"
#include "Engine/Components/Interfaces/pixmap_component_interface.h"
#include "Engine/Components/Enums/scene_layer_ids.h"

class GameScene : public QWidget {
  Q_OBJECT
 public:
  GameScene(GameScene&) = delete;
  GameScene& operator=(GameScene&) = delete;

  static constexpr int
      kNumberOfLayers{static_cast<int>(SceneLayerID::kEnumSize)};
  static GameScene& GetInstance();

  void paintEvent(QPaintEvent*) override;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  GameScene() = default;

  friend class PixmapComponent;

  void AddPixmap(PixmapComponentInterface*);
  void RemovePixmap(PixmapComponentInterface*);

  void RenderPixmap(PixmapComponentInterface*, QPainter&);
  QRect GetPixmapQRect(const Vector2D& pos,
                        const Vector2D& size);

  std::set<PixmapComponentInterface*> objects_[kNumberOfLayers];
};
