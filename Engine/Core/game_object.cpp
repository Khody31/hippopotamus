#include "game_object.h"

TransformationComponent* GameObject::GetTransformationComponent() const {
  return transformation_component_;
}
PixmapComponent* GameObject::GetPixmapComponent() const {
  return pixmap_component_;
}
