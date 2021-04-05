#include <QApplication>

#include "engine/system/game_widget.h"
#include "engine/core/game_object.h"
#include "engine/comp/transformation_component.h"
#include "engine/comp/pixmap_component.h"
#include "engine/engine.h"
#include "mouse_listener.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  GameWidget::Get().show();
  GameWidget::Get().setFixedSize(1600, 900);
  Engine::Init();
  GameObject player;
  player.AddComponent(new TransformationComponent);
  // dynamic_cast<TransformationComponent*>(
  // player.GetComponent(ComponentIDs::kTransformationID))
  // ->SetPos({-1.0, -1.0});
  player.AddComponent(new PixmapComponent({0.5, 0.5}, ":/player.png"));
  MouseListener ml;
  GameWidget::Get().SetMouseListener(&ml);

  return QApplication::exec();
}
