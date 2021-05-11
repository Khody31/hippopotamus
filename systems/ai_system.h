#pragma once

#include <components/components.h>
#include "engine/coordinator.h"

class Connector;

class AiSystem : public System {
 public:
  void Update(QVector2D player_pos, Coordinator* coordinator);
  void SetConnector(Connector*);

 private:
  Connector* connector_;
};