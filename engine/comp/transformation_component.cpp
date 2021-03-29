#include "transformation_component.h"
#include "system_comp_ids.h"

void TransformationComponent::SetX(float x) {
  pos_.setX(x);
  EmitPulse();
}
void TransformationComponent::SetY(float y) {
  pos_.setY(y);
  EmitPulse();
}
void TransformationComponent::SetPos(const QVector2D& pos) {
  pos_ = pos;
  EmitPulse();
}
void TransformationComponent::MoveBy(const QVector2D& pos) {
  pos_ += pos;
  EmitPulse();
}
TransformationComponent::TransformationComponent()
    : Component(ComponentIDs::kTransformationID) {}
