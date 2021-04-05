#pragma  once

#include <QVector2D>

#include "component.h"

class TransformationComponent : public Component {
 public:
  TransformationComponent();

  void SetX(float x);
  void SetY(float y);
  void SetPos(const QVector2D&);
  void MoveBy(const QVector2D&);
  void SetVelocity(const QVector2D&);


  [[nodiscard]] const QVector2D& GetPos() const;
  [[nodiscard]] const QVector2D& GetVelocity() const;

 private:
  QVector2D pos_;
  QVector2D velocity_;
};
