#pragma  once

#include "component.h"

#include <QVector2D>

class PhysicsComponent : public Component {
 public:
  explicit PhysicsComponent(
      GameObject* parent,
      double mass = 0,
      QVector2D size = {0, 0});
  ~PhysicsComponent() override = default;

  QVector2D GetVelocity() const;
  double GetMass() const;
  QVector2D GetSize() const;
  double GetRestitution() const;

  void SetVelocity(QVector2D new_velocity);

 private:
  double mass_;
  double restitution_;
  QVector2D size_{0, 0};
  QVector2D velocity_{0, 0};
};
