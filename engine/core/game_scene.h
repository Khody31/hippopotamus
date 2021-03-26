// TODO(Nikolay Goponyako): Remove everything unrelated to rendering!

#pragma once

#include <QGraphicsScene>
#include <QWidget>
#include <QVector2D>
#include <set>

#include "engine/misc/singleton.h"
#include "engine/components/interfaces/pixmap_component_interface.h"
#include "engine/components/enums/scene_layer_ids.h"

class Player;

class GameScene : public QWidget, public Singleton {
 Q_OBJECT

 public:
  static constexpr int kNumOfLayers{static_cast<int>(SceneLayerID::kEnumSize)};
  static GameScene& GetInstance();

  void paintEvent(QPaintEvent*) override;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void SetPlayer(Player* player) {
    player_ = player;
  }

 private:
  friend class PixmapComponent;

  void AddPixmap(PixmapComponentInterface*);
  void RemovePixmap(PixmapComponentInterface*);

  void RenderPixmap(PixmapComponentInterface*, QPainter&);
  QRect GetPixmapQRect(const QVector2D& pos, const QVector2D& size);

  std::array<std::set<PixmapComponentInterface*>, kNumOfLayers> objects_;

  Player* player_;
};
