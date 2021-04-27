#pragma once

#include <bitset>

#include "components/components.h"

struct EntityDescription {
  std::optional<TransformationComponent> transform_comp;
  std::optional<PixmapComponent> pixmap_comp;
  std::optional<JoystickComponent> joystick_comp;
  std::optional<CollisionComponent> collision_comp;
  std::optional<MotionComponent> motion_comp;
  std::optional<SerializationComponent> serialization_comp;
};
