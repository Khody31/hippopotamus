#ifndef TRANSFORMATION_COMPONENT_H_
#define TRANSFORMATION_COMPONENT_H_

#include <QVector2D>
#include "component.h"

class TransformationComponent : public Component {
 public:
  TransformationComponent();

  void SetX(float x);
  void SetY(float y);
  void SetPos(const QVector2D&);
  void MoveBy(const QVector2D&);

 private:
  QVector2D pos_;
};

#endif  // TRANSFORMATION_COMPONENT_H_
