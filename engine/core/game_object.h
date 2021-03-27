#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <array>

#include "engine/comp/system_comp_ids.h"

class AbstractComponent;

class GameObject {
 public:
  AbstractComponent* GetComponent(uint64_t type_id);
  void AddComponent(AbstractComponent*, uint64_t type_id);

  ~GameObject();

 private:
  std::array<AbstractComponent*, ComponentIDs::kNumOfComponents> components_{};
};

#endif  // GAME_OBJECT_H_
