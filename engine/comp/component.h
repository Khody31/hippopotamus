#ifndef ABSTRACT_COMPONENT_H_
#define ABSTRACT_COMPONENT_H_

#include "engine/gov/governor.h"
#include "engine/core/game_object.h"

class Component {
 public:
  explicit Component(uint64_t type_id, GameObject* parent = nullptr);
  virtual ~Component();

  [[nodiscard]] GameObject* GetParent() const;

 protected:
  void EmitPulse();

 private:
  friend class GameObject;

  void SetParent(GameObject*);

  GameObject* parent_object_{};
  Governor* parent_governor_;

  int type_id_;
};

#endif  // ABSTRACT_COMPONENT_H_
