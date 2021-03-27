#ifndef ABSTRACT_COMPONENT_H_
#define ABSTRACT_COMPONENT_H_

#include "engine/gov/governor.h"
#include "engine/core/game_object.h"

class AbstractComponent {
 public:
  explicit AbstractComponent(uint64_t type_id);
  ~AbstractComponent();

  [[nodiscard]] GameObject* GetParent() const;

 protected:
  void NotifyGovernor();

 private:
  friend class GameObject;

  void SetParent(GameObject*);

  GameObject* parent_object_{};
  Governor* parent_governor_{};
};

#endif  // ABSTRACT_COMPONENT_H_
