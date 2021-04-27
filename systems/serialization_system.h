#pragma  once

#include "engine/system.h"
#include "core/room.h"

class SerializationSystem : public System {
 public:
  void Deserialize(Coordinator* coordinator, int id);
  void Serialize();
 private:
  static void LoadToJson(Room room);
  static Room LoadFromJson(int id);
  static EntityDescription LoadDescription(QJsonObject object);
  static auto LoadTransformationComponent(QJsonObject object);
  static auto LoadCollisionComponent(QJsonObject object);
  static auto LoadMotionComponent(QJsonObject object);
  static auto LoadPixmapComponent(QJsonObject object);
  static auto LoadVec2D(QJsonArray object);
  static QJsonObject LoadToJson(const EntityDescription& description);
  static QJsonObject LoadToJson(const TransformationComponent& component);
  static QJsonObject LoadToJson(const MotionComponent& component);
  static QJsonObject LoadToJson(const CollisionComponent& component);

  // TODO(Khody31) : implement serialization of empty components
  static QJsonObject LoadToJson(const JoystickComponent& component);
  static QJsonObject LoadToJson(const SerializationComponent& component);
  static QJsonObject LoadToJson(const PixmapComponent& component);
  static QJsonArray LoadToJson(const QVector2D& vector);
};
