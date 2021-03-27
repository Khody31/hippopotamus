#pragma once

#include "engine/core/game_object.h"
#include "engine/components/pixmap_component.h"
#include "engine/components/transformation_component_player.h"

class Player : public GameObject {
 public:
  Player();

  void OnTick() override;

};

