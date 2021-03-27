#include "transformation_component_bullet.h"

void TransformationComponentBullet::Update() {
  coordinates_ += velocity_;
}
