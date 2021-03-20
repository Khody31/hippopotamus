#pragma once

#include <QObject>

#include "Engine/Components/Interfaces/game_object_interface.h"
#include "Engine/Components/Interfaces/transformation_component_interface.h"
#include "Engine/Components/Interfaces/pixmap_component_interface.h"

class GameObject : public GameObjectInterface {
 public:

  void SetTransformationComponent(TransformationComponentInterface* component) override;
  void SetPixmapComponent(PixmapComponentInterface* component) override;

  [[nodiscard]] TransformationComponentInterface* GetTransformationComponent() const override;
  [[nodiscard]] PixmapComponentInterface* GetPixmapComponent() const override;

 protected:
  TransformationComponentInterface* transformation_component_{nullptr};
  PixmapComponentInterface* pixmap_component_{nullptr};
};
