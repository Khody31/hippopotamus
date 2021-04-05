#include <QPainter>
#include <iostream>
#include "engine/comp/transformation_component.h"
#include "engine/comp/pixmap_component.h"
#include "game_scene.h"
#include "engine/system/game_widget.h"
#include "engine/misc/utils.h"

GameScene::GameScene()
    : Governor(ComponentIDs::kPixmapID),
      QWidget(&GameWidget::Get()) {
  GameWidget::Get().SetSceneWidget(this);
  show();
}

void GameScene::OnTick() {
  repaint();
}
void GameScene::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  for (const Component* child : GetComponents()) {
    auto pixmap_ptr{dynamic_cast<const PixmapComponent*>(child)};
    auto transform_ptr
        {dynamic_cast<const TransformationComponent*>(
             child->GetParent()->
                 GetComponent(ComponentIDs::kTransformationID))};
    QVector2D
        upper_left{transform_ptr->GetPos() - pixmap_ptr->GetSize() / 2};
    QVector2D
        lower_right{transform_ptr->GetPos() + pixmap_ptr->GetSize() / 2};
    QPoint
        game_ul{utils::GameToWidgetCoordinates(upper_left)};
    QPoint
        game_lr{utils::GameToWidgetCoordinates(lower_right)};

    painter.drawPixmap(game_ul.x(),
                       game_ul.y(),
                       game_lr.x() - game_ul.x(),
                       game_lr.y() - game_ul.y(),
                       pixmap_ptr->GetPixmap());
  }
}
