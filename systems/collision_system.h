#pragma once

#include "components/components.h"
#include "engine/coordinator.h"
#include "core/keyboard_interface.h"

class Connector;

class CollisionSystem : public System {

 public:
  CollisionSystem(Connector* connector,
                  Coordinator* coordinator,
                  KeyboardInterface* keyboard);
  void Update();

 private:
  void UpdateCollisionComponents();
  void UpdateOtherComponents();

  Coordinator* coordinator_;
  KeyboardInterface* keyboard_;
  Connector* connector_;
};

struct Collision {
  CollisionComponent* first = nullptr;
  CollisionComponent* second = nullptr;
  float penetration = 0;
  QVector2D normal;
};

std::pair<float, float> CalculateOverlaps(Collision* collision);
bool IsCollisionPresent(Collision* collision);
void ResolveCollision(Collision* collision);
void PositionalCorrection(Collision* collision);


