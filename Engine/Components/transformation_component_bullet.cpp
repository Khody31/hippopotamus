//
// Created by nikolai on 25.03.2021.
//

#include "transformation_component_bullet.h"

void TransformationComponentBullet::Update() {
  coordinates_ += velocity_;
}
