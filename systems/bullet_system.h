#include "engine/game_system.h"
#include <QVector2D>

class BulletSystem : public System {
 public:
  void Update(Coordinator* coordinator) override;

  void SetPlayer(Entity player);
  Entity GetPlayer();

  void CreateBullet(const QVector2D& point, Coordinator* coordinator);

 private:
  Entity player_;
};

