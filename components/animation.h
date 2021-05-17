#pragma once

#include <vector>
#include <QPixmap>

class Animation {
 public:
  Animation(std::initializer_list<QString>, uint64_t ms_per_frame);
  ~Animation();

  [[nodiscard]] const QPixmap* GetFrame(uint64_t elapsed_time) const;

 private:
  std::vector<QPixmap*> pixmaps_;
  uint64_t ms_per_frame_;
};
