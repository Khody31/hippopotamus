#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "animation_pack.h"

const QPixmap* AnimationPack::GetFrame(AnimationType type,
                                       uint64_t elapsed_time) const {
  const auto& animation = animations_.at(type);
  return animation[(elapsed_time / frame_duration_) % animation.size()].get();
}

AnimationPack::AnimationPack(const QString& path_to_json) {
  QFile file(path_to_json);
  file.open(QIODevice::ReadOnly);
  assert(file.isOpen());
  QJsonObject input_object = QJsonDocument::fromJson(file.readAll()).object();
  assert(!input_object.isEmpty());
  file.close();
  auto animation_names = input_object["animations"].toObject();

  auto keys = animation_names.keys();
  for (const auto& key : keys) {
    assert(str_to_type.find(key) != str_to_type.end()
               && "Invalid animation type name");
    const auto& animation_paths = animation_names[key];

    AnimationType type = str_to_type.at(key);
    std::vector<std::unique_ptr<QPixmap>>& animation = animations_[type];
    const auto& array = animation_paths.toArray();

    for (const auto& frame_path : array) {
      animation.push_back(std::make_unique<QPixmap>(frame_path.toString()));
      assert(!animation.back()->isNull() && "No pixmap at path specified");
    }
  }
  frame_duration_ = input_object["frame_duration"].toInt();
}
