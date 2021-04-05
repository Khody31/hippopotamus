#pragma once

#include "engine/gov/governor.h"
#include "engine/core/game_object.h"

class Component {
 public:
  explicit Component(int type_id);
  virtual ~Component();

  [[nodiscard]] GameObject* GetParent() const;
  [[nodiscard]] int GetTypeID() const;

 protected:
  void EmitPulse();

 private:
  friend class GameObject;

  void SetParent(GameObject*);

  GameObject* parent_object_{};
  Governor* parent_governor_;

  int type_id_;
};
