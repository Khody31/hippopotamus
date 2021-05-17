#include "animation.h"

Animation::Animation(std::initializer_list<QString> list, uint64_t ms_per_frame)
    : ms_per_frame_(ms_per_frame) {
  for (const auto& path : list) {
    pixmaps_.push_back(new QPixmap(path));
  }
}

Animation::~Animation() {
  for (auto ptr : pixmaps_) {
    delete ptr;
  }
}

const QPixmap* Animation::GetFrame(uint64_t elapsed_time) const {
  return pixmaps_[(elapsed_time / ms_per_frame_) % pixmaps_.size()];
}
