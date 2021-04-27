#include "serialization_system.h"

#include <QFile>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Room SerializationSystem::LoadFromJson(int id) {
  QFile file(":res/data/room_" + QString::number(id));
  file.open(QIODevice::ReadOnly);
  QJsonObject json_object = QJsonDocument::fromJson(
      file.readAll()).object();

  Room result(json_object["id"].toInt());
  QJsonArray entity_descriptions = json_object["entities"].toArray();
  for (int i = 0; i < entity_descriptions.size(); ++i) {
    EntityDescription description =
        LoadDescription(entity_descriptions[i].toObject());
    result.AddDescription(description);
  }

  return result;
}

void SerializationSystem::LoadToJson(Room room) {
  QJsonObject object;
  object.insert("id", room.GetId());
  QJsonArray entities;

  for (const auto& description : room.GetDescriptions()) {
    entities.append(QJsonObject(LoadToJson(description)));
  }

  object.insert("entities", entities);
}

QJsonObject SerializationSystem::LoadToJson(const EntityDescription& description) {
  QJsonObject object;
  if (description.transform_comp) {
    object.insert("transform", LoadToJson(description.transform_comp.value()));
  }
  if (description.collision_comp) {
    object.insert("collision", LoadToJson(description.collision_comp.value()));
  }
  if (description.joystick_comp) {
    object.insert("joystick", LoadToJson(description.joystick_comp.value()));
  }
  if (description.motion_comp) {
    object.insert("motion", LoadToJson(description.motion_comp.value()));
  }
  if (description.pixmap_comp) {
    object.insert("pixmap", LoadToJson(description.pixmap_comp.value()));
  }
  if (description.serialization_comp) {
    object.insert("serialization",
                  LoadToJson(description.serialization_comp.value()));
  }
  return object;
}

auto SerializationSystem::LoadVec2D(QJsonArray object) {
  QVector2D result;
  result[0] = static_cast<float>(object[0].toDouble());
  result[1] = static_cast<float>(object[1].toDouble());
  return result;
}

auto SerializationSystem::LoadTransformationComponent(QJsonObject object) {
  TransformationComponent component;
  component.pos = LoadVec2D(object["pos"].toArray());
  return component;
}

auto SerializationSystem::LoadCollisionComponent(QJsonObject object) {
  CollisionComponent component;
  component.inverted_mass =
      static_cast<float>(object["inverted_mass"].toDouble());
  component.elasticity = static_cast<float>(object["elasticity"].toDouble());
  component.size = LoadVec2D(object["size"].toArray());
  return component;
}

auto SerializationSystem::LoadMotionComponent(QJsonObject object) {
  MotionComponent component;
  component.direction = LoadVec2D(object["direction"].toArray());
  component.speed = static_cast<float>(object["speed"].toDouble());
  return component;
}

auto SerializationSystem::LoadPixmapComponent(QJsonObject object) {
  PixmapComponent component;
  component.size = LoadVec2D(object["size"].toArray());

  // TODO(Khody31) : implement pixmap loading

  return component;
}

EntityDescription SerializationSystem::LoadDescription(QJsonObject object) {
  EntityDescription description;

  // TODO(Khody31) : implement serialization and joystick component loading

  if (!object["transformation"].isNull()) {
    description.transform_comp =
        LoadTransformationComponent(object["transformation"].toObject());
  }
  if (!object["pixmap"].isNull()) {
    description.pixmap_comp =
        LoadPixmapComponent(object["pixmap"].toObject());
  }
  if (!object["collision"].isNull()) {
    description.collision_comp =
        LoadCollisionComponent(object["collision"].toObject());
  }
  if (!object["motion"].isNull()) {
    description.motion_comp =
        LoadMotionComponent(object["motion"].toObject());
  }

  return EntityDescription();
}

QJsonArray SerializationSystem::LoadToJson(const QVector2D& vector) {
  QJsonArray object;
  object.append(vector.x());
  object.append(vector.y());
  return object;
}

QJsonObject SerializationSystem::LoadToJson(
    const TransformationComponent& component) {
  QJsonObject object;
  object.insert("pos", LoadToJson(component.pos));
  return object;
}

QJsonObject SerializationSystem::LoadToJson(const MotionComponent& component) {
  QJsonObject object;
  object.insert("speed", component.speed);
  object.insert("direction", LoadToJson(component.direction));
  return object;
}

QJsonObject SerializationSystem::LoadToJson(const CollisionComponent& component) {
  QJsonObject object;
  object.insert("size", LoadToJson(component.size));
  object.insert("inverted_mass", component.inverted_mass);
  object.insert("elasticity", component.elasticity);
  return object;
}

QJsonObject SerializationSystem::LoadToJson(const PixmapComponent& component) {
  QJsonObject object;
  object.insert("size", LoadToJson(component.size));
  // TODO(Khody31) : implement insertion of pixmap

  return object;
}
