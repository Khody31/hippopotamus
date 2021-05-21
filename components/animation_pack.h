#include <QPixmap>

class AnimationPack {
 public:
  explicit AnimationPack(const QString& path_to_json);
  const QPixmap* GetFrame(const QString& animation_name, uint64_t elapsed_time);

 private:
  std::unordered_map<QString, std::vector<std::unique_ptr<QPixmap>>> animations_;
  uint64_t frame_duration_;
};
