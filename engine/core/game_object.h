#pragma once

#include <QObject>

#include "engine/components/interfaces/game_object_interface.h"
#include "engine/components/interfaces/transformation_component_interface.h"
#include "engine/components/interfaces/pixmap_component_interface.h"
#include "engine/components/updatable_on_tick.h"

enum class EntityID {
  kPlayer,
  kBullet,
  kEnemy,

  kEnumSize
};

class GameObject : public GameObjectInterface, public UpdatableOnTick {
 public:
  explicit GameObject(EntityID entity);

  void OnTick() override;

  void SetTransformationComponent(TransformationComponentInterface* component) override;
  void SetPixmapComponent(PixmapComponentInterface* component) override;

  [[nodiscard]] TransformationComponentInterface* GetTransformationComponent() const override;
  [[nodiscard]] PixmapComponentInterface* GetPixmapComponent() const override;

 protected:
  TransformationComponentInterface* transformation_component_{nullptr};
  PixmapComponentInterface* pixmap_component_{nullptr};

  EntityID entity_;
};
