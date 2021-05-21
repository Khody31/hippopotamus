#include "engine/system.h"

class Coordinator;

class AnimationSystem : public System {
 public:
  explicit AnimationSystem(Coordinator* coordinator);
  void Update();

 private:
  void HandleMovingAnimation(Entity entity);
  void HandleStaticAnimation(Entity entity);

  Coordinator* coordinator_;
  uint64_t timestamp_;
};
